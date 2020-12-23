#include <exception>
#include "../_iterator.h"
#include "../_stack.h"
#include "../_queue.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using std::vector;

TEST(stack_test, stack) {
    _tree* tree = new _tree(100);
    tree->insert(10);
    tree->insert(150);

    _stack stack1(tree->left);
    stack1.push(tree);
    stack1.push(tree->right);

    ASSERT_EQ(stack1.pop()->get_value(), 150);
    ASSERT_EQ(stack1.pop()->get_value(), 100);
    ASSERT_EQ(stack1.pop()->get_value(), 10);

    stack1.push(tree->root);
    tree->insert(130);
    stack1.push(tree->root->right->left);
    ASSERT_EQ(stack1.pop()->get_value(), 130);
    ASSERT_EQ(stack1.pop()->get_value(), 100);

    ASSERT_THROW(stack1.pop(), std::out_of_range);
    ASSERT_THROW(stack1.top(), std::out_of_range);

    delete tree;
}


TEST(queue_test, queue) {
    _tree* tree = new _tree(100);
    tree->insert(10);
    tree->insert(150);

    _queue queue(tree->left);
    queue.enqueue(tree);
    queue.enqueue(tree->right);

    ASSERT_EQ(queue.dequeue()->get_value(), 10);
    ASSERT_EQ(queue.dequeue()->get_value(), 100);
    ASSERT_EQ(queue.dequeue()->get_value(), 150);

    queue.enqueue(tree->root);
    tree->insert(130);
    queue.enqueue(tree->root->right->left);
    ASSERT_EQ(queue.dequeue()->get_value(), 100);
    ASSERT_EQ(queue.dequeue()->get_value(), 130);

    ASSERT_THROW(queue.dequeue(), std::out_of_range);
    ASSERT_THROW(queue.peek(), std::out_of_range);

    delete tree;
}


TEST(tree_test, iterators) {
    _tree* tree = new _tree(10);
    tree->insert(20);
    tree->insert(10);
    tree->insert(5);
    tree->insert(7);
    tree->insert(25);

    ASSERT_EQ(tree->root->get_value(), 10);
    ASSERT_EQ(tree->parent, nullptr);

    // bft
    bft_iterator* runner_bft = (bft_iterator*)tree->create_bft_iterator();
    ASSERT_EQ(runner_bft->next(), 10);
    ASSERT_EQ(runner_bft->next(), 10);
    ASSERT_EQ(runner_bft->next(), 20);
    ASSERT_EQ(runner_bft->next(), 5);
    ASSERT_EQ(runner_bft->next(), 25);
    ASSERT_EQ(runner_bft->next(), 7);

    // dft
    dft_iterator* runner_dft = (dft_iterator*)tree->create_dft_iterator();
    ASSERT_EQ(runner_dft->next(), 10);
    ASSERT_EQ(runner_dft->next(), 10);
    ASSERT_EQ(runner_dft->next(), 5);
    ASSERT_EQ(runner_dft->next(), 7);
    ASSERT_EQ(runner_dft->next(), 20);
    ASSERT_EQ(runner_dft->next(), 25);


//     there's no such element
    ASSERT_THROW(tree->remove(-10000), std::runtime_error);

    delete runner_bft;
    delete runner_dft;
    delete tree;
}

TEST(tree_test, insertions) {
    _tree* tree = new _tree(10);
    tree->insert(10);
    tree->remove(10);

    ASSERT_EQ(tree->left, nullptr);

    tree->insert(20);
    tree->insert(30);

    ASSERT_EQ(tree->right->get_value(), 20);
    ASSERT_EQ(tree->right->right->get_value(), 30);

    tree->remove(20);

    ASSERT_EQ(tree->right->get_value(), 30);


    // 15 -(r) 10 -(l) 10 -(l) 10
    tree->insert(10);
    tree->insert(5);
    tree->insert(8);

    tree->remove(5);

    ASSERT_EQ(tree->left->left->get_value(), 8);

    delete tree;
}

TEST(tree_test, contains_test) {
    _tree* tree = new _tree(10);
    tree->insert(100);

    ASSERT_TRUE(tree->contains(10));
    ASSERT_TRUE(tree->contains(100));
    tree->remove(100);
    ASSERT_FALSE(tree->contains(100));
    ASSERT_FALSE(tree->contains(200));
    tree->insert(10);
    tree->insert(5);
    tree->insert(8);
    tree->insert(7);
    tree->insert(6);
    tree->insert(3);
    tree->insert(2);
    tree->insert(1);
    tree->insert(4);
    tree->insert(9);

    for (int i = 1; i < 11; i++)
        ASSERT_TRUE(tree->contains(i));


    delete tree;
}