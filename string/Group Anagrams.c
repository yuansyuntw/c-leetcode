char** g_strs;
int g_strsSize;

int g_maxGroupSize;
char*** g_group;
int g_returnSize;
int* g_returnColumnSizes;

struct Item {
    char* sortedStr;
    int groupIndex;
    struct Item* nextItem;
};

int g_hashTableSize;
struct Item** g_hashTable;

int qsortCompareChar(void* a, void* b) {
    return *((char* )a) - *((char* )b);
}

int getKey(char* strs) {
    unsigned int key = 0;

    int index = 0;
    while (strs[index] != '\0') {
        key = (key << 5) | (key >> 27);
        key += strs[index];
        index++;
    }
    
    key = (key >> 8) + key;
    key = fmod(key, INT_MAX);
    
    return (int)key;
}

int getGrounpIndex(char* str) {
    int hashkey = getKey(str);
    int index = hashkey % g_hashTableSize;
    
    struct Item* item = g_hashTable[index];
    while(item != NULL) {
        if (strcmp(item->sortedStr, str) == 0) {
            return item->groupIndex;
        }
        
        item = item->nextItem;
    }
    
    return -1;
}

int newGroup(char* str) {
    int hashkey = getKey(str);
    int index = hashkey % g_hashTableSize;
    
    struct Item* item = g_hashTable[index];
    struct Item* lastItem = NULL;
    while(item != NULL) {
        lastItem = item;
        item = item->nextItem;
    }
    
    int groupIndex = g_returnSize++;
    
    struct Item* newItem = (struct Item*)malloc(sizeof(struct Item));
	if (newItem == NULL) {
		printf("fail to malloc newItem\n");
		return -1;
	}
	
    newItem->sortedStr = str;
    newItem->groupIndex = groupIndex;
    newItem->nextItem = NULL;
    
    g_group[groupIndex] = (char**)malloc(sizeof(char*) * g_maxGroupSize);
    if (g_group[groupIndex] == NULL) {
		printf("fail to malloc g_group[groupIndex]\n");
		return -1;
	}
	
    if (lastItem == NULL) {
        g_hashTable[index] = newItem;
    } else {
        lastItem->nextItem = newItem;
    }

    return groupIndex;
}

void addStrToGroup(char* str, int index) {
    if (index >= g_returnSize) {
        printf("fail to ground strs: wrong index(%d)\n", index);
        return;
    }
    
    int columnSize = g_returnColumnSizes[index];
    g_group[index][columnSize++] = str;
    g_returnColumnSizes[index] = columnSize;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays ar
 e returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes){
    g_strs = strs;
    g_strsSize = strsSize;
	
    g_hashTableSize = 1024;
    g_hashTable = (struct Item**)malloc(sizeof(struct Item*) * g_hashTableSize);
	if (g_hashTable == NULL) {
		printf("fail to malloc g_hashTable\n");
		return NULL;
	}
	
    for (int i=0;i<g_hashTableSize;i++) {
        g_hashTable[i] = NULL;
    }
    
    g_returnSize = 0;
    g_maxGroupSize = g_strsSize;
    g_group = (char***)malloc(sizeof(char**) * g_maxGroupSize);
	if (g_group == NULL) {
		printf("fail to malloc g_group\n");
		return NULL;
	}
	
    g_returnColumnSizes = (int*)calloc(g_maxGroupSize, sizeof(int));
	if (g_returnColumnSizes == NULL) {
		printf("fail to malloc g_returnColumnSizes\n");
		return NULL;
	}
    
    for (int i=0; i<g_strsSize; i++) {
        int strsSize = strlen(g_strs[i]);
        char* copyStrs = malloc(sizeof(char) * (strsSize + 1));
        strcpy(copyStrs, g_strs[i]);
        qsort(copyStrs, strsSize, sizeof(char), qsortCompareChar);
        int hashkey = getKey(copyStrs);

        int index = getGrounpIndex(copyStrs);
        if (index == -1) {
            index = newGroup(copyStrs);
        } else {
            free(copyStrs);
        }
		
		if (index == -1) {
            return NULL;
        }
        
        addStrToGroup(g_strs[i], index);
    }
    
    for (int i=0;i<g_hashTableSize;i++) {
        struct Item *item = g_hashTable[i];
        while(item != NULL) {
            struct Item* nextItem = item->nextItem;
            free(item->sortedStr);
            free(item);
            item = nextItem;
        }
    }
    free(g_hashTable);
    
    *returnSize = g_returnSize;
	
    *returnColumnSizes = (int*)malloc(sizeof(int) * g_returnSize);
	if (*returnColumnSizes == NULL) {
		printf("fail to malloc *returnColumnSizes\n");
		return NULL;
	}
		
    char*** returnGroup = (char***)malloc(sizeof(char**) * g_returnSize);
	if (*returnGroup == NULL) {
		printf("fail to malloc *returnGroup\n");
		return NULL;
	}
    
    for (int i=0;i<g_returnSize;i++) {
        int columnSize = g_returnColumnSizes[i];

        (*returnColumnSizes)[i] = columnSize;
        returnGroup[i] = (char**)malloc(sizeof(char*) * columnSize);
		if (returnGroup[i] == NULL) {
			printf("fail to malloc returnGroup[i]\n");
			return NULL;
		}
        
        for (int j=0;j<columnSize;j++) {
            returnGroup[i][j] = g_group[i][j];
        }
    }
    free(g_returnColumnSizes);
    
    for (int i=0;i<g_returnSize;i++) {
        free(g_group[i]);
    }
    free(g_group);
    
    return returnGroup;
}