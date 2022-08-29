
struct Item {
    char key[2];
    char value;
    UT_hash_handle hh;
};

bool isDifferenceAndAdd(struct Item** hashtable, char key, char value) {
    char keyString[2];
    sprintf(keyString, "%c", key);

    struct Item* foundItem = NULL;
    HASH_FIND_STR(*hashtable, keyString, foundItem);
    bool isNotFound = (foundItem == NULL);
    if (isNotFound) {
        struct Item* newItem = malloc(sizeof *newItem);
        sprintf(newItem->key, "%c", key);
        newItem->value = value;
        HASH_ADD_STR(*hashtable, key, newItem);
    } else {
        char existValue = foundItem->value;
        bool isDifference = (value != existValue);
        if (isDifference) {
            return false;
        }
    }
    
    return true;
}

bool isIsomorphic(char* s, char* t) {
    int sSize = strlen(s);
    
    struct Item *mappingTableS = NULL;
    struct Item *mappingTableT = NULL;
    bool result = true;
    for (int i = 0; i < sSize; i++) {
        char sChar = s[i];
        char tChar = t[i];
        result = isDifferenceAndAdd(&mappingTableS, sChar, tChar);
        if (!result) {
            break;
        }
        
        result = isDifferenceAndAdd(&mappingTableT, tChar, sChar);
        if (!result) {
            break;
        }
    }
    
    HASH_CLEAR(hh, mappingTableS);
    HASH_CLEAR(hh, mappingTableT);

    return result;
}