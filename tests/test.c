#include <stdio.h>
#include <gtest/gtest.h>
#include "vector.h"
#include "stack.h"
#include "queue.h"
#include "dict.h"
#include "hashtable.h"
#include "skiplist.h"
#include "avl-tree.h"
#include "bstree.h"
#include "binary-minheap.h"
#include "trie.h"

static int a[] = {
    11, 23, 35, 20, 
    2, -10, 330, -501,
    0, 25, 78, 0,
};

static int b[] = {
    29, 30, 50, 0,
    44, 600, -2, -90,
    5, -999, 60, 1000,
};

int LEN_A = sizeof(a) / sizeof(a[0]);
int LEN_B = sizeof(b) / sizeof(b[0]);

TEST(vector, testing_vector)
{
    int i;
    vectorElem x;
    vector_t vector;

    ASSERT_EQ(0, vector_new(&vector));
    for (i = 0; i < LEN_A; i++) {
        EXPECT_EQ(0, vector_append(vector, &a[i]));
    }

    EXPECT_EQ(0, vector_append(vector, &a[2]));
    EXPECT_EQ(0, vector_pop(vector, &x));

    EXPECT_EQ(LEN_A, vector_get_size(vector));

    for (i = 0; i < LEN_A; i++) {
        EXPECT_EQ(0, vector_get(vector, i, &x));
        EXPECT_EQ(a[i], *(int *)x);
    }

    EXPECT_EQ(0, vector_set(vector, 2, &a[1]));
    EXPECT_EQ(0, vector_set(vector, 0, &a[2]));
    EXPECT_EQ(-1, vector_set(vector, 15, &a[3]));

    EXPECT_FALSE(vector_isempty(vector));

    for (i = 0; i < LEN_A; i++) {
        EXPECT_EQ(0, vector_pop(vector, &x));
    }

    EXPECT_TRUE(vector_isempty(vector));
    vector_free(&vector);
}

TEST(stack, stack_testing) {
    int i;
    stackElem x;
    _stack_t stack;

    ASSERT_EQ(0, stack_new(&stack));
    for (i = 0; i < LEN_A; i++) {
        EXPECT_EQ(0, stack_push(stack, &a[i]));
    }

    EXPECT_EQ(0, stack_pop(stack, &x));
    EXPECT_EQ(0, stack_push(stack, &a[2]));
    EXPECT_EQ(0, stack_peek(stack, &x));
    EXPECT_EQ(a[2], *(int *) x);

    EXPECT_EQ(LEN_A, stack_get_size(stack));
    EXPECT_FALSE(stack_isempty(stack));

    for (i = 0; i < LEN_A; i++) {
        EXPECT_EQ(0, stack_pop(stack, &x));
    }

    EXPECT_EQ(-1, stack_pop(stack, &x));
    EXPECT_EQ(-1, stack_peek(stack, &x));
    EXPECT_TRUE(stack_isempty(stack));
    stack_free(&stack);
}

TEST(queue, queue_testing) {
    int i;
    queueElem x;
    queue_t queue;

    ASSERT_EQ(0, queue_new(&queue));
    for (i = 0; i < LEN_A; i++) {
        EXPECT_EQ(0, queue_push(queue, &a[i]));
    }

    EXPECT_EQ(0, queue_pop(queue, &x));
    EXPECT_EQ(0, queue_push(queue, &a[2]));
    EXPECT_EQ(0, queue_peek(queue, &x));
    EXPECT_EQ(a[1], *(int *) x);

    EXPECT_EQ(LEN_A, queue_get_size(queue));
    EXPECT_FALSE(queue_isempty(queue));

    for (i = 0; i < LEN_A; i++) {
        EXPECT_EQ(0, queue_pop(queue, &x));
    }

    EXPECT_EQ(-1, queue_pop(queue, &x));
    EXPECT_EQ(-1, queue_peek(queue, &x));
    EXPECT_TRUE(queue_isempty(queue));
    queue_free(&queue);
}

