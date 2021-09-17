/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isValidBSTForBranch(struct TreeNode* root, bool isCheckedMinVal, int minVal, bool isCheckedMaxVal, int maxVal){
    bool isValid = true;
    
    if (isValid && isCheckedMinVal && (root->val <= minVal)) {
        isValid = false;
    }
    if (isValid && isCheckedMaxVal && (root->val >= maxVal)) {
        isValid = false;
    }
    
    if (isValid && (root->left != NULL)) {
        isValid = isValidBSTForBranch(root->left, isCheckedMinVal, minVal, true, root->val);
    }
    if (isValid && (root->right != NULL)) {
        isValid = isValidBSTForBranch(root->right, true, root->val, isCheckedMaxVal, maxVal);
    }
    
    return isValid;
}

bool isValidBST(struct TreeNode* root) {
    bool isValid = true;
    
    if (isValid && (root->left != NULL) && (root->left->val >= root->val)) {
        isValid = false;
    }
    if (isValid && (root->right != NULL) && (root->right->val <= root->val)) {
        isValid = false;
    }
    
    if (isValid && (root->left != NULL)) {
        isValid = isValidBSTForBranch(root->left, false, 0, true, root->val);
    }
    if (isValid && (root->right != NULL)) {
        isValid = isValidBSTForBranch(root->right, true, root->val, false, 0);
    }
    
    return isValid;
}