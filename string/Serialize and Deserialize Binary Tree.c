
void helper(struct TreeNode* root, char* buffer, int maxLegth) {
    if (root == NULL) return;
    
    if (strlen(buffer) >= maxLegth) {
        printf("the buffer size is out of range\n");
        return;
    }
    
    char* appendString = calloc(sizeof(char), 7);
    sprintf(appendString, " %d", root->val);
    strcat(buffer, appendString);
    
    if (root->left != NULL) {
        helper(root->left, buffer, maxLegth);
    } else {
        strcat(buffer, " n");
    }
    
    if (root->right != NULL) {
        helper(root->right, buffer, maxLegth);
    } else {
        strcat(buffer, " n");
    }
}

struct TreeNode* getNode(char* data) {
    char* found = strtok(data, " ");
    if (found == NULL) return NULL;
    
    if ((strlen(found) == 1) && (found[0] == 'n')) {
        return NULL;
    }
    
    struct TreeNode *result = calloc(sizeof(struct TreeNode), 1);
    sscanf(found, "%d", &result->val);
    result->left = getNode(NULL);
    result->right = getNode(NULL);
    
    return result;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/** Encodes a tree to a single string. */
char* serialize(struct TreeNode* root) {
    int bufferSize = 10000*5;
    char* buffer = calloc(sizeof(char), bufferSize);
    helper(root, buffer, bufferSize);
    return buffer;
}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data) {
    return getNode(data);
}

// Your functions will be called as such:
// char* data = serialize(root);
// deserialize(data);