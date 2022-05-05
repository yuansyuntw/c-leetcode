int gWordChildrenSize = 26;

typedef struct Word WordDictionary;
struct Word {
    int maxLength;
    WordDictionary** children;
    bool isEnd;
};

void updateObj(WordDictionary* obj, int wordLength) {
    if (wordLength > obj->maxLength) {
        obj->maxLength = wordLength;
    }
}

WordDictionary* wordDictionaryCreate() {
    WordDictionary *word = calloc(sizeof(WordDictionary), 1);
    word->maxLength = 0;
    word->children = calloc(sizeof(WordDictionary *), gWordChildrenSize);
    word->isEnd = false;
    return word;
}

void wordDictionaryAddWord(WordDictionary* obj, char * word) {
    int wordLength = strlen(word);
    updateObj(obj, wordLength);
    
    int index = 0;
    while(word[index] != '\0') {
        int i = word[index] - 'a';
        if (obj->children[i] == NULL) {
            obj->children[i] = wordDictionaryCreate();
        }
        
        obj = obj->children[i];
        updateObj(obj, wordLength);
        
        index++;
    }
    
    obj->isEnd = true;
}

bool searchWordDFS(WordDictionary* obj, char * word, int index, int length) {
    if (index >= length) {
        return obj->isEnd;
    }
    
    char c = word[index];
    if (c == '.') {
        for (int i=0;i<gWordChildrenSize;i++) {
            if (obj->children[i] != NULL) {
                WordDictionary* child = obj->children[i];
                if (length <= child->maxLength) {
                    if (searchWordDFS(child, word, index+1, length)) {
                        return true;
                    }
                }
            }
        }
    } else {
        int i = c-'a';
        if (obj->children[i] != NULL) {
            return searchWordDFS(obj->children[i], word, index+1, length);
        }
    }
    
    return false;
}

bool wordDictionarySearch(WordDictionary* obj, char * word) {
    return searchWordDFS(obj, word, 0, strlen(word));
}

void wordDictionaryFree(WordDictionary* obj) {
    for (int i=0;i<gWordChildrenSize;i++) {
        if (obj->children[i] != NULL) {
            wordDictionaryFree(obj->children[i]);
        }
    }
    
    free(obj->children);
    free(obj);
}

/**
 * Your WordDictionary struct will be instantiated and called as such:
 * WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);
 
 * bool param_2 = wordDictionarySearch(obj, word);
 
 * wordDictionaryFree(obj);
*/