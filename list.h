#pragma once

struct _node;

struct _iterator {
    virtual int next() = 0;
    virtual bool has_next() = 0;
};

class _tree {
    int value = 0;

    _tree* find_left_leef(_tree* root) const;
    _tree* find_node(int value) const;
//    _tree* find_parent();
    void clear_tree(_tree* to_delete);
public:
    _tree* left = nullptr;
    _tree* right = nullptr;
    _tree* parent = nullptr;
    _tree* root = nullptr;


    _tree(int value, _tree* parent = nullptr, _tree* _root = nullptr) {
        this->value = value;
        this->parent = parent;
        if (_root == nullptr) {
            root = this;
        } else {
            root = _root;
        }
    }

    ~_tree() {
        if (parent == nullptr && (left != nullptr || right != nullptr))
            clear_tree(root);
    }

    bool contains(int value) const;

    // O(log N)
    void insert(int value);
    void remove(int value);

    int get_value() const;

    _iterator* create_dft_iterator();    // depth-first traverse
    _iterator* create_bft_iterator();    // breadth-first traverse
};


struct _node {
    _tree* tnode = nullptr;
    _node* next = nullptr;

    _node(_tree* _tnode, _node* _next = nullptr) {
        tnode = _tnode;
        next = _next;
    }
};

