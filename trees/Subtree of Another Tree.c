bool isSameTree(struct TreeNode* root, struct TreeNode* subRoot) {
    if ((root == NULL) || (subRoot == NULL)) {
        if ((root == NULL) && (subRoot == NULL)) {
        return true;
    }
        
        return false;
    }

    if (root->val != subRoot->val) {
        return false;
    }
    
    if (!isSameTree(root->left, subRoot->left)) {
       return false;
    }

    if (!isSameTree(root->right, subRoot->right)) {
        return false;
    }
    
    return true;
}

bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot) {
    if (root->val == subRoot->val) {
        if (isSameTree(root, subRoot)) {
            return true;
        }
    }
    
    if ((root->left != NULL) && isSubtree(root->left, subRoot)) {
        return true;
    }
    
    if ((root->right != NULL) && isSubtree(root->right, subRoot)) {
        return true;
    }
            
    return false;
}