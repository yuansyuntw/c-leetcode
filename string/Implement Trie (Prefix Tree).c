const int gAlphabetSize = 26;

typedef struct TrieNode Trie;
struct TrieNode{
    Trie** childs;
    bool isEnd;
};

Trie* newTrie(bool isEnd) {
    Trie* root = malloc(sizeof(Trie));
    root->childs = calloc(sizeof(Trie*), gAlphabetSize);
    root->isEnd = isEnd;
    return root;
}

Trie* trieCreate() {
    return newTrie(false);
}

void trieInsert(Trie* obj, char * word) {
    int index = 0;
    while(word[index] != '\0') {
        char key = word[index];
        if (obj->childs[(key-'a')] != NULL) {
            obj = obj->childs[key-'a'];
        } else {
            Trie* child = newTrie(false);
            obj->childs[key-'a'] = child;
            obj = child;
        }
        
        index++;
    }
    
    obj->isEnd = true;
}

bool trieSearch(Trie* obj, char * word) {
    int index = 0;
    while(word[index] != '\0') {
        char key = word[index];
        if (obj->childs[key-'a'] != NULL) {
            obj = obj->childs[key-'a'];
        } else {
            return false;
        }

        index++;
    }
    
    return obj->isEnd;
}

bool trieStartsWith(Trie* obj, char * prefix) {
    int index = 0;
    while(prefix[index] != '\0') {
        char key = prefix[index];
        if (obj->childs[key-'a'] != NULL) {
            obj = obj->childs[key-'a'];
        } else {
            return false;
        }

        index++;
    }
    
    return true;
}

void trieFree(Trie* obj) {
    if (obj == NULL) return;
    
    for(int i=0;i<gAlphabetSize;i++) {
        if (obj->childs[i] != NULL) {
            trieFree(obj->childs[i]);
        }
    }
    
    free(obj->childs);
    free(obj);
}

/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);
 
 * bool param_2 = trieSearch(obj, word);
 
 * bool param_3 = trieStartsWith(obj, prefix);
 
 * trieFree(obj);
*/