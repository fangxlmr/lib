/*
 * 二叉排序树(bstree)的代码实现
 *
 * 节点的添加、查找与删除的方法
 * 有递归与非递归，在本库中均有实现。
 * 默认使用可靠性更好的非递归迭代版本。
 */

#include <stdlib.h>
#include "bstree.h"
/*
 * 判断a, b大小，返回较大值。
 */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/*
 * 节点结构
 */
typedef struct _BSTreeNode BSTreeNode;

struct _BSTreeNode {
    BSTreeValue data;
    BSTreeNode *left;
    BSTreeNode *right;
};

/*
 * 二叉排序树
 */
struct _BSTree {
    BSTreeNode *root;           /* 根节点 */
    BSTreeCompareFunc cmp;  /* 节点大小比较函数 */
};

BSTree *bstree_new(BSTreeCompareFunc cmp)
{
    BSTree *bstree;

    bstree = (BSTree *) malloc(sizeof(BSTree));

    if (!bstree) {
        return BSTREE_NULL;
    }

    bstree->root = NULL;
    bstree->cmp  = cmp;

    return bstree;
}

/**
 * subtree_free     销毁子树
 *
 * @param root      子树根节点
 */
static void subtree_free(BSTreeNode *root)
{
    if (!root) {
        return;
    }
    /*
     * 分别销毁左右子树
     */
    subtree_free(root->left);
    subtree_free(root->right);
    /*
     * 释放当前节点
     */
    free(root);
}

void bstree_free(BSTree *bstree)
{
    subtree_free(bstree->root);
    free(bstree);
}

/**
 * subtree_add      向子树中添加元素value
 *
 * @param root      子树根节点的二级指针
 * @param value     带添加的元素
 * @param cmp       节点元素比较大小函数
 * @return          添加成功，则返回非0值，
 *                  添加失败（内存分配失败，
 *                  或已存在该节点）则返回0。
 */
static int subtree_add(BSTreeNode **root,
                       BSTreeValue value,
                       BSTreeCompareFunc cmp)
{
    BSTreeNode *new_node;

    /*
     * 非递归查找添加，系统性能更好
     */
    while (*root != NULL && cmp(value, (*root)->data)) {
        /* 查找左子树 */
        if (cmp(value, (*root)->data) < 0) {
            root = &(*root)->left;

            /* 查找右子树 */
        } else {
            root = &(*root)->right;
        }
    }

    if (*root != NULL) {
        /* 忽略重复值 */
        return 0;

        /*
         * 不存在匹配节点，则
         * 新建节点，并添加进二叉树
         */
    } else {
        new_node = (BSTreeNode *) malloc(sizeof(BSTreeNode));

        if (!new_node) {   /* 内存分配失败 */
            return 0;
        }

        /* 新节点 */
        new_node->data  = value;
        new_node->left  = NULL;
        new_node->right = NULL;

        *root = new_node;  /* 插入 */
        return 1;
    }


    /*
     * 递归查找，增加系统开销，且大数据量时可能造成栈溢出
     */
//    /*
//     * 没有匹配的节点，新建节点，并插入二叉排序树
//     */
//    if (!*root) {
//        new_node = (BSTreeNode *) malloc(sizeof(BSTreeNode));
//
//        if (!new_node) {   /* 内存分配失败 */
//            return 0;
//        }
//
//        /* 新节点 */
//        new_node->data  = value;
//        new_node->left  = NULL;
//        new_node->right = NULL;
//
//        *root = new_node;  /* 插入 */
//        return 1;
//    }
//
//    if (cmp(value, (*root)->data) == 0) {
//        return 0;     /* 忽略重复值 */
//
//    /* 查找左子树 */
//    } else if (cmp(value, (*root)->data) < 0) {
//        subtree_add(&(*root)->left, value, cmp);
//
//    /* 查找右子树 */
//    } else {
//        subtree_add(&(*root)->right, value, cmp);
//    }
}

int bstree_add(BSTree *bstree, BSTreeValue value)
{
    return subtree_add(&bstree->root, value, bstree->cmp);
}

/**
 * subtree_find     查找子树中是否存在节点值等于value
 *
 * @param root      子树根节点
 * @param value     待查找的元素
 * @param cmp       节点元素比较函数
 * @return          若子树中含有元素value，则返回非0值，
 *                  否则返回0。
 */
static int subtree_find(BSTreeNode *root,
                        BSTreeValue value,
                        BSTreeCompareFunc cmp)
{
    /*
     * 非递归查找，系统性能更好
     */
    while (root != NULL && cmp(value, root->data) != 0) {
        /* 继续查找左子树 */
        if (cmp(value, root->data) < 0) {
            root = root->left;

            /* 继续查找右子树 */
        } else {
            root = root->right;
        }
    }

    /*
     * 没有匹配值，返回0，
     * 存在匹配值，返回1
     */
    return root != NULL;


    /*
     * 递归查找，增加系统开销，
     * 且当数据量过大时，可能造成栈溢出
     */
//    if (!root) {
//        return 0;
//    }
//
//    if (cmp(value, root->data) == 0) {
//        return 1;
//
//    } else if (cmp(value, root->data) < 0) {
//        return subtree_find(root->left, value, cmp);
//
//    } else {
//        return subtree_find(root->right, value, cmp);
//    }
}

