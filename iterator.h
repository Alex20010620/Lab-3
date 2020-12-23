#pragma once

#include "_queue.h"
#include "_stack.h"
#include <iostream>

struct bft_iterator : public _iterator {
    bft_iterator(_tree* start) {
        if (start != nullptr) {
            current = start;
            node_storage.enqueue(start);
        } else {
            throw std::out_of_range("iterator is broken");
        }
    }

    int next() override {
        if (!node_storage.is_empty()) {
            current = node_storage.dequeue();
            if (current->left != nullptr) {
                node_storage.enqueue(current->left);
            }
            if (current->right != nullptr) {
                node_storage.enqueue(current->right);
            }
            return current->get_value();
        }
        else {
            current = nullptr;
            throw std::out_of_range("No more elements\n");
        }
    }

    bool has_next() override {
        return !node_storage.is_empty();
//        return current != nullptr;
    }

private:
    _tree* current = nullptr;
    _queue node_storage;
};



struct dft_iterator : public _iterator {
    dft_iterator(_tree* start) {
        current = start;
        if (current != nullptr) {
            node_storage.push(current);
        }
        else {
            throw std::out_of_range("this tree is empty\n");
        }
    }

    int next() override {
        if (first) {
            first = false;  // first element we have to pop
            return node_storage.pop()->get_value();
        }

        if (current->right != nullptr) {
            node_storage.push(current->right);
        }
        if (current->left != nullptr) {
            current = current->left;
        } else if (node_storage.get_size() > 0) {
            current = node_storage.pop();
        } else {
            current = nullptr;
            throw std::out_of_range("No more elements\n");
        }
        return current->get_value();
    }

    bool has_next() override {
//        return node_storage.get_size() > 0;
        return current != nullptr;
    }


private:
    _tree* current = nullptr;
    _stack node_storage;
    bool first = true;
};
