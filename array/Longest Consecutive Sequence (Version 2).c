
int g_itemTableSize;
struct Item** g_itemTable;

int* g_nums;

int* g_groupArray;
int* g_grounpSize;

int g_maxGroupSize;

struct Item {
    int key;
    int value;
    struct Item* nextItem;
};

int hashkey(int num) {
    if (num == 0) {
        num = 1;
    }
    
    if (num < 0) {
        num*=-1;
    }
    
    return (int)(num>>16) + num;
}

bool addItem(int key, int value) {
    int index = hashkey(key) % g_itemTableSize;
    
    struct Item* item = g_itemTable[index];
    struct Item* lastItem = NULL;
    while(item != NULL) {
        if (item->key == key) {
            return false;
        }
        
        lastItem = item;
        item = item->nextItem;
    }
    
    struct Item *newItem = malloc(sizeof(struct Item));
    newItem->key = key;
    newItem->value = value;
    newItem->nextItem = NULL;
    
    if (lastItem == NULL) {
        g_itemTable[index] = newItem;
    } else {
        lastItem->nextItem = newItem;
    }
    
    return true;
}

int findValue(int key) {
    int index = hashkey(key) % g_itemTableSize;
    
    struct Item* item = g_itemTable[index];
    while(item != NULL) {
        if (item->key == key) {
            return item->value;
        }
        
        item = item->nextItem;
    }
    
    return -1;
}

void unionGroup(int num1, int num2) {
    int groupRootIndex1 = findValue(num1);
    if (groupRootIndex1 == -1) {
        printf("fail to find the num1: %d\n", num1);
        return;
    }

    while(g_groupArray[groupRootIndex1] != groupRootIndex1) {
        groupRootIndex1 = g_groupArray[groupRootIndex1];
    }
    int groupRootNum1 = g_nums[groupRootIndex1];
    int groupRootSize1 = g_grounpSize[groupRootIndex1];
    
    int groupRootIndex2 = findValue(num2);
    if (groupRootIndex2 == -1) {
        printf("fail to find the num2: %d\n", num2);
            return;
    }
    
    while(g_groupArray[groupRootIndex2] != groupRootIndex2) {
        groupRootIndex2 = g_groupArray[groupRootIndex2];
    }
    int groupRootNum2 = g_nums[groupRootIndex2];
    int groupRootSize2 = g_grounpSize[groupRootIndex2];

    int largerGroupNum = groupRootNum1;
    int largetGroupIndex = groupRootIndex1;
    int smallerGroupNum = groupRootNum2;
    int smallerGroupIndex = groupRootIndex2;
    if (groupRootSize1 < groupRootSize2) {
        largerGroupNum = groupRootNum2;
        largetGroupIndex = groupRootIndex2;
        smallerGroupNum = groupRootNum1;
        smallerGroupIndex = groupRootIndex1;
    }
    
    // union the smaller to bigger
    g_groupArray[smallerGroupIndex] = largetGroupIndex;
    g_grounpSize[largetGroupIndex] += g_grounpSize[smallerGroupIndex];

    if (g_grounpSize[largetGroupIndex] > g_maxGroupSize) {
        g_maxGroupSize = g_grounpSize[largetGroupIndex];
    }
}

int longestConsecutive(int* nums, int numsSize){
    if (numsSize == 0) {
        return 0;
    }
    
    g_nums = nums;
    
    g_itemTableSize = 2048;
    g_itemTable = malloc(sizeof(struct Item*) * g_itemTableSize);
    for (int i=0;i<g_itemTableSize;i++){
        g_itemTable[i] = NULL;
    }
    
    g_maxGroupSize = 1;
    g_groupArray = calloc(sizeof(int), numsSize);
    g_grounpSize = calloc(sizeof(int), numsSize);
    
    for (int i=0;i<numsSize;i++) {
        if (!addItem(nums[i], i)) {
            continue;
        }
        
        // pointer the group to self
        g_groupArray[i] = i;
        
        // the size of ground is one when initializing
        g_grounpSize[i] = 1;
        
        int leftNeighbor = nums[i] - 1;
        if (findValue(leftNeighbor) != -1) {
            unionGroup(leftNeighbor, nums[i]);
        }
        
        int rightNeightbor = nums[i] + 1;
        if (findValue(rightNeightbor) != -1) {
            unionGroup(rightNeightbor, nums[i]);
        }

    }
    
    for (int i=0;i<g_itemTableSize;i++) {
        struct Item* item = g_itemTable[i];
        while(item != NULL) {
            struct Item* temp = item->nextItem;
            free(item);
            item = temp;
        }
    }
    free(g_itemTable);
    
    free(g_groupArray);
    free(g_grounpSize);
    
    return g_maxGroupSize;
}