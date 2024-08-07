#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <memory> // For std::allocator
#include <new> // For placement new
#include <cstddef>
#include <cstdint>
#include <type_traits>

#ifndef HEAP_SIZE_BYTES
#define HEAP_SIZE_BYTES 4096
#endif

template <typename T, std::size_t N = HEAP_SIZE_BYTES>
class StaticHeap {
    static constexpr std::size_t heapSize = N / sizeof(T);
    std::aligned_storage_t<sizeof(T), alignof(T)> buffer[heapSize];
    bool used[heapSize] = { false };

public:
    template <typename... Args>
    T* allocate(Args&&... args) {
        for (std::size_t i = 0; i < heapSize; ++i) {
            if (!used[i]) {
                used[i] = true;
                return new (&buffer[i]) T(std::forward<Args>(args)...);
            }
        }
        return nullptr; // No space available
    }

    void deallocate(T* ptr) {
        for (std::size_t i = 0; i < heapSize; ++i) {
            if (ptr == reinterpret_cast<T*>(&buffer[i])) {
                ptr->~T();
                used[i] = false;
                return;
            }
        }
    }
};



template <typename DataType>
struct BNode {
    DataType data = DataType();
    BNode<DataType>* right = nullptr;
    BNode<DataType>* left = nullptr;
    BNode<DataType>* parent = nullptr;
    uint32_t bitvector = 0;

    // Disable copy and move operations
    BNode(const BNode& other) = delete;
    BNode& operator=(const BNode& other) = delete;
    BNode(BNode&& other) = delete;
    BNode& operator=(BNode&& other) = delete;

    // Constructor
    BNode() : parent(nullptr), left(nullptr), right(nullptr), bitvector(0) {}
    BNode(const DataType& val, BNode<DataType>* parent)
        : data(val), parent(parent), left(nullptr), right(nullptr), bitvector(0) {}

    // Destructor
    ~BNode() {}

    enum Color { RED, BLACK };

    Color getColor() const {
        return static_cast<Color>((bitvector >> 31) & 1);
    }

    void setColor(Color color) {
        if (color == RED) {
            bitvector |= (1 << 31); // Set MSB
        }
        else {
            bitvector &= ~(1 << 31); // Clear MSB
        }
    }

    bool getOriginalColor() const {
        return (bitvector >> 30) & 1;
    }

    void setOriginalColor(bool color) {
        if (color) {
            bitvector |= (1 << 30); // Set the second MSB
        }
        else {
            bitvector &= ~(1 << 30); // Clear the second MSB
        }
    }

    uint32_t getCount() const {
        return bitvector & 0x3FFFFFFF; // Get count without the two MSBs
    }

    void setCount(uint32_t cnt) {
        bitvector = (bitvector & 0xC0000000) | (cnt & 0x3FFFFFFF); // Set count, preserve the two MSBs
    }
};
auto print_int = [](BNode<int>* p) { std::cout << p->data << " "; };
auto print_str = [](BNode<const char*>* p) { std::cout << p->data << " "; };
auto cmp_str = [](const char* key, const char* pdata) { return std::strcmp(key, pdata); };

auto cmp_int = [](const int& key, const int& pdata) {
    if (key == pdata) {
        return 0;
    }
    else if (key < pdata) {
        return -1;
    }
    else {
        return 1;
    }
    };

template <typename DataType, typename Compare = decltype(cmp_int), typename Func = decltype(print_int)>
class BinTree {
    BNode<DataType> sentinel;
    BNode<DataType>* root = &sentinel;
    Compare comp;
    Func func;
    StaticHeap<BNode<DataType>> heap;

    void delete_tree(BNode<DataType>* p)  {
        if (p && p != &sentinel) {
            delete_tree(p->left);
            delete_tree(p->right);
            heap.deallocate(p);
        }
    }

    void inner_visit_in_order(BNode<DataType>* p) const {
        if (p != &sentinel) {
            inner_visit_in_order(p->left);
            func(p);
            inner_visit_in_order(p->right);
        }
    }

    void inner_visit_pre_order(BNode<DataType>* p) const {
        if (p != &sentinel) {
            func(p);
            inner_visit_pre_order(p->left);
            inner_visit_pre_order(p->right);
        }
    }

    void inner_visit_post_order(BNode<DataType>* p) const {
        if (p != &sentinel) {
            inner_visit_post_order(p->left);
            inner_visit_post_order(p->right);
            func(p);
        }
    }

