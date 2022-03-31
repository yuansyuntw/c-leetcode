struct Item* g_itemHashTable;
int g_maxGroupSize;

struct Item {
    int key;
    int value;
    UT_hash_handle hh;
};

bool addItem(int num, int index) {
    if (findValue(num) != -1) {
        printf("add a repeated item: %d\n", num);
        return;
    }
    
    struct Item *newItem = malloc(sizeof(struct Item));
    newItem->key = num;
    newItem->value = index;
    HASH_ADD_INT(g_itemHashTable, key, newItem);
}

int findValue(int key) {
    struct Item *findItem;
    HASH_FIND_INT(g_itemHashTable, &key, findItem);
    if (findItem == NULL) {
        return -1;
    }
    
    return findItem->value;
}


int longestConsecutive(int* nums, int numsSize){
    if (numsSize == 0) {
        return 0;
    }
    
    g_itemHashTable = NULL;
    for (int i=0;i<numsSize;i++) {
        addItem(nums[i], i);
    }
    
    g_maxGroupSize = 1;
    for (int i=0; i<numsSize; i++) {
        if (findValue(nums[i] - 1) == -1) {
            int length = 1;
            for (int j=nums[i]+1; length<=numsSize; j++) {
                if (findValue(j) == -1) {
                    break;
                }

                length++;
                if (length > g_maxGroupSize) {
                    g_maxGroupSize = length;
                }
            }
        }
    }
    
    struct Item *currentItem, *tmpItem;
    HASH_ITER(hh, g_itemHashTable, currentItem, tmpItem) {
        HASH_DEL(g_itemHashTable, currentItem);
        free(currentItem);
    }
    
    return g_maxGroupSize;
}