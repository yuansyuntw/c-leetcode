struct Item {
    UT_hash_handle hh;
    int key;
    int value;
};

int sortByKey(struct Item* itemA, struct Item* itemB) {
    if (itemA->key > itemB->key) {
        return 1;
    } else if (itemA->key < itemB->key) {
        return -1;
    } else {
        return 0;
    }
}

bool isNStraightHand(int* hand, int handSize, int groupSize) {
	bool isPossible = ((handSize % groupSize) == 0);
	if (!isPossible) {
		return false;
	}

    struct Item *hashTable = NULL;

	for (int i = 0; i < handSize; i++) {
        int key = hand[i];
        struct Item *item = NULL;
        
        HASH_FIND_INT(hashTable, &key, item);
        bool isNotFound = (item == NULL);
        if (isNotFound) {
            item = calloc(1, sizeof(struct Item));
            item->key = hand[i];
            item->value = 0;
        } else {
            HASH_DEL(hashTable, item);
        }
        
        item->value = item->value + 1;
        HASH_ADD_INT(hashTable, key, item);
	}
    
    HASH_SORT(hashTable, sortByKey);
    int groupCount = 0;
    struct Item* item = hashTable;
    int lastKey = item->key - 1;
    while(item != NULL) {
        struct Item* nextItem = item->hh.next;
        
        bool isCanTake = ((item->key - lastKey) == 1);
        if (!isCanTake) {
            groupCount = 1;
            break;
        }
        
        lastKey = item->key;
        groupCount++;
        item->value--;
        if (item->value == 0) {
            // Pop the wrong item, it make the next group is not consecutive.
            bool isStop = (item != hashTable);
            HASH_DEL(hashTable, item);
            free(item);
            if (isStop) {
                groupCount = 1;
                break;
            }
        }
        
        if (groupCount == groupSize) {
            groupCount = 0;
            item = hashTable;
            
            bool isStop = (item == NULL);
            if (isStop) {
                break;
            }
            
            lastKey = item->key - 1;
            continue;
        }
        
        item = nextItem;
    }
    
    HASH_CLEAR(hh, hashTable);

	return (groupCount == 0);
}