int bstree_find(BSTree *bstree, BSTreeValue value)
{
    return subtree_find(bstree->root, value, bstree->cmp);
}

/**
 * delete_node      删除二叉排序树中的单个节点
 *
 * @param node      待删除节点的二级指针
 *
 * @note            需要处理三种不同的节点位置情况
 *                  [1]  左孩子为空
 *                  [2]  右孩子为空
 *                  [3]  左右孩子都不空
 */
static void delete_node(BSTreeNode **node) {
    BSTreeNode *p, *q;

    /* [1] */
    if (!(*node)->left) {
        p = *node;
        *node = p->right;
        free(p);

     /* [2] */
    } else if (!(*node)->right) {
        p = *node;
        *node = p->left;
        free(p);

    /* [3] */
    } else {
        p = *node;  /* 保存当前节点指针 */

        /* 转左孩子，找到待删除节点的直接前驱 */
        q = p->left;
        while (q->right) {
            p = q;
            q = q->right;
        }
        /*
         * 将直接前驱的值复制到带删除节点，
         * 就相当于删除了待删除节点。
         */
        (*node)->data = q->data;

        /*
         * 处理直接前驱的子树。
         *
         * 如果p与*node指向相同，则重接p的左子树。
         * 此种情况为，待删除节点的左孩子没有右子树，
         * 直接前驱就为左孩子本身。
         * 则将直接前驱的左孩子重接到待删除节点的左孩子处。
         */
        if (p == *node) {
            p->left = q->left;
            free(q);

        /*
         * 如果p与*node的指向不同，则重接p的右子树。
         * 此种情况为，待删除节点的左孩子存在右子树，
         * 直接前驱不是左孩子。
         * 则将直接前驱的左孩子重接到直接前驱父节点的右孩子处。
         */
        } else {
            p->right = q->left;
            free(q);
        }
    }
}
/**
 * subtree_del      删除子树中元素值等于value的节点
 *
 * @param root      子树根节点的二级指针
 * @param value     目标元素值
 * @param cmp       节点元素比较大小函数
 * @return          删除成功，则返回非0值，
 *                  没有匹配值，则返回0。
 */
static int subtree_del(BSTreeNode **root,
                        BSTreeValue value,
                        BSTreeCompareFunc cmp)
{
    /*
     * 非递归查找，系统性能更好
     */
    while (*root != NULL && cmp(value, (*root)->data) != 0) {
        /* 继续查找左子树 */
        if (cmp(value, (*root)->data) < 0) {
            root = &(*root)->left;

            /* 继续查找右子树 */
        } else {
            root = &(*root)->right;
        }
    }

    if (*root != NULL) {
        /* 找到匹配值，删除之 */
        delete_node(root);
        return 1;

        /* 没有匹配值 */
    } else {
        return 0;
    }

      /*
       * 递归查找删除，增加系统开销，
       * 且当数据量大时，可能造成栈溢出。
       */

//    /*
//     * 不存在值为value的节点
//     */
//    if (!*root) {
//        return 0;
//    }
//
//    if (cmp(value, (*root)->data) == 0) {
//        /*
//         * 节点匹配，删除之
//         */
//        delete_node(root);
//        return 1;
//        /*
//         * 查找左子树
//         */
//    } else if (cmp(value, (*root)->data) < 0) {
//        subtree_del(&(*root)->left, value, cmp);
//        /*
//         * 查找右子树
//         */
//    } else {
//        subtree_del(&(*root)->right, value, cmp);
//    }
}

int bstree_del(BSTree *bstree, BSTreeValue value)
{
    return subtree_del(&bstree->root, value, bstree->cmp);
}

/**
 * subtree_depth    求子树的高度
 *
 * @param root      子树根节点
 * @return          若子树为空，则返回0，
 *                  若子树不空，返回子树的高度。
 */
static int subtree_depth(BSTreeNode *root)
{
    if (!root)
        return 0;
    /*
     * 当前子树的高度为左右子树的最大值 + 1
     */
    return MAX(subtree_depth(root->left), subtree_depth(root->right)) + 1;
}

int bstree_depth(BSTree *bstree)
{
    return subtree_depth(bstree->root);
}

int bstree_is_empty(BSTree *bstree)
{
    return bstree->root == NULL;
}

BSTreeValue bstree_min(BSTree *bstree)
{
    BSTreeNode *node;

    node = bstree->root;

    /* 向左，查找最小值 */
    while (node != NULL && node->left != NULL) {
        node = node->left;
    }

    /* 空树 */
    if (!node) {
        return BSTREE_NULL;

        /* 树非空，存在最小值*/
    } else {
        return node->data;
    }
}

BSTreeValue bstree_max(BSTree *bstree)
{
    BSTreeNode *node;

    node = bstree->root;

    /* 向右，查找最大 值 */
    while (node != NULL && node->right != NULL) {
        node = node->right;
    }

    /* 空树 */
    if (!node) {
        return BSTREE_NULL;

        /* 树非空，存在最大值*/
    } else {
        return node->data;
    }

}
