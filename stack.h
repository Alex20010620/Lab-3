#pragma once

#include "_list.h"

class _stack {
    _node* head = nullptr;
    unsigned size = 0;
public:
    _stack(_tree* start) {
        head = new _node(start);
        size = 1;
    }

    _stack() {}

    ~_stack() {
        _node* current = head;
        while(current != nullptr && size > 0) {
            _node* to_delete = current;
            current = current->next;
            delete to_delete;
            size--;
        }
    }

    void push(_tree* new_node);

    _tree* pop();
    _tree* top() const;

    unsigned get_size() const { return size;}
};
