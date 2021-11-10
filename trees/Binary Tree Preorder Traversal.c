/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void getPreorderList(struct TreeNode* node, int* preorderValueList, int* index) {
    if (node != NULL) {
        preorderValueList[*index] = node->val;
        *index = *index + 1;
        
        if (node->left != NULL) {
            getPreorderList(node->left, preorderValueList, index);
        }

        if (node->right != NULL) {
            getPreorderList(node->right, preorderValueList, index);
        }
    }
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorderTraversal(struct TreeNode* root, int* returnSize){
    int* preorderValueList = malloc(sizeof(int) * 100);
    *returnSize = 0;
    
    getPreorderList(root, preorderValueList, returnSize);
    
    return preorderValueList;
    
}