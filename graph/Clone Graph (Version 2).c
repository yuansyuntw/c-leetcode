/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numNeighbors;
 *     struct Node** neighbors;
 * };
 */

struct Item {
    int key;
    struct Node* node;
    UT_hash_handle hh;
};

struct Item *g_hashTable;

struct Node* lookThrough(struct Node* s) {
    struct Item* findItem;
    HASH_FIND_INT(g_hashTable, &s->val, findItem);
    if (findItem != NULL) {
        return findItem->node;
    }
    
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->val = s->val;
    newNode->numNeighbors = s->numNeighbors;
    newNode->neighbors = malloc(sizeof(struct Node*) * newNode->numNeighbors);
    
    findItem = malloc(sizeof(struct Item));
    findItem->key = s->val;
    findItem->node = newNode;
    HASH_ADD_INT(g_hashTable, key, findItem);
    
    for (int i=0;i<newNode->numNeighbors;i++) {
        newNode->neighbors[i] = lookThrough(s->neighbors[i]);
    }
    
    return newNode;
}

struct Node *cloneGraph(struct Node *s) {
    if (s == NULL) {
        return NULL;
    }
    
    g_hashTable = NULL;
    
    struct Node* copyS = lookThrough(s);
    
    struct Item *currentItem, *tempItem;
    HASH_ITER(hh, g_hashTable, currentItem, tempItem) {
        HASH_DEL(g_hashTable, currentItem);
        free(currentItem);
    };
    
	return copyS;
}