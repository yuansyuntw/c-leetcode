/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool checkChildIsSymmetric(struct TreeNode *leftNode, struct TreeNode *rightNode) {
    if (leftNode->val != rightNode->val) {
        return false;
    }
    
    bool isSymmetric = true;
    if ((leftNode->left == NULL) && (rightNode->right == NULL)) {
        isSymmetric = true;
    } else if ((leftNode->left != NULL) && (rightNode->right != NULL)) {
        isSymmetric = checkChildIsSymmetric(leftNode->left, rightNode->right);
    } else {
        isSymmetric = false;
    }
    
    if (!isSymmetric) {
        return isSymmetric;
    }
    
    if ((leftNode->right == NULL) && (rightNode->left == NULL)) {
        isSymmetric = true;
    } else if ((leftNode->right != NULL) && (rightNode->left != NULL)) {
        isSymmetric = checkChildIsSymmetric(leftNode->right, rightNode->left);
    } else {
        isSymmetric = false;
    }
    
    return isSymmetric;
}


bool isSymmetric(struct TreeNode* root) {
    if ((root->left == NULL) && (root->right == NULL)) {
        return true;
    }
    
    if ((root->left != NULL) && (root->right != NULL)) {
        return checkChildIsSymmetric(root->left, root->right);
    }
    
    return false;
}