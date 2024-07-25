/*==============================================================================
 Name        : open_table.c 
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#include "common.h"
/**=============================================================================
 Interface:   open_table

 Purpose:    open_table is an open addressing hash table that uses the static
             heap manager.  It uses double hashing for collision resolution.
==============================================================================*/
struct open_table {
	size_t count;
	size_t table_size;
	size_t datasize;
	size_t collisions;  // New field for tracking collisions
	size_t (*h1)(const genptr value);
	size_t (*h2)(const genptr value);
	int (*compare)(const genptr, const genptr);
        void(*alloc_insert)(tableptr, size_t, genptr);
	genptr* table;
};

/**=============================================================================
 Function:   open_table_init

 Purpose:    Returns an open_table interface pointer.  

 Parameters: tbsize: sizeof the hash table, should be prime number.
             datasize: size in bytes of an entry.
             h1: primary hash function.
	     h2: secondary hash function (can be the same as h1).
	     compare: compare two generic types.

 Returns:     open_table interface pointer.

 Example:     tableptr tp = open_table_init(97, sizeof(foo), foo_h1, foo_h2);
==============================================================================*/
tableptr open_table_init(const size_t tbsize, const size_t datasize,
			size_t (*h1)(const genptr),
			size_t (*h2)(const genptr),
			int (*compare)(const genptr, const genptr),
                        void(*alloc_insert)(tableptr, size_t, genptr))
{
	assert(h1 && h2 && compare);
	tableptr newtable = Heap_Malloc(sizeof(open_table));
	if (newtable == NULL) {
		fprintf(stderr, "out of memory error\n");
		exit(EXIT_FAILURE);
	}

	newtable->table = Heap_Malloc(tbsize * CHAR_BIT);
	if (newtable->table == NULL) {
		fprintf(stderr, "out of memory error\n");
		Heap_Free(newtable);
		exit(EXIT_FAILURE);
	}

	newtable->table_size = tbsize;
	newtable->datasize = datasize;
	newtable->h1 = h1;
	newtable->h2 = h2;
	newtable->count=0;
	newtable->collisions=0;
	newtable->compare = compare;
        newtable->alloc_insert = alloc_insert;
	newtable->count = 0;

	for (int i = 0; i < tbsize; i++)
		newtable->table[i] = NULL;

	return newtable;
}

void open_table_destroy(tableptr table)
{
	assert(table);
	for (int i = 0; i < table->table_size; i++) {
		Heap_Free(table->table[i]);
		table->table[i] = NULL;
	}

	Heap_Free(table->table);
	Heap_Free(table);
}
/**=============================================================================
 Function:   open_table_insert

 Purpose:    Inserts a generic type into the hash table  

 Parameters: table: open_table interface pointer
             value: entry to add

 Returns:     enum: INSERTED indicates that the new entry was added. EXISTS
              indicates that the entry already exists in the table. FULL 
	      indicates that there is no room for another entry, the table needs
	      to be resized and rehashed.

 Example:     open_table_insert(pt, &foo);
==============================================================================*/
size_t quadratic_probe(size_t hash, int i, size_t table_size) {
    return (hash + i * i) % table_size;
}
enum insert_state open_table_insert(tableptr table, const genptr value) {
    assert(table);

    if (open_table_lookup(table, value) != NULL)
        return EXISTS;

    size_t hash = table->h1(value);
    for (int i = 0; i < table->table_size; i++) {
        size_t idx = quadratic_probe(hash, i, table->table_size);

        if (table->table[idx] == NULL) {
            table->alloc_insert(table, idx, value);
            table->count++;
            return INSERTED;
        } else {
            table->collisions++;
        }
    }
    return TABLEFULL;
}
_Bool open_table_remove_entry(tableptr table, const genptr value) {
    assert(table);
    size_t hash = table->h1(value);
    for (int i = 0; i < table->table_size; i++) {
        size_t idx = quadratic_probe(hash, i, table->table_size);

        if (table->table[idx] != NULL &&
            (table->compare(value, table->table[idx]) == 0)) {
            Heap_Free(table->table[idx]);
            table->table[idx] = NULL;
            table->count--;
            return true;
        }
    }
    return false;
}
genptr open_table_lookup(const tableptr table, const genptr value) {
    assert(table);
    size_t hash = table->h1(value);
    for (int i = 0; i < table->table_size; i++) {
        size_t idx = quadratic_probe(hash, i, table->table_size);

        if (table->table[idx] != NULL &&
            (table->compare(value, table->table[idx]) == 0))
            return table->table[idx];
    }
    return NULL;
}



