/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void insertNode(struct TreeNode* root, int value) {
    if (value < root->val) {
        if (root->left == NULL) {
            root->left = malloc(sizeof(struct TreeNode) * 1);
            root->left->val = value;
            root->left->left = NULL;
            root->left->right = NULL;
        } else {
            insertNode(root->left, value);
        }
    } else {
        if (root->right == NULL) {
            root->right = malloc(sizeof(struct TreeNode) * 1);
            root->right->val = value;
            root->right->left = NULL;
            root->right->right = NULL;
        } else {
            insertNode(root->right, value);
        }
    }
}

void pickMiddleNumber(struct TreeNode* root, int* nums, int startIndex, int endIndex) {
    if (endIndex < startIndex) {
        return;
    }
    
    int middleIndex = (startIndex + endIndex)/2;
    insertNode(root, nums[middleIndex]);
    
    pickMiddleNumber(root, nums, startIndex, middleIndex - 1);
    pickMiddleNumber(root, nums, middleIndex + 1, endIndex);
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    int middleIndex = (numsSize-1)/2;
    
    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    root->val = nums[middleIndex];
    root->left = NULL;
    root->right = NULL;
    
    pickMiddleNumber(root, nums, 0, middleIndex - 1);
    pickMiddleNumber(root, nums, middleIndex + 1, numsSize - 1);
    
    return root;
}