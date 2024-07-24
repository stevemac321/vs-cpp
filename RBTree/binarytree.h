
#pragma once
template <typename DataType>
struct BNode {
    DataType data;
    int count = 1;
    BNode<DataType>* right = nullptr;
    BNode<DataType>* left = nullptr;
    BNode<DataType>* parent = nullptr;
    bool is_red = false;

    // Disable copy and move operations
    BNode(const BNode& other) = delete;
    BNode& operator=(const BNode& other) = delete;
    BNode(BNode&& other) = delete;
    BNode& operator=(BNode&& other) = delete;

    // Constructor
    BNode() {}
    BNode(const DataType& val, BNode<DataType> *parent) : data(val), parent(parent) {}

    // Destructor
    ~BNode() {
  
    }
};

auto print_int = [](BNode<int> *p) { std::cout << p->data << " "; };
auto print_str = [](BNode<const char*> *p) { std::cout << p->data << " "; };

auto cmp_int = [](const int &key, const int &pdata) {
    if(key == pdata) {
        return 0;
    }else if (key < pdata) {
        return -1;
    } else {
        return 1;
    };
};
auto cmp_str = [](const char *key, const char *pdata) {return std::strcmp(key, pdata);};

template <typename DataType, typename Compare = decltype(cmp_int), typename Func = decltype(print_int)>
class BinTree {
    BNode<DataType> sentinel;
    BNode<DataType>* root = &sentinel;
    Compare comp;
    Func func;

 

    void delete_tree(BNode<DataType>* p) const {
        if (p && p != &sentinel) {
            delete_tree(p->left);
            delete_tree(p->right);
            delete p;
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
 BNode<DataType>* successor(BNode<DataType>* x) 
 {
    if(x == nullptr) {
        return nullptr;
    }
    if(x->right != nullptr) {
        return find_min(x->right);
    }
    BNode<DataType> *y = x->parent;
    while(y != nullptr && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
 }
 BNode<DataType>* predecessor(BNode<DataType>* x) 
 {
    if(x == nullptr) {
        return nullptr;
    }
    if(x->left != nullptr) {
        return find_max(x->left);
    }
    BNode<DataType> *y = x->parent;
    while(y != nullptr && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
 }
    BNode<DataType>* find_min(BNode<DataType>* p) 
    {
        while (p && p->left != nullptr) {
            p = p->left;
        }
        return p;
    }
    BNode<DataType>* find_max(BNode<DataType>* p) 
    {
        while (p && p->right != nullptr) {
            p = p->right;
        }
        return p;
    }
    void transplant(BNode<DataType>* u, BNode<DataType>* v) {
        if (u == nullptr) {
            return;
        }

        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;  // Correct the right child assignment
        }

        if (v != nullptr) {  // Only assign the parent if v is not null
            v->parent = u->parent;
        }
    }

     BNode<DataType>* inner_search(BNode<DataType>* p, const DataType &key) 
    {
        /*
        iterative:
        while(p != nullptr && key != p->data) {
            if(key < p->data) {
                p = p->left;
            } else {
                p = p->right
            }
            return p;
        }
        */
        if(p == nullptr || comp(key, p->data)== 0) {
            return p;
        }

        if(comp(key, p->data)== -1) {
            return inner_search(p->left, key);
        }else {
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
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
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
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    
    y->right = x;
    x->parent = y;
}
void inner_rb_insert(BNode<DataType>* z) {
    if (z == nullptr) {
        throw std::invalid_argument("Node to be inserted is null");
    }

    BNode<DataType>* y = &sentinel;
    BNode<DataType>* x = root;

    while (x != &sentinel) {
        y = x;

        if (x == nullptr) {
            throw std::runtime_error("Encountered a null node in the tree");
        }

        if (comp(z->data, x->data) == -1) {
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
    else {
        if (comp(z->data, y->data) == -1) {
            y->left = z;
        }
        else {
            y->right = z;
        }
    }

    z->left = &sentinel;
    z->right = &sentinel;
    z->is_red = true;
    rb_insert_fixup(z);
}

void rb_insert_fixup(BNode<DataType>* z) {
    while (z->parent->is_red) {
        if (z->parent == z->parent->parent->left) {
            BNode<DataType>* y = z->parent->parent->right;
            if (y->is_red) {
                z->parent->is_red = false;
                y->is_red = false;
                z->parent->parent->is_red = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(z);
                }
                z->parent->is_red = false;
                z->parent->parent->is_red = true;
                right_rotate(z->parent->parent);
            }
        } else {
            BNode<DataType>* y = z->parent->parent->left;
            if (y->is_red) {
                z->parent->is_red = false;
                y->is_red = false;
                z->parent->parent->is_red = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(z);
                }
                z->parent->is_red = false;
                z->parent->parent->is_red = true;
                left_rotate(z->parent->parent);
            }
        }
    }
    root->is_red = false;
}



public:
    BinTree(Compare compare = cmp_int, Func func=print_int) : comp(compare), func(func) 
    {
        sentinel.left = &sentinel;
        sentinel.right = &sentinel;
    }

    ~BinTree() 
    {
        delete_tree(root);
        root = nullptr;
    }

    void rb_insert(const DataType& data) {
        auto z = new BNode<DataType>(data, nullptr);
        if (root == &sentinel) {
            // Tree is empty, z becomes the root
            z->parent = &sentinel;
            root = z;
            root->is_red = false;  // Root must be black
            root->left = &sentinel;
            root->right = &sentinel;
        }
        else {
            inner_rb_insert(z);
        }
    }

    void visit_in_order() const 
    {
        inner_visit_in_order(root);
    }
    
    void visit_pre_order() const 
    {
        inner_visit_pre_order(root);
    }
    void visit_post_order() const 
    {
        inner_visit_post_order(root);
    }
    BNode<DataType>* search(const DataType &key) 
    {
        return inner_search(root, key);
    }
    std::vector<DataType> get_test_vector() 
    {
        std::vector<DataType> v;
        inner_get_test_vector(root, v);
        return v;
    }
};
/////////////////////////////////////////////////////////
 
#include "bintree_test.h"

 