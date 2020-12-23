#include "_queue.h"

#include <iostream>

void _queue::enqueue(_tree* new_tree) {
    if (size == 0) {
        que_begin = new _node(new_tree);
        que_end = que_begin;
    } else {
        que_end->next = new _node(new_tree);
        que_end = que_end->next;
    }
    size++;
}

_tree* _queue::dequeue() {
    if (size == 0) {
        throw std::out_of_range("Cannot pop queue");
    } else if (size == 1) {
        size--;
        return que_begin->tnode;
    } else {
        _node* to_return = que_begin;
        que_begin = que_begin->next;
        size--;
        return to_return->tnode;
    }
}

int _queue::peek() const {
    if (size == 0) throw std::out_of_range("Queue is empty");
    return que_begin->tnode->get_value();
}

bool _queue::is_empty() const {
    return size == 0;
}

_queue::_queue() {}