TEST(dict, dict_testing) {
    int i;
    dictKey x;
    dictValue y;
    dict_t dict;

    ASSERT_EQ(0, dict_new(&dict, NULL));
    for (i = 0; i < LEN_A; i++) {
        EXPECT_EQ(0, dict_add(dict, &a[i], &b[i]));
    }
    EXPECT_TRUE(dict_contains_key(dict, &a[0]));
    EXPECT_FALSE(dict_contains_key(dict, &b[0]));

    EXPECT_EQ(0, dict_remove(dict, &a[0]));
    EXPECT_FALSE(dict_contains_key(dict, &a[0]));

    for (i = 1; i < LEN_A; i++) {
        EXPECT_EQ(0, dict_get_value(dict, &a[i], &y));
        EXPECT_EQ(*(int *) y, b[i]);
    }

    dict_free(&dict);
}

TEST(hashtable, hashtable_testing) {
    int i;
    hashtableElem x;
    hashtable_t hashtable;

    ASSERT_EQ(0, hashtable_new(&hashtable, NULL));
    for (i = 0; i < LEN_A; i++) {
        EXPECT_EQ(0, hashtable_add(hashtable, &a[i]));
    }
    EXPECT_TRUE(hashtable_contains(hashtable, &a[0]));
    EXPECT_FALSE(hashtable_contains(hashtable, &b[0]));

    EXPECT_EQ(0, hashtable_remove(hashtable, &a[0]));
    EXPECT_FALSE(hashtable_contains(hashtable, &a[0]));

    for (i = 1; i < LEN_A; i++) {
        EXPECT_EQ(0, hashtable_remove(hashtable, &a[i]));
    }
    EXPECT_EQ(-1, hashtable_remove(hashtable, &a[1]));

    hashtable_free(&hashtable);
}

TEST(skiplist, skiplist_testing) {
    int i;
    skiplistElem x;
    skiplist_t skiplist;

    ASSERT_EQ(0, skiplist_new(&skiplist, NULL));
    for (i = 0; i < LEN_A; i++) {
        EXPECT_EQ(0, skiplist_add(skiplist, &a[i]));
    }
    EXPECT_TRUE(skiplist_contains(skiplist, &a[0]));
    EXPECT_FALSE(skiplist_contains(skiplist, &b[0]));

    EXPECT_EQ(0, skiplist_remove(skiplist, &a[0]));
    EXPECT_FALSE(skiplist_contains(skiplist, &a[0]));

    for (i = 1; i < LEN_A - 1; i++) {
        EXPECT_EQ(0, skiplist_remove(skiplist, &a[i]));
    }
    EXPECT_EQ(-1, skiplist_remove(skiplist, &a[LEN_A - 1]));    /* Duplicate value. */
    EXPECT_EQ(-1, skiplist_remove(skiplist, &a[1]));

    skiplist_free(&skiplist);
}

TEST(avl_tree, avltree_testing) {
    int i;
    avltreeElem x;
    avltree_t avl;

    ASSERT_EQ(0, avltree_new(&avl, NULL));
    for (i = 0; i < LEN_A; i++) {
        EXPECT_EQ(0, avltree_add(avl, &a[i]));
    }
    EXPECT_TRUE(avltree_contains(avl, &a[0]));
    EXPECT_FALSE(avltree_contains(avl, &b[0]));

    EXPECT_EQ(0, avltree_remove(avl, &a[0]));
    EXPECT_FALSE(avltree_contains(avl, &a[0]));

    EXPECT_FALSE(avltree_isempty(avl));

    EXPECT_EQ(0, avltree_get_min(avl, &x));
    EXPECT_EQ(-501, *(int *) x);

    EXPECT_EQ(0, avltree_get_max(avl, &x));
    EXPECT_EQ(330, *(int *) x);

    for (i = 1; i < LEN_A - 1; i++) {
        EXPECT_EQ(0, avltree_remove(avl, &a[i]));
    }
    EXPECT_EQ(-1, avltree_remove(avl, &a[LEN_A - 1]));
    EXPECT_EQ(-1, avltree_remove(avl, &a[1]));

    EXPECT_TRUE(avltree_isempty(avl));

    avltree_free(&avl);
}

