typedef struct
{
    int key;
    int count;
    int heapIndex;
    UT_hash_handle hh;
} Item;

Item *hashtable;

int heapCount;
Item **heap;

int heapGetParentIndex(int index)
{
    return (index - 1) / 2;
}

void heapSwap(int index1, int index2)
{
    heap[index1]->heapIndex = index2;
    heap[index2]->heapIndex = index1;

    Item *tmp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = tmp;
}

void heapUpdateItem(Item *item)
{
    Item *currentItem = item;

    int parentItemIndex = heapGetParentIndex(currentItem->heapIndex);
    Item *parentItem = heap[parentItemIndex];

    while ((currentItem->heapIndex > 0) && (currentItem->count > parentItem->count))
    {
        heapSwap(currentItem->heapIndex, parentItem->heapIndex);

        parentItemIndex = heapGetParentIndex(currentItem->heapIndex);
        if (parentItemIndex == currentItem->heapIndex)
        {
            break;
        }

        parentItem = heap[parentItemIndex];
    }
}

void heapPush(Item *item)
{
    heap[heapCount] = item;
    item->heapIndex = heapCount;
    heapCount++;
    heapUpdateItem(item);
}

int heapGetLeftChildIndex(int parentIndex)
{
    return (parentIndex * 2) + 1;
}

int heapGetRightChildIndex(int parentIndex)
{
    return (parentIndex * 2) + 2;
}

void maxHeapify(int fromIndex)
{
    if (fromIndex >= heapCount)
    {
        return;
    }

    int maxCount = heap[fromIndex]->count;
    int maxIndex = fromIndex;
    int leftIndex = heapGetLeftChildIndex(fromIndex);
    if (leftIndex < heapCount)
    {
        Item *leftChild = heap[leftIndex];
        if (leftChild->count > maxCount)
        {
            maxCount = leftChild->count;
            maxIndex = leftIndex;
        }
    }

    int rightIndex = heapGetRightChildIndex(fromIndex);
    if (rightIndex < heapCount)
    {
        Item *rightChild = heap[rightIndex];
        if (rightChild->count > maxCount)
        {
            maxCount = rightChild->count;
            maxIndex = rightIndex;
        }
    }

    bool shouldSwitchWithChild = (maxIndex != fromIndex);
    if (shouldSwitchWithChild)
    {
        heapSwap(fromIndex, maxIndex);
        maxHeapify(maxIndex);
    }
}

Item *heapPop()
{
    if (heapCount == 0)
    {
        return NULL;
    }

    Item *top = heap[0];
    heap[0] = heap[heapCount - 1];
    heap[0]->heapIndex = 0;
    heapCount--;

    maxHeapify(0);
    return top;
}

char *reorganizeString(char *s)
{
    hashtable = NULL;

    heapCount = 0;
    heap = (Item **)calloc(27, sizeof(Item *));

    int sLength = strlen(s);
    ;
    for (int i = 0; i < sLength; i++)
    {
        Item *item = NULL;
        int findKey = (int)s[i];
        HASH_FIND_INT(hashtable, &findKey, item);
        bool isNotFind = (item == NULL);
        if (isNotFind)
        {
            item = (Item *)calloc(1, sizeof(Item));
            item->key = findKey;
            item->count = 1;
        }
        else
        {
            item->count++;
        }

        Item *oldItem = NULL;
        HASH_REPLACE_INT(hashtable, key, item, oldItem);
    }

    for (int i = 'a'; i <= 'z'; i++)
    {
        Item *item = NULL;
        HASH_FIND_INT(hashtable, &i, item);
        if (item != NULL)
        {
            heapPush(item);
        }
    }

    char *result = (char *)calloc(sLength + 1, sizeof(char));
    Item *lastItem = NULL;
    int count = 0;
    while (count < sLength)
    {
        Item *item = heapPop();
        if (item == NULL)
        {
            result[0] = '\0';
            break;
        }

        sprintf(result, "%s%c", result, item->key);
        item->count--;

        if (lastItem != NULL)
        {
            if (lastItem->count > 0)
            {
                heapPush(lastItem);
            }
            lastItem = NULL;
        }
        lastItem = item;

        count++;
    }

    Item *currentItem, *tempItem;
    HASH_ITER(hh, hashtable, currentItem, tempItem)
    {
        HASH_DEL(hashtable, currentItem);
        if (currentItem != NULL)
        {
            free(currentItem);
        }
    }

    free(heap);

    sprintf(s, "%s", result);
    free(result);

    return s;
}