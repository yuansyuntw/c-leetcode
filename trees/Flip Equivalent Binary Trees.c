/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isEqual(struct TreeNode* node1, struct TreeNode* node2) {
    if ((node1 == NULL) || (node2 == NULL)) {
        bool areEmpty = (node1 == node2);
        if (areEmpty) {
            return true;
        }
        
        return false;
    }
    
    bool areSame = (node1->val == node2->val);
    return areSame;
}

bool flipEquiv(struct TreeNode* root1, struct TreeNode* root2){
    if ((root1 == NULL) || (root2 == NULL)) {
        if (root1 == root2) {
            return true;
        }
        
        return false;
    }
    
    bool isDifferentValue = (root1->val != root2->val);
    if (isDifferentValue) {
        return false;
    }
    
    // no-flip
    bool isSameChilds = (isEqual(root1->left, root2->left) && isEqual(root1->right, root2->right));
    if (isSameChilds) {
        bool isLeftEquivalent = flipEquiv(root1->left, root2->left);
        bool isRightEquivalent = flipEquiv(root1->right, root2->right);
        if (isLeftEquivalent && isRightEquivalent) {
            return true;
        }
    }
    
    // flip
    bool isCanFlip = (isEqual(root1->left, root2->right) && isEqual(root1->right, root2->left));
    if (isCanFlip) {
         bool isLeftEquivalent = flipEquiv(root1->left, root2->right);
        if (!isLeftEquivalent) {
            return false;
        }
        
        bool isRightEquivalent = flipEquiv(root1->right, root2->left);
        if (!isRightEquivalent) {
            return false;
        }
        
        return true;
    }
    
    return false;
}