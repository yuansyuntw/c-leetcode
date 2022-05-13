/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

// struct TreeNode* 

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {    
    if ((root->left != NULL) && (p->val < root->val) && (q->val < root->val)) {
        return lowestCommonAncestor(root->left, p, q);
    }
            
    if ((root->right != NULL) && (p->val > root->val) && (q->val > root->val)) {
        return lowestCommonAncestor(root->right, p, q);
    }
    
    // When we split the dsp path, the node is the LCA
    return root;
}