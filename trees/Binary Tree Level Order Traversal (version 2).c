/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int getLevelOrder(struct TreeNode* root, int depth, int** nodeLists, int** returnColumnSizes){
    if (root == NULL) {
        return depth;
    }
    
    int columnSizesIndex = *((*returnColumnSizes) + depth);
    nodeLists[depth][columnSizesIndex] = root->val;
    
    columnSizesIndex++;
    *((*returnColumnSizes) + depth) = columnSizesIndex;
    
    int leftDepth = getLevelOrder(root->left, depth+1, nodeLists, returnColumnSizes);
    int rightDepth = getLevelOrder(root->right, depth+1, nodeLists, returnColumnSizes);
    
    if (leftDepth > rightDepth) {
        return leftDepth;
    } else {
        return rightDepth;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    int** nodeLists = NULL;
    if (root == NULL) {
        *returnSize = 0;
        return nodeLists;
    }
    
    int nodeListsCount = 2000;
    
    nodeLists = (int**) malloc(sizeof(int*) * nodeListsCount);
    *returnColumnSizes = malloc(sizeof(int) * nodeListsCount);
    
    for (int i=0; i<nodeListsCount; i++) {
        int count = 2000;
        if (i<=10) {
            count = (int)pow(2, i);
        }

        nodeLists[i] = malloc(sizeof(int) * count);
        *(*(returnColumnSizes) + i) = 0;
    }
    
    *returnSize = getLevelOrder(root, 0, nodeLists, returnColumnSizes);
    
    return nodeLists;
}