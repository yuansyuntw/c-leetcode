struct Item
{
    int id;
    int value;
    UT_hash_handle hh;
};

int subarraySum(int *nums, int numsSize, int k)
{
    int result = 0;

    struct Item *hashtable = NULL;

    struct Item *placeholderItem = (struct Item *)calloc(1, sizeof(struct Item));
    placeholderItem->id = 0;
    placeholderItem->value = 1;
    HASH_ADD_INT(hashtable, id, placeholderItem);

    int sum = 0;
    for (int i = 0; i < numsSize; i++)
    {
        sum += nums[i];
        int diff = sum - k;

        struct Item *preSumItem;
        HASH_FIND_INT(hashtable, &diff, preSumItem);
        if (preSumItem != NULL)
        {
            result += preSumItem->value;
        }

        struct Item *newPreSumItem;
        HASH_FIND_INT(hashtable, &sum, newPreSumItem);
        if (newPreSumItem == NULL)
        {
            newPreSumItem = (struct Item *)calloc(1, sizeof(struct Item));
            newPreSumItem->id = sum;
        }
        newPreSumItem->value += 1;
        struct Item *oldPreSumItem;
        HASH_REPLACE_INT(hashtable, id, newPreSumItem, oldPreSumItem);
        if (newPreSumItem != oldPreSumItem)
        {
            free(oldPreSumItem);
        }
    }

    struct Item *current, *tmp;
    HASH_ITER(hh, hashtable, current, tmp)
    {
        HASH_DEL(hashtable, current);
        free(current);
    }

    return result;
}
