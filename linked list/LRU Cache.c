struct Node
{
    int key;
    int val;
    struct Node *next;
    struct Node *previous;
};

struct HashItem
{
    int key;
    struct Node *node;
    UT_hash_handle hh;
};

typedef struct
{
    struct Node *head;
    struct Node *trail;
    int capacity;
    struct HashItem *hashtable;
    int count;
} LRUCache;

LRUCache *lRUCacheCreate(int capacity)
{
    LRUCache *cache = (LRUCache *)calloc(1, sizeof(LRUCache));
    cache->head = NULL;
    cache->trail = NULL;
    cache->capacity = capacity;
    cache->hashtable = NULL;
    cache->count = 0;
    return cache;
}

int lRUCacheGet(LRUCache *obj, int key)
{
    if (obj->head == NULL)
    {
        return -1;
    }

    struct HashItem *item = NULL;
    HASH_FIND_INT(obj->hashtable, &key, item);
    if (item == NULL)
    {
        return -1;
    }

    // Move to the front
    struct Node *currentNode = item->node;
    if (currentNode == NULL)
    {
        return -1;
    }

    if (obj->head == currentNode)
    {
        return currentNode->val;
    }

    struct Node *head = currentNode;
    struct Node *trail = obj->trail;
    if (obj->trail == currentNode)
    {
        trail = currentNode->previous;
    }

    struct Node *next = obj->head;
    struct Node *previousOfNext = head;
    struct Node *nextOfNext = next->next;
    if (nextOfNext == currentNode)
    {
        nextOfNext = currentNode->next;
    }

    struct Node *previousOfNextOfCurrentNode = currentNode->previous;
    struct Node *nextOfPreviousOfCurrentNode = currentNode->next;

    struct Node *previousOfHead = NULL;
    struct Node *nextOfHead = next;

    obj->head = head;
    obj->trail = trail;

    next->previous = previousOfNext;
    next->next = nextOfNext;

    if (currentNode->next != NULL)
    {
        currentNode->next->previous = previousOfNextOfCurrentNode;
    }

    if (currentNode->previous != NULL)
    {
        currentNode->previous->next = nextOfPreviousOfCurrentNode;
    }

    head->previous = previousOfHead;
    head->next = nextOfHead;

    return currentNode->val;
}

void removeNode(LRUCache *obj, struct Node *node)
{
    struct HashItem *item = NULL;

    HASH_FIND_INT(obj->hashtable, &node->key, item);
    if (item != NULL)
    {
        HASH_DEL(obj->hashtable, item);
        free(item);
    }

    struct Node *head = obj->head;
    if (head == node)
    {
        head = NULL;
    }

    struct Node *trail = obj->trail;
    if (trail == node)
    {
        trail = node->previous;
    }

    struct Node *nextOfPrevious = node->next;
    if (obj->trail == node)
    {
        nextOfPrevious = NULL;
    }

    struct Node *previousOfNext = node->previous;

    if (node->previous != NULL)
    {
        node->previous->next = nextOfPrevious;
    }

    if (node->next != NULL)
    {
        node->next->previous = previousOfNext;
    }

    obj->head = head;
    obj->trail = trail;

    obj->count--;

    free(node);
}

void appendNode(LRUCache *obj, int key, int value)
{
    struct Node *node = (struct Node *)calloc(1, sizeof(struct Node));
    node->key = key;
    node->val = value;
    node->previous = obj->trail;
    node->next = NULL;

    if (obj->trail != NULL)
    {
        obj->trail->next = node;
    }
    obj->trail = node;

    if (obj->head == NULL)
    {
        obj->head = node;
    }

    struct HashItem *item = (struct HashItem *)calloc(1, sizeof(struct HashItem));
    item->key = key;
    item->node = node;
    HASH_ADD_INT(obj->hashtable, key, item);

    obj->count++;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    struct HashItem *item = NULL;
    HASH_FIND_INT(obj->hashtable, &key, item);
    if (item != NULL)
    {
        item->node->val = value;
        lRUCacheGet(obj, key); // update the location.
        return;
    }

    if (obj->count >= obj->capacity)
    {
        if (obj->trail != NULL)
        {
            removeNode(obj, obj->trail);
        }
    }

    appendNode(obj, key, value);
    lRUCacheGet(obj, key); // update the location.
}

void lRUCacheFree(LRUCache *obj)
{
    struct Node *node = obj->head;
    while (node != NULL)
    {
        struct Node *next = node->next;
        free(node);
        node = next;
    }

    struct HashItem *current, *temp;
    HASH_ITER(hh, obj->hashtable, current, temp)
    {
        HASH_DEL(obj->hashtable, current);
        free(current);
    }

    free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);

 * lRUCachePut(obj, key, value);

 * lRUCacheFree(obj);
*/