size_t open_table_resize(tableptr table, const size_t newsize)
{
	assert(table);
	return table->table_size;
}

void open_table_visit(const tableptr table, void (*visit)(const genptr))
{
	assert(table);
	for (int i = 0; i < table->table_size; i++)
		if(table->table[i] != NULL)
			visit(table->table[i]);
}

size_t open_table_size(const tableptr table)
{
	assert(table);
	return table->table_size;
}

size_t open_table_entries(const tableptr table)
{
	assert(table);
	return table->count;
}
_Bool open_table_resize_needed(const tableptr table)
{
   assert(table);
   size_t cap = table->table_size - table->count;
   if (cap < (table->table_size / 4))
      return true;

   return false;
}

#define FNV_PRIME_32 16777619
#define FNV_OFFSET_BASIS_32 2166136261U

//fnv1a
size_t strhash(const char* str) {
    size_t hash = FNV_OFFSET_BASIS_32;
    for (const char* p = str; *p != '\0'; p++) {
        hash ^= (size_t)(unsigned char)(*p);
        hash *= FNV_PRIME_32;
    }
    return hash;
}

size_t inthash(const int* value)
{
   assert(value);
   const int* ptr = value;
   size_t val = 0;
   size_t tmp = 0;

   val = (val << 4) + (*ptr);

   if ((tmp = (val & 0xf0000000))) {
      val = val ^ (tmp >> 24);
      val = val ^ tmp;
   }

   return val;
}

void table_report(const tableptr table)
{
   printf("Table size: %zu Element count: %zu Collisions: %zu\n", table->table_size, table->count, table->collisions);
}
void table_int_alloc(tableptr table, size_t idx, genptr value)
{
    assert(table && value);
    table->table[idx] = Heap_Malloc(table->datasize);
	memcpy(table->table[idx], value, table->datasize);
}

void table_str_alloc(tableptr table, size_t idx, genptr value)
{
    assert(table && value);
    const char * s = (const char*)value;
    size_t len = strlen(s);
    table->table[idx] = Heap_Malloc(len);
	strcpy(table->table[idx], s);
}

void open_table_cluster_report(const tableptr table) 
{
	puts("\n---------------REPORT----------------------------\n");
	table_report(table);
	puts("\n---------------CLUSTER REPORT----------------------------\n");
	for (int i = 0; i < table->table_size; i++) {
		if(table->table[i] == NULL) {
			printf("%s ", "_");
		} else {
			printf("%s ", "F");
		}
	}
	analyze_clusters(table);
	puts("\n---------------END CLUSTER REPORT----------------------------\n");
}

void analyze_clusters(const tableptr table) 
{
    enum { IN, OUT } state = OUT;
    size_t cluster_count = 0;
    size_t total_cluster_length = 0;
    size_t largest_cluster = 0;
    size_t current_cluster_length = 0;

    for (size_t i = 0; i < table->table_size; i++) {
        if (table->table[i] != NULL) {  // Filled slot
            if (state == OUT) {
                state = IN;
                cluster_count++;
                current_cluster_length = 1;
            } else {
                current_cluster_length++;
            }
            total_cluster_length++;
        } else {  // Empty slot
            if (state == IN) {
                state = OUT;
                if (current_cluster_length > largest_cluster) {
                    largest_cluster = current_cluster_length;
                }
                current_cluster_length = 0;  // Reset for next cluster
            }
        }
    }

    // Check if the last cluster is the largest
    if (state == IN && current_cluster_length > largest_cluster) {
        largest_cluster = current_cluster_length;
    }

    printf("Cluster Count: %zu\n", cluster_count);
    printf("Total Cluster Length: %zu\n", total_cluster_length);
    printf("Largest Cluster Size: %zu\n", largest_cluster);
    printf("Average Cluster Length: %.2f\n", cluster_count ? (double)total_cluster_length / cluster_count : 0.0);
}