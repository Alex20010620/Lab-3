#include "_list.h"

#include <iostream>

#include "_iterator.h"
#include "_queue.h"
#include "_stack.h"

// _iterator

_iterator* _tree::create_bft_iterator() {
    return new bft_iterator(root);
}

_iterator* _tree::create_dft_iterator() {
    return new dft_iterator(root);
}

// _tree

_tree* _tree::find_node(int value) const {
    _tree* current_tree = (_tree*)this;
    int current_value = this->value;
    if (current_tree->left != nullptr) {
        if (current_tree->left->value == value) {
            do {
                if (current_tree->left->get_value() != value) break;
                current_tree = current_tree->left;
            } while (current_tree->left == nullptr);
            return current_tree;
        }
    }

    while (current_value != value) {
        if (current_tree == nullptr) break;
        current_value = current_tree->value;

        if (value > current_value) {
            current_tree = current_tree->right;
        } else if (value < current_value) {
            current_tree = current_tree->left;
        }
    }
    return current_tree;
}

bool _tree::contains(int value) const {
    if (find_node(value) != nullptr) {
        if (find_node(value)->value == value) return true;
    }
    return false;
}

_tree* _tree::find_left_leef(_tree* root) const {
    _tree* current = root;
    while(current->left != nullptr) {
        current = current->left;
    }

    return current;
}


// O(log N)
void _tree::insert(int value) {
    _tree* current = (_tree*)this;
    _tree* current_parent = current;
    while (true) {
        if (value <= current->value) {
            if (current->left == nullptr){
             // insertion
             current->left = new _tree(value, current_parent, root);
             break;
            }
            current = current->left;
            current_parent = current;

        } else if (value > current->value) {
            if (current->right == nullptr){
                // insertion
                current->right = new _tree(value, current_parent, root);
                break;
            }

            current = current->right;
            current_parent = current;
        }
    }
}

// don't forget about new node's parent
void _tree::remove(int value) {
    _tree* node_to_remove = find_node(value);
    if (node_to_remove == nullptr)
        throw std::runtime_error("There's no such node to delete");

    if (node_to_remove->left == nullptr && node_to_remove->right == nullptr) {      // removing leaf
        if (node_to_remove->parent == nullptr) {
            // root node
            delete node_to_remove;
        } else {
            if (value <= node_to_remove->parent->value) {
                node_to_remove->parent->left = nullptr;
            } else {
                node_to_remove->parent->right = nullptr;
            }
            delete node_to_remove;
        }
    } else if ((node_to_remove->left == nullptr && node_to_remove->right != nullptr) ||
            (node_to_remove->left != nullptr && node_to_remove->right == nullptr)) {
        // it has only one child or one subtree

        if (node_to_remove == node_to_remove->parent->left) {
            if (node_to_remove->left != nullptr) {
                node_to_remove->left->parent = node_to_remove->parent;
                node_to_remove->parent->left = node_to_remove->left;
            } else {
                node_to_remove->right->parent = node_to_remove->parent;
                node_to_remove->parent->left = node_to_remove->right;
            }
        } else {
            if (node_to_remove->left != nullptr) {
                node_to_remove->left->parent = node_to_remove->parent;
                node_to_remove->parent->right = node_to_remove->left;
            } else {
                node_to_remove->right->parent = node_to_remove->parent;
                node_to_remove->parent->right = node_to_remove->right;
            }
        }

        delete node_to_remove;
    } else {
        // the node has two children
        _tree* right_subtree_left_leaf = find_left_leef(node_to_remove->right);
        if (right_subtree_left_leaf == node_to_remove->right) {
            // if right subtree hasn't left leaf - we'll just change them
            node_to_remove->right->parent = node_to_remove->parent;

            if (node_to_remove == node_to_remove->parent->left) {
                node_to_remove->parent->left = node_to_remove->right;
            } else {
                node_to_remove->parent->right = node_to_remove->right;
            }

            delete node_to_remove;
        } else {
            node_to_remove->value = right_subtree_left_leaf->value;
            right_subtree_left_leaf->parent->left = nullptr;
            delete right_subtree_left_leaf;
        }
    }
}

int _tree::get_value() const {
    return value;
}

void _tree::clear_tree(_tree* to_delete) {
    if (to_delete != nullptr) {
        clear_tree(to_delete->left);
            to_delete->left = nullptr;
        //        if (to_delete->left != nullptr) {
//            if (to_delete == to_delete->parent->left)
//                to_delete->parent->left = nullptr;
//        }
        clear_tree(to_delete->right);
        to_delete->right = nullptr;
//        if (to_delete->parent != nullptr) {
//            if (to_delete == to_delete->parent->right)
//                to_delete->parent->right = nullptr;
//        }

        if (to_delete->parent != nullptr)
             delete to_delete;
    }
}
