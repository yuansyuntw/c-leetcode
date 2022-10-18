const int COUNT_TO_LINKLISTITEMS_MAP_LENGTH = 20000;
typedef struct LinkListItem {
	int value;
	struct LinkListItem* nextItem;
} LinkListItem;

typedef struct {
    int value;
    int frequency;	
    UT_hash_handle hh;
} HashTableItem;

typedef struct {
    int maxFrequency;
    HashTableItem* hashtable;
    LinkListItem** countToItemsMap;
} FreqStack;

FreqStack* freqStackCreate() {
   	FreqStack *stack = (FreqStack *)calloc(1, sizeof *stack);
	stack->maxFrequency = 0;
    stack->hashtable = NULL;
    stack->countToItemsMap = (LinkListItem**)calloc(COUNT_TO_LINKLISTITEMS_MAP_LENGTH , sizeof(LinkListItem*));
    return stack;
}

HashTableItem* updateHashTable(FreqStack* obj, int value) {
    HashTableItem* item = NULL;

    HASH_FIND_INT(obj->hashtable, &value, item);
    bool isNotFind = (item == NULL);
    if (isNotFind) {
        item = (HashTableItem *)calloc(1, sizeof *item);
        item->value = value;
        item->frequency = 0;
    }

    item->frequency++;
    HashTableItem* oldItem;
	HASH_REPLACE_INT(obj->hashtable, value, item, oldItem);
	
	return item;
}

void updateCountToItemsLinkList(FreqStack* obj, HashTableItem* item) {
	int currentFrequency = item->frequency;
	LinkListItem *lastItem = obj->countToItemsMap[currentFrequency];
	LinkListItem *currentItem = lastItem;
	while(currentItem != NULL) {
		lastItem = currentItem;
		currentItem = currentItem->nextItem;
    }
    

    LinkListItem* newItem = (LinkListItem *)calloc(1, sizeof(LinkListItem));
    newItem->value = item->value;

    bool isEmpty = (lastItem == NULL);
    if (isEmpty) {
        obj->countToItemsMap[currentFrequency] = newItem;
    } else {
        lastItem->nextItem = newItem;
    }
}

void freqStackPush(FreqStack* obj, int val) {
	HashTableItem* item = updateHashTable(obj, val);

    bool isUpdatedMaxFrequency = (item->frequency > obj->maxFrequency);	
    if (isUpdatedMaxFrequency) {
        obj->maxFrequency = item->frequency;
    }

    updateCountToItemsLinkList(obj, item);
}

const int INVALID_VALUE = -1;
int removeLastItemForTargetCount(FreqStack* obj) {
	LinkListItem* start = obj->countToItemsMap[obj->maxFrequency];
    bool isEmpty = (start == NULL);
    if (isEmpty) {
        return INVALID_VALUE;
    }
    
    LinkListItem* previous = start;
    LinkListItem* last = start->nextItem;
    if (last == NULL) {
        int value = start->value;
        free(start);
        obj->countToItemsMap[obj->maxFrequency] = NULL;
        obj->maxFrequency--;
        return value;
    }
    
    while(last->nextItem != NULL) {
        previous = last;
        last = last->nextItem;
    }

    int value = last->value;
    free(last);
    previous->nextItem = NULL;
    return value;
}

void decendingItemFrequency(FreqStack* obj, int targetValue) {
	HashTableItem* item;

	HASH_FIND_INT(obj->hashtable, &targetValue, item);
	if (item != NULL) {
		item->frequency--;
        
        HashTableItem *oldItem;
		HASH_REPLACE_INT(obj->hashtable, value, item, oldItem);
    }
}

int freqStackPop(FreqStack* obj) {
	int value = removeLastItemForTargetCount(obj);
	if (value == INVALID_VALUE) {
		return INVALID_VALUE;
    }

	decendingItemFrequency(obj, value);
	return value;
}

void freqStackFree(FreqStack* obj) {
    HashTableItem *currentItem, *tmp;

	HASH_ITER(hh, obj->hashtable, currentItem, tmp) {
		free(currentItem);
    }

    for (int i=1;i<obj->maxFrequency; i++) {
        LinkListItem *item = obj->countToItemsMap[i];
        while(item != NULL) {
            LinkListItem *tmp = item->nextItem;
            free(item);
            item = tmp;
        }
    }

    free(obj);
}


/**
 * Your FreqStack struct will be instantiated and called as such:
 * FreqStack* obj = freqStackCreate();
 * freqStackPush(obj, val);
 
 * int param_2 = freqStackPop(obj);
 
 * freqStackFree(obj);
*/