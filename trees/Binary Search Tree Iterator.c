/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct
{
    int stackCount;
    struct TreeNode **stack;
} BSTIterator;

void dfs(BSTIterator *iterator, struct TreeNode *node)
{
    iterator->stack[iterator->stackCount++] = node;

    if (node->left != NULL)
    {
        dfs(iterator, node->left);
    }
}

BSTIterator *bSTIteratorCreate(struct TreeNode *root)
{
    BSTIterator *iterator = (BSTIterator *)calloc(1, sizeof(BSTIterator));
    iterator->stackCount = 0;
    iterator->stack = (struct TreeNode **)calloc(100000, sizeof(struct TreeNode *));

    dfs(iterator, root);

    return iterator;
}

int bSTIteratorNext(BSTIterator *obj)
{
    if (obj->stackCount <= 0)
    {
        printf("something wrong\n");
        return 0;
    }

    struct TreeNode *node = obj->stack[obj->stackCount - 1];
    int result = node->val;
    obj->stackCount--;

    if (node->right != NULL)
    {
        dfs(obj, node->right);
    }

    return result;
}

bool bSTIteratorHasNext(BSTIterator *obj)
{
    return (obj->stackCount > 0);
}

void bSTIteratorFree(BSTIterator *obj)
{
    free(obj->stack);
}