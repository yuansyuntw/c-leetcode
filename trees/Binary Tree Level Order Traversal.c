/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int getLevelOrder(struct TreeNode** nodes, int nodesCount, int depth, int** nodeLists, int** returnColumnSizes){
    if (nodesCount == 0) {
        free(nodes);
        return depth;
    }
    
    depth += 1;
    nodeLists[depth] = malloc(sizeof(int) * nodesCount);
    returnColumnSizes[0][depth] = nodesCount;

    struct TreeNode** childNodes = malloc(sizeof(struct TreeNode*) * 2000);
    int childNodesCount = 0;
    for(int i=0; i<nodesCount; i++) {
        if (nodes[i]->left != NULL) {
            childNodes[childNodesCount++] = nodes[i]->left;
        }
        
        if (nodes[i]->right != NULL) {
            childNodes[childNodesCount++] = nodes[i]->right;
        }
        
        nodeLists[depth][i] = nodes[i]->val;
    }
    
    free(nodes);
    
    return getLevelOrder(childNodes, childNodesCount, depth, nodeLists, returnColumnSizes);
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
    
    nodeLists = malloc(sizeof(int*) * nodeListsCount);
    *returnColumnSizes = malloc(sizeof(int) * nodeListsCount);
    for (int i=0; i<nodeListsCount; i++) {
        *(*(returnColumnSizes) + i) = 0;
    }
    
    // depth = 0
    nodeLists[0] = malloc(sizeof(int) * 1);
    nodeLists[0][0] = root->val;
    returnColumnSizes[0][0] = 1;
    
    struct TreeNode** childNodes = malloc(sizeof(struct TreeNode*) * 2);
    int childNodesCount = 0;
    if (root->left != NULL) {
        childNodes[childNodesCount++] = root->left;
    }
    
    if (root->right != NULL) {
        childNodes[childNodesCount++] = root->right;
    }
    
    *returnSize = getLevelOrder(childNodes, childNodesCount, 0, nodeLists, returnColumnSizes) + 1;
    
    return nodeLists;
}