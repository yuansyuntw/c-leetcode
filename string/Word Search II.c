int gWordSize;

int gBoardRowSize;
int gBoardColSize;
char** gBoard;

int gResultsCount;
char** gResults;

int gTrieChildrenSize = 26;
struct Trie {
    char character;
    bool isEnd;
    int wordCount;
    char* word;
    struct Trie** children;
};
struct Trie* gRootTrie; 

struct Trie* createTrie() {
    struct Trie* trie = calloc(sizeof(struct Trie), 1);
    trie->children = calloc(sizeof(struct Tire *), gTrieChildrenSize);
    trie->character = '0';
    trie->wordCount = 0;
    trie->isEnd = false;
    trie->word = NULL;
    return trie;
}

void freeTrie(struct Trie* trie) {
    for (int i=0;i<gTrieChildrenSize;i++) {
        if (trie->children[i] != NULL) {
            freeTrie(trie->children[i]);
        }
    }
    
    free(trie->children);
    free(trie);
}

void findTrie(struct Trie * trie, char* word) {
    gResults[gResultsCount++] = word;

    int index = 0;
    struct Trie* parent = trie;
    while(word[index] != '\0') {
        int i = word[index] - 'a';
        if (trie->children[i] == NULL) {
            return;
        }
        
        parent = trie;
        parent->wordCount--;

        trie = trie->children[i];
        
        index++;
    }
    
    // avoid to repeat find it.
    trie->isEnd = false;
    trie->wordCount--;
}

void insertTrie(struct Trie* trie, char* word) {
    trie->wordCount++;
    
    int index = 0;
    while(word[index] != '\0') {
        int i = word[index] - 'a';
        if (trie->children[i] == NULL) {
            trie->children[i] = createTrie();
        }
            
        trie = trie->children[i];
        trie->character = word[index];
        trie->wordCount++;

        index++;
    }
    
    trie->isEnd = true;
    trie->word = word;
}

void backtracking(struct Trie * trie, int row, int col) {
    if ((row < 0) || (row >= gBoardRowSize) || (col < 0) || (col >= gBoardColSize)) return;
    if (gResultsCount == gWordSize) return;
    if (trie->wordCount == 0) return;
    if (gBoard[row][col] == '0') return;
    
    char temp = gBoard[row][col];
    int i = temp - 'a';
    if (trie->children[i] != NULL) {
        struct Trie* child = trie->children[i];
        if (gBoard[row][col] == child->character) {
            if (child->isEnd) {
                findTrie(gRootTrie, child->word);

                if (gResultsCount == gWordSize) return;

                // skip to next children
                if (child->wordCount == 0) return;
            }
            
            gBoard[row][col] = '0';
            backtracking(child, row + 1, col);
            backtracking(child, row - 1, col);
            backtracking(child, row, col + 1);
            backtracking(child, row, col - 1);
            gBoard[row][col] = temp;
        }
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** findWords(char** board, int boardSize, int* boardColSize, char ** words, int wordsSize, int* returnSize){
    gRootTrie = createTrie();
    
    gWordSize = wordsSize;
    for (int i=0;i<wordsSize;i++) {
        insertTrie(gRootTrie, words[i]);
    }
    
    gResultsCount = 0;
    gResults = calloc(sizeof(char *), wordsSize);
    
    gBoardRowSize = boardSize;
    gBoardColSize = *boardColSize;
    gBoard = board;
    
    for (int r=0;r<gBoardRowSize;r++) {
        for (int c=0;c<gBoardColSize;c++) {
            backtracking(gRootTrie, r, c);
            if (gResultsCount == wordsSize) break;
        }
    }
    
    freeTrie(gRootTrie);
    
    *returnSize = gResultsCount;
    return gResults;
}