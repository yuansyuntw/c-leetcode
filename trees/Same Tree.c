bool helper(struct TreeNode* p, struct TreeNode* q) {
    if ((p == NULL) && (q == NULL)) {
        return true;
    }
    
    if ((p != NULL) && (q != NULL))  {
        if (p->val == q->val) {
            bool isSameLeftChild = helper(p->left, q->left);
            if (!isSameLeftChild) {
                return false;
            }
            
            bool isSameRightChild = helper(p->right, q->right);
            return isSameRightChild;
        }
    }
    
    return false;
}


bool isSameTree(struct TreeNode* p, struct TreeNode* q){
    return helper(p, q);
}