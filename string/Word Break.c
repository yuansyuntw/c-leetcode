char* g_s;

char ** g_wordDict;
int g_wordDictSize;

int* g_memoryTable;

bool compareWord(char* word, int startIndex, int endIndex) {
    int wordLength = strlen(word);
    if (wordLength != (endIndex - startIndex + 1)) {
        return false;
    }
    
    int wordIndex = 0;
    for (int i=startIndex;i<=endIndex;i++) {
        if (g_s[i] != word[wordIndex]) {
            return false;
        }
        
        wordIndex++;
    }
    
    return true;
}

bool wordBreak(char * s, char ** wordDict, int wordDictSize){
    g_s = s;
    g_wordDict = wordDict;
    g_wordDictSize = wordDictSize;
    
    // make sure to add one for check the last index
    g_memoryTable = calloc(sizeof(int), strlen(s) + 1);
    
    int sLength = strlen(s);

    // the last index must can be break
    g_memoryTable[sLength] = 1;
    
    // check each index can be matched in word dictionary
    for(int i=sLength-1;i>=0;i--) {
        for (int j=0;j<wordDictSize;j++) {
            char* word = wordDict[j];
            int wordLength = strlen(word);
            if ((i + wordLength) <= sLength) {
                bool isBreak = compareWord(word, i, i + wordLength - 1);
                if (isBreak) {
                    // bottom-up, look the next sub problem from i+worldLength
                    g_memoryTable[i] = g_memoryTable[i + wordLength];
                }
                if (g_memoryTable[i] == 1) {
                    break;
                }
            }
        }
    }
    
    bool isCanBreak = (g_memoryTable[0] == 1);
    free(g_memoryTable);
    
    return isCanBreak;
}