/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numNeighbors;
 *     struct Node** neighbors;
 * };
 */

struct Node** g_hashTable;

struct Node* lookThrough(struct Node* s) {
    struct Item* findItem = g_hashTable[s->val];
    if (findItem != NULL) {
        return findItem;
    }
    
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->val = s->val;
    newNode->numNeighbors = s->numNeighbors;
    newNode->neighbors = malloc(sizeof(struct Node*) * newNode->numNeighbors);
    
    g_hashTable[s->val] = newNode;
    
    for (int i=0;i<newNode->numNeighbors;i++) {
        newNode->neighbors[i] = lookThrough(s->neighbors[i]);
    }
    
    return newNode;
}

struct Node *cloneGraph(struct Node *s) {
    if (s == NULL) {
        return NULL;
    }
    
    int hashTableSize = 101;
    g_hashTable = malloc(sizeof(struct Node*) * hashTableSize);
    for (int i=0;i<hashTableSize;i++) {
        g_hashTable[i] = NULL;
    }
    
    struct Node* copyS = lookThrough(s);
    
    free(g_hashTable);
    
	return copyS;
}