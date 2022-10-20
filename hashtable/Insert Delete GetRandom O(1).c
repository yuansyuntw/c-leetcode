const int HASHTABLE_MAX_SIZE = 20000;
typedef struct Item
{
    int value;
    int index;
    UT_hash_handle hh;
} Item;

typedef struct
{
    int currentItemCount;
    Item *hashtable;
    int *numberList;
} RandomizedSet;

RandomizedSet *randomizedSetCreate()
{
    RandomizedSet *set = (RandomizedSet *)calloc(1, sizeof(RandomizedSet));
    set->hashtable = NULL;
    set->numberList = (int *)calloc(HASHTABLE_MAX_SIZE, sizeof(int));

    // Set the seed for getting random number
    srand(time(NULL));

    return set;
}

bool randomizedSetInsert(RandomizedSet *obj, int val)
{
    Item *item;

    HASH_FIND_INT(obj->hashtable, &val, item);
    bool isNotExit = (item == NULL);
    if (isNotExit)
    {
        obj->numberList[obj->currentItemCount] = val;

        item = (Item *)calloc(1, sizeof(Item));
        item->value = val;
        item->index = obj->currentItemCount++;
        HASH_ADD_INT(obj->hashtable, value, item);
    }

    return isNotExit;
}

bool randomizedSetRemove(RandomizedSet *obj, int val)
{
    Item *item;

    HASH_FIND_INT(obj->hashtable, &val, item);
    bool isExit = (item != NULL);
    if (isExit)
    {
        int lastValue = obj->numberList[obj->currentItemCount - 1];
        Item *lastItem;
        HASH_FIND_INT(obj->hashtable, &lastValue, lastItem);
        if (lastItem != NULL)
        {
            lastItem->index = item->index;
            obj->numberList[lastItem->index] = lastValue;
            obj->currentItemCount--;
        }
        else
        {
            printf("something wrong: %d\n", val);
        }

        HASH_DEL(obj->hashtable, item);
        free(item);
    }

    return isExit;
}

int randomizedSetGetRandom(RandomizedSet *obj)
{
    int targetIndex = rand() % obj->currentItemCount;
    return obj->numberList[targetIndex];
}

void randomizedSetFree(RandomizedSet *obj)
{
    Item *current, *temp;
    HASH_ITER(hh, obj->hashtable, current, temp)
    {
        HASH_DEL(obj->hashtable, current);
        free(current);
    }

    free(obj->numberList);
    free(obj->hashtable);
    free(obj);
}
