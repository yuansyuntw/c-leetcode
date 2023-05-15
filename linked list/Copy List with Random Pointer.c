/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *next;
 *     struct Node *random;
 * };
 */

struct Item
{
    UT_hash_handle hh;
    void *key;
    struct Node *oldNode;
    struct Node *newNode;
};

struct Item *table;

struct Node *getNode(struct Node *oldNode)
{
    if (oldNode == NULL)
    {
        return NULL;
    }

    struct Item *item = NULL;

    HASH_FIND_PTR(table, &oldNode, item);
    if (item == NULL)
    {
        struct Node *newNode = (struct Node *)calloc(1, sizeof(struct Node));

        item = (struct Item *)calloc(1, sizeof(struct Item));
        item->key = (void *)oldNode;
        item->oldNode = oldNode;
        item->newNode = newNode;
        HASH_ADD_PTR(table, key, item);
    }

    return item->newNode;
}

struct Node *copyRandomList(struct Node *head)
{
    if (head == NULL)
    {
        return NULL;
    }

    table = NULL;

    struct Node *result = getNode(head);
    struct Node *copyNode = NULL;
    struct Node *currentNode = head;
    while (currentNode != NULL)
    {
        copyNode = getNode(currentNode);
        copyNode->val = currentNode->val;
        copyNode->next = getNode(currentNode->next);
        copyNode->random = getNode(currentNode->random);
        currentNode = currentNode->next;
    }

    struct Item *current, *temp;
    HASH_ITER(hh, table, current, temp)
    {
        HASH_DEL(table, current);
        free(current);
    }

    return result;
}