    void inner_get_test_vector(BNode<DataType>* p, std::vector<DataType>& v) {
        if (p != &sentinel) {
            inner_get_test_vector(p->left, v);
            v.push_back(p->data);
            inner_get_test_vector(p->right, v);
        }
    }

    BNode<DataType>* successor(BNode<DataType>* x) {
        if (x == nullptr) {
            return nullptr;
        }
        if (x->right != nullptr) {
            return find_min(x->right);
        }
        BNode<DataType>* y = x->parent;
        while (y != nullptr && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    BNode<DataType>* predecessor(BNode<DataType>* x) {
        if (x == nullptr) {
            return nullptr;
        }
        if (x->left != nullptr) {
            return find_max(x->left);
        }
        BNode<DataType>* y = x->parent;
        while (y != nullptr && x == y->left) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    BNode<DataType>* find_min(BNode<DataType>* p) {
        while (p && p->left != nullptr) {
            p = p->left;
        }
        return p;
    }

    BNode<DataType>* find_max(BNode<DataType>* p) {
        while (p && p->right != nullptr) {
            p = p->right;
        }
        return p;
    }

    void transplant(BNode<DataType>* u, BNode<DataType>* v) {
        if (u == nullptr || u == &sentinel) {
            return;
        }
        if (u->parent == &sentinel) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        if (v != &sentinel) {
            v->parent = u->parent;
        }
    }

    BNode<DataType>* inner_search(BNode<DataType>* p, const DataType& key) {
        if (p == nullptr || p == &sentinel || comp(key, p->data) == 0) {
            return p;
        }

        if (comp(key, p->data) == -1) {
            return inner_search(p->left, key);
        }
        else {
            return inner_search(p->right, key);
        }
    }

    void left_rotate(BNode<DataType>* x) {
        if (x == nullptr || x->right == nullptr) {
            return;
        }

        BNode<DataType>* y = x->right; // y is x's right child
        x->right = y->left; // Turn y's left subtree into x's right subtree

        if (y->left != &sentinel) {
            y->left->parent = x;
        }
        y->parent = x->parent; // Link y's parent to x's parent

        if (x->parent == &sentinel) {
            root = y; // If x was root, make y the new root
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x; // Put x on y's left
        x->parent = y;
    }

    void right_rotate(BNode<DataType>* x) {
        if (x == nullptr || x == &sentinel) {
            return;
        }

        BNode<DataType>* y = x->left;
        if (y == &sentinel) {
            return;
        }

        x->left = y->right;
        if (y->right != &sentinel) {
            y->right->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == &sentinel) {
            root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;
    }

    void inner_rb_insert(BNode<DataType>* z) {
        BNode<DataType>* y = &sentinel;
        BNode<DataType>* x = root;

        while (x != &sentinel) {
            y = x;
            if (comp(z->data, x->data) == 0) {
                // If duplicate, increase count and return
                uint32_t current_count = x->getCount();
                x->setCount(current_count + 1);
                heap.deallocate(z);
                return;
            }
            else if (comp(z->data, x->data) == -1) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == &sentinel) {
            root = z;
        }
        else if (comp(z->data, y->data) == -1) {
            y->left = z;
        }
        else {
            y->right = z;
        }
        z->left = &sentinel;
        z->right = &sentinel;
        z->setColor(BNode<DataType>::RED);
        z->setOriginalColor(BNode<DataType>::RED); // Set the original color as RED
        rb_insert_fixup(z);
    }

    void rb_insert_fixup(BNode<DataType>* z) 
    {
        while (z->parent != nullptr && z->parent->getColor() == BNode<DataType>::RED) {
            if (z->parent == z->parent->parent->left) {
                BNode<DataType>* y = z->parent->parent->right;
                if (y->getColor() == BNode<DataType>::RED) {
                    z->parent->setColor(BNode<DataType>::BLACK);
                    y->setColor(BNode<DataType>::BLACK);
                    z->parent->parent->setColor(BNode<DataType>::RED);
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->setColor(BNode<DataType>::BLACK);
                    z->parent->parent->setColor(BNode<DataType>::RED);
                    right_rotate(z->parent->parent);
                }
            }
            else {
                BNode<DataType>* y = z->parent->parent->left;
                if (y->getColor() == BNode<DataType>::RED) {
                    z->parent->setColor(BNode<DataType>::BLACK);
                    y->setColor(BNode<DataType>::BLACK);
                    z->parent->parent->setColor(BNode<DataType>::RED);
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->setColor(BNode<DataType>::BLACK);
                    z->parent->parent->setColor(BNode<DataType>::RED);
                    left_rotate(z->parent->parent);
                }
            }
        }
        root->setColor(BNode<DataType>::BLACK);
    }

    void inner_rb_delete(BNode<DataType>* z) {
        if (z == nullptr) {
            return;
        }
        BNode<DataType>* y = z;
        BNode<DataType>* x = nullptr;
        auto y_original_color = y->getColor();
        if (z->left == &sentinel) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == &sentinel) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = find_min(z->right);
            y_original_color = y->getColor();
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->setColor(z->getColor());
        }
        if (y_original_color == BNode<DataType>::BLACK) {
            rb_delete_fixup(x);
        }
    }

    void rb_delete_fixup(BNode<DataType>* x) {
        while (x != root && x->getColor() == BNode<DataType>::BLACK) {
            if (x == x->parent->left) {
                BNode<DataType>* w = x->parent->right;
                if (w->getColor() == BNode<DataType>::RED) {
                    w->setColor(BNode<DataType>::BLACK);
                    x->parent->setColor(BNode<DataType>::RED);
                    left_rotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->getColor() == BNode<DataType>::BLACK && w->right->getColor() == BNode<DataType>::BLACK) {
                    w->setColor(BNode<DataType>::RED);
                    x = x->parent;
                }
                else {
                    if (w->right->getColor() == BNode<DataType>::BLACK) {
                        w->left->setColor(BNode<DataType>::BLACK);
                        w->setColor(BNode<DataType>::RED);
                        right_rotate(w);
                        w = x->parent->right;
                    }
                    w->setColor(x->parent->getColor());
                    x->parent->setColor(BNode<DataType>::BLACK);
                    w->right->setColor(BNode<DataType>::BLACK);
                    left_rotate(x->parent);
                    x = root;
                }
            }
            else {
                BNode<DataType>* w = x->parent->left;
                if (w->getColor() == BNode<DataType>::RED) {
                    w->setColor(BNode<DataType>::BLACK);
                    x->parent->setColor(BNode<DataType>::RED);
                    right_rotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->getColor() == BNode<DataType>::BLACK && w->left->getColor() == BNode<DataType>::BLACK) {
                    w->setColor(BNode<DataType>::RED);
                    x = x->parent;
                }
                else {
                    if (w->left->getColor() == BNode<DataType>::BLACK) {
                        w->right->setColor(BNode<DataType>::BLACK);
                        w->setColor(BNode<DataType>::RED);
                        left_rotate(w);
                        w = x->parent->left;
                    }
                    w->setColor(x->parent->getColor());
                    x->parent->setColor(BNode<DataType>::BLACK);
                    w->left->setColor(BNode<DataType>::BLACK);
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }
        x->setColor(BNode<DataType>::BLACK);
    }

public:
    BinTree(Compare compare = cmp_int, Func func = print_int) : comp(compare), func(func) {
        sentinel.left = &sentinel;
        sentinel.right = &sentinel;
    }

    ~BinTree() {
        delete_tree(root);
        root = nullptr;
    }

    void rb_insert(const DataType& data) {
        auto z = heap.allocate();
        new (z) BNode<DataType>(data, nullptr); // Placement new
        if (root == &sentinel) {
            // Tree is empty, z becomes the root
            z->parent = &sentinel;
            root = z;
            root->setColor(BNode<DataType>::BLACK); // Root must be black
            root->left = &sentinel;
            root->right = &sentinel;
        }
        else {
            inner_rb_insert(z);
        }
    }

    void visit_in_order() const {
        inner_visit_in_order(root);
    }

    void visit_pre_order() const {
        inner_visit_pre_order(root);
    }

    void visit_post_order() const {
        inner_visit_post_order(root);
    }

    BNode<DataType>* search(const DataType& key) {
        return inner_search(root, key);
    }

    std::vector<DataType> get_test_vector() {
        std::vector<DataType> v;
        inner_get_test_vector(root, v);
        return v;
    }

    void rb_delete(const DataType& key) {
        auto p = inner_search(root, key);
        inner_rb_delete(p);
    }
};
