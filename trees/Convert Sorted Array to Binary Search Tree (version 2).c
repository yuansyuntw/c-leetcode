/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int maxDepth(struct TreeNode* root){
    if (root == NULL) {
        return 0;
    }
    
    int depth = 1;
    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);
    
    if (leftDepth > rightDepth) {
        depth += leftDepth;
    } else {
        depth += rightDepth;
    }
    
    return depth;
}

struct TreeNode* checkTheBalance(struct TreeNode* root) {
    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);

    if (rightDepth - leftDepth > 1) {
        struct TreeNode* tempRoot = root;
        root = root->right;
        
        struct TreeNode* tempLeft = root->left;
        root->left = tempRoot;
        root->left->right = tempLeft;
        
        root = checkTheBalance(root);
    } else {
        if (leftDepth > 1) {
            root->left = checkTheBalance(root->left);
        }
        
        if (rightDepth > 1) {
            root->right = checkTheBalance(root->right);
        }
    }
    
    return root;
}

void insertNode(struct TreeNode* root, int value) {
    if (root->val > value) {
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

struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    root->val = nums[0];
    root->left = NULL;
    root->right = NULL;
    
    for(int i=1; i<numsSize; i++) {
        insertNode(root, nums[i]);
        root = checkTheBalance(root);
    }
    
    return root;
}