TEST(bstree, bstree_testing) {
    int i;
    bstreeElem x;
    bstree_t bstree;

    ASSERT_EQ(0, bstree_new(&bstree, NULL));
    for (i = 0; i < LEN_A; i++) {
        EXPECT_EQ(0, bstree_add(bstree, &a[i]));
    }
    EXPECT_TRUE(bstree_contains(bstree, &a[0]));
    EXPECT_FALSE(bstree_contains(bstree, &b[0]));

    EXPECT_EQ(0, bstree_remove(bstree, &a[0]));
    EXPECT_FALSE(bstree_contains(bstree, &a[0]));

    EXPECT_FALSE(bstree_isempty(bstree));

    EXPECT_EQ(0, bstree_get_min(bstree, &x));
    EXPECT_EQ(-501, *(int *) x);

    EXPECT_EQ(0, bstree_get_max(bstree, &x));
    EXPECT_EQ(330, *(int *) x);

    for (i = 1; i < LEN_A - 1; i++) {
        EXPECT_EQ(0, bstree_remove(bstree, &a[i]));
    }
    EXPECT_EQ(-1, bstree_remove(bstree, &a[LEN_A - 1]));
    EXPECT_EQ(-1, bstree_remove(bstree, &a[1]));

    EXPECT_TRUE(bstree_isempty(bstree));

    bstree_free(&bstree);
}

TEST(binary_minheap, binary_minheap_testing) {
    int i;
    binaryMinHeapElem x;
    binary_minheap_t mh;    /* Min heap. */

    ASSERT_EQ(0, binary_minheap_new(&mh, LEN_A, NULL));
    for (i = 0; i < LEN_A; i++) {
        EXPECT_EQ(0, binary_minheap_add(mh, &a[i]));
    }

    EXPECT_FALSE(binary_minheap_isempty(mh));
    EXPECT_TRUE(binary_minheap_isfull(mh));

    EXPECT_EQ(0, binary_minheap_peek(mh, &x));
    EXPECT_EQ(-501, *(int *) x);

    EXPECT_EQ(0, binary_minheap_poll(mh, &x));
    EXPECT_EQ(-501, *(int *) x);

    EXPECT_EQ(0, binary_minheap_poll(mh, &x));
    EXPECT_EQ(-10, *(int *) x);

    EXPECT_EQ(LEN_A - 2, binary_minheap_get_size(mh));

    for (i = 1; i < LEN_A - 1; i++) {
        EXPECT_EQ(0, binary_minheap_poll(mh, &x));
    }

    EXPECT_EQ(-1, binary_minheap_poll(mh, &x));
    EXPECT_EQ(0, binary_minheap_get_size(mh));

    EXPECT_TRUE(binary_minheap_isempty(mh));
    EXPECT_FALSE(binary_minheap_isfull(mh));

    binary_minheap_free(&mh);
}

static const char *str[] = {
        "hello", "world", "this",
        "is", "an", "simple",
        "example", "exam", "he",
};

TEST(trie, trie_testing) {
    int i, len;
    trie_t trie;

    len = sizeof(str) / sizeof(str[0]);
    ASSERT_EQ(0, trie_new(&trie));

    for (i = 0; i < len; ++i) {
        EXPECT_EQ(0, trie_add(trie, str[i]));
    }

    for (i = 0; i < len; ++i) {
        EXPECT_TRUE(trie_contains(trie, str[i]));
    }
    EXPECT_FALSE(trie_contains(trie, "what"));
    EXPECT_FALSE(trie_contains(trie, "how"));

    EXPECT_TRUE(trie_startswith(trie, "worl"));
    EXPECT_TRUE(trie_startswith(trie, "exam"));
    EXPECT_TRUE(trie_startswith(trie, "sim"));
    EXPECT_FALSE(trie_startswith(trie, "she"));

    trie_free(&trie);
}

int main (int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
