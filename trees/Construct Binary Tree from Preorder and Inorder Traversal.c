/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct Item {
    int key;
    int value;
    struct Item* nextItem;
};

int* g_preorder;
int g_preorderSize;
int* g_inorder;
int g_inorderSize;

int g_preorderSeenCount;

int g_inorderItemTableSize;
struct Item** g_inorderItemTable;

int getHashkey(int key) {
    return (key + 3000);
}

void addItem(int key, int value) {
    int index = getHashkey(key) % g_inorderItemTableSize;
    
    struct Item* item = g_inorderItemTable[index];
    struct Item* lastItem = NULL;
    while(item != NULL) {
        if (item->key == key) {
            return;
        }
        
        lastItem = item;
        item = item->nextItem;
    }
    
    struct Item *newItem = malloc(sizeof(struct Item));
    newItem->key = key;
    newItem->value = value;
    newItem->nextItem = NULL;
    
    if (lastItem == NULL) {
        g_inorderItemTable[index] = newItem;
    } else {
        lastItem->nextItem = newItem;
    }
}

int getValue(int key) {
    int index = getHashkey(key) % g_inorderItemTableSize;
    
    struct Item* item = g_inorderItemTable[index];
    while(item != NULL) {
        if (item->key == key) {
            return item->value;
        }
        
        item = item->nextItem;
    }
    
    return -1;
}

struct TreeNode* findRoot(int startIndex, int endIndex) {
    if (startIndex > endIndex) {
        return NULL;
    }
    
    if ((startIndex < 0) || (startIndex >= g_inorderSize)) {
        return NULL;
    }
    
    if ((endIndex < 0) || (endIndex >= g_inorderSize)) {
        return NULL;
    }
    
    // the preorder list decide the root value
    int rootValue = g_preorder[g_preorderSeenCount++];
    
    // the inorder index decide the node wheather it has childs.
    int rootInorderIndex = getValue(rootValue);

    struct TreeNode* node = malloc(sizeof(struct TreeNode));
    node->val = rootValue;
    node->left = NULL;
    node->right = NULL;
    
    if (startIndex == endIndex) {
        return node;
    }
    
    node->left = findRoot(startIndex, rootInorderIndex - 1);
    node->right = findRoot(rootInorderIndex + 1, endIndex);
    
    return node;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
    g_preorder = preorder;
    g_preorderSize = preorderSize;
    
    g_inorder = inorder;
    g_inorderSize = inorderSize;
    
    g_inorderItemTableSize = 1024;
    g_inorderItemTable = malloc(sizeof(struct Item*) * g_inorderItemTableSize);
    for (int i=0;i<g_inorderItemTableSize;i++) {
        g_inorderItemTable[i] = NULL;
    }
    
    for (int i=0;i<inorderSize;i++) {
        addItem(inorder[i], i);
    }
    
    g_preorderSeenCount = 0;
    struct TreeNode* root = findRoot(0, preorderSize-1);
    
    for (int i=0;i<g_inorderItemTableSize;i++) {
        struct Item* item = g_inorderItemTable[i];
        while(item != NULL) {
            struct Item* tempItem = item->nextItem;
            free(item);
            item = tempItem;
        }
    }
    free(g_inorderItemTable);
    
    return root;
}