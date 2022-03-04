
struct Item {
    char letter;
    int count;
};

int g_tableSize;
struct Item** g_tTable;

int g_sSize;
char* g_s;

int g_tSize;

int getIndex(char letter) {
    if ((letter >= 'a') && (letter <= 'z')) {
        return letter - 'a' + 26;
    } else {
        return letter - 'A';
    }
}

struct Item* getItem(struct Item** table, char letter) {
    int index = getIndex(letter);
    return table[index];
}

void addItem(struct Item** table, char addedLetter) {
    int index = getIndex(addedLetter);
    
    struct Item* item = table[index];
    if (item != NULL) {
        item->count++;
        return;
    }
    
    struct Item *newItem = malloc(sizeof(struct Item));
    newItem->letter = addedLetter;
    newItem->count = 1;
    table[index] = newItem;
}

void removeLetter(struct Item** table, char letter) {
    struct Item* item = getItem(table, letter);
    if (item == NULL) return;
    
    item->count--;
    if (item->count < 0) {
        item->count = 0;
    }
}

bool isSubString(struct Item** comparedTable) {
    for (int i=0;i<g_tableSize;i++) {
        struct Item* tItem = g_tTable[i];
        if (tItem != NULL) {
            struct Item* comparedItem = getItem(comparedTable, tItem->letter);
            if ((comparedItem == NULL) || (comparedItem->count < tItem->count)) return false;
        }
    }
    
    return true;
}

void releaseTable(struct Item** table) {
    for (int i=0; i<g_tableSize; i++) {
        struct Item* item = table[i];
        if (item != NULL) free(item);
    }
    free(table);
}

char * minWindow(char * s, char * t){
    g_sSize = strlen(s);
    g_tSize = strlen(t);
    if (g_sSize < g_tSize) return "";
    
    g_s = s;
    
    g_tableSize = 26*2;
    g_tTable = malloc(sizeof(struct Item*) * g_tableSize);
    for (int i=0; i<g_tableSize; i++) {
        g_tTable[i] = NULL;
    }
    
    int tIndex = 0;
    while (t[tIndex] != '\0') {
        addItem(g_tTable, t[tIndex++]);
    }
    
    int miniSubStringSize = g_sSize + 1;
    int miniLeftIndex = -1;
    int miniRightIndex = -1;
    
    struct Item** checkedTable = malloc(sizeof(struct Item*) * g_tableSize);
    for (int i=0; i<g_tableSize; i++) {
        checkedTable[i] = NULL;
    }
    
    int leftIndex = 0;
    int rightIndex = 0;
    addItem(checkedTable, g_s[rightIndex]);
    
    while (leftIndex < g_sSize) {
        if (isSubString(checkedTable)) {
            int subStringSize = rightIndex - leftIndex + 1;
            if (subStringSize < miniSubStringSize) {
                miniSubStringSize = subStringSize;
                miniLeftIndex = leftIndex;
                miniRightIndex = rightIndex;
            }

            removeLetter(checkedTable, g_s[leftIndex++]);
        } else {
            if (++rightIndex >= g_sSize) break;
            addItem(checkedTable, g_s[rightIndex]);
        }
    }

    releaseTable(checkedTable);
    releaseTable(g_tTable);

    if ((miniLeftIndex == -1) && (miniRightIndex == -1)) return "";
    
    int resultSize = miniRightIndex - miniLeftIndex + 1;
    char* result = malloc(sizeof(char) * (resultSize+1));
    int reusltIndex = 0;
    for (int i=miniLeftIndex; i<=miniRightIndex; i++) {
        result[reusltIndex++] = g_s[i];
    }
    result[reusltIndex] = '\0';

    return result;
}