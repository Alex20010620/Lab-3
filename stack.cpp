#include "_stack.h"

#include <iostream>

void _stack::push(_tree* new_tree) {
    if (size == 0) {
        head = new _node(new_tree);
    } else {
        head = new _node(new_tree, head);
    }
    size++;
}

_tree* _stack::pop() {
    if (size > 0) {
        _node* to_return = head;
        head = head->next;
        size--;
        return to_return->tnode;
    } else {
        throw std::out_of_range("Stack is empty. Cannot pop.");
    }
}

_tree* _stack::top() const {
    if (size == 0)
        throw std::out_of_range("Stack is empty");

    return head->tnode;
}