int g_nodeChildsSize = 26;
struct Node {
    struct Node** childs;
    bool isTerminal;
};

struct Node* g_trie;
char* g_s;
int g_maxWordLength;
int g_minWordLength;
int** g_memoryTable;

struct Node* createNode(bool isTerminal) {
    struct Node* node = malloc(sizeof(struct Node));
    node->childs = malloc(sizeof(struct Node*) * g_nodeChildsSize);
    for (int i=0;i<g_nodeChildsSize;i++) {
        node->childs[i] = NULL;
    }

    node->isTerminal = isTerminal;
    return node;
}

void addWord(char * word) {
    int index = 0;
    struct Node* parent = g_trie;
    struct Node* child = NULL;
    while(word[index] != '\0') {
        char c = word[index];
        int childIndex = c - 'a';
        child = parent->childs[childIndex];
        
        if (child == NULL) {
            child = createNode(false);
            parent->childs[childIndex] = child;
        }
        
        index++;
        parent = child;
    }
    
    // Last character
    if (child != NULL) {
        child->isTerminal = true;
    }
}

void deleteNode(struct Node* node) {
    if (node->isTerminal) {
        free(node);
    } else {
        for (int i=0;i<g_nodeChildsSize;i++) {
            struct Node* child = node->childs[i];
            if (child != NULL) {
                deleteNode(child);
            }
        }
    }
}

bool findWord(int startIndex, int endIndex) {
    struct Node *parent = g_trie;
    for (int i=startIndex;i<=endIndex;i++) {
        char targetChar = g_s[i];
        int childIndex = targetChar - 'a';
        struct Node* child = parent->childs[childIndex];
        if (child == NULL) {
            return false;
        }
        
        parent = child;
    }
    
    return parent->isTerminal;
}

bool breakTheRange(int startIndex, int endIndex) {
    if (startIndex > endIndex) {
        return false;
    }
    
    if (g_memoryTable[startIndex][endIndex] == 1) {
        return true;
    } else if (g_memoryTable[startIndex][endIndex] == -1) {
        return false;
    }
    
    int frontIndex = endIndex;
    int rearIndex = endIndex;
    bool isCanBreak = false;
    while (frontIndex >= startIndex) {
        int length = rearIndex - frontIndex + 1;
        if (length < g_minWordLength) {
            frontIndex--;
            continue;
        }
        
        if (length > g_maxWordLength) {
            g_memoryTable[startIndex][endIndex] = -1;
            return false;
        }
        
        bool isWord = findWord(frontIndex, rearIndex);
        if (isWord) {
            if (frontIndex == startIndex) {
                isCanBreak = true;
                break;
            }
            
            g_memoryTable[frontIndex][rearIndex] = 1;
            isCanBreak = breakTheRange(startIndex, --frontIndex);
            if (isCanBreak) {
                break;
            }
        } else {
            g_memoryTable[frontIndex][rearIndex] = -1;
            frontIndex--;
        }
    }
    
    g_memoryTable[startIndex][endIndex] = isCanBreak ? 1 : -1;
    
    return isCanBreak;
}

bool wordBreak(char * s, char ** wordDict, int wordDictSize){
    g_s = s;
    
    g_memoryTable = malloc(sizeof(int*) * strlen(s));
    for (int i=0;i<strlen(s);i++) {
        g_memoryTable[i] = calloc(sizeof(int), strlen(s));
    }
    
    // 1. create trie
    g_maxWordLength = INT_MIN;
    g_minWordLength = INT_MAX;
    g_trie = createNode(false);
    for (int i=0;i<wordDictSize;i++) {
        addWord(wordDict[i]);
        int wordLength = strlen(wordDict[i]);
        if (wordLength > g_maxWordLength) {
            g_maxWordLength = wordLength;
        }
        
        if (wordLength < g_minWordLength) {
            g_minWordLength = wordLength;
        }
    }
    
    bool isCanBreak = breakTheRange(0, strlen(s) - 1);
    
    deleteNode(g_trie);
    
    for (int i=0;i<strlen(s);i++) {
        free(g_memoryTable[i]);
    }
    free(g_memoryTable);
    
    return isCanBreak;
}