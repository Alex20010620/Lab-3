#pragma once

#include "_list.h"

class _queue {
    _node* que_begin = nullptr;
    _node* que_end = nullptr;

    unsigned size = 0;
public:
    _queue(_tree* start) {
        que_begin = new _node(start);
        que_end = que_begin;
        size = 1;
    }

    _queue();

    ~_queue() {
        _node* current = que_begin;
        while(current != nullptr && size > 0) {
            _node* to_delete = current;
            current = current->next;
            delete to_delete;
            size--;
        }

    }

    void enqueue(_tree* new_tree);
    _tree* dequeue();

    int peek() const;
    bool is_empty() const;
};
