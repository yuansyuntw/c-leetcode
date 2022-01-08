char **gTable;

char * longestPalindrome(char * s){
    int sSize = strlen(s);
    
    gTable = malloc(sizeof(*gTable) * sSize);
    for (int i=0;i<sSize;i++) {
        gTable[i] = calloc(sizeof(*(gTable[i])), sSize);
    }
    
    // the length is 1
    int longestLength = 1;
    int longestSubstringStartIndex = 0;
    for (int i=0;i<sSize;i++) {
        gTable[i][i] = 1;
    }
    
    // the length is 2
    for (int i=0;i<sSize-1;i++) {
        if (s[i] == s[i+1]) {
            gTable[i][i+1] = 1;
            longestLength = 2;
            longestSubstringStartIndex = i;
        }
    }
    
    // the length is above 3
    for (int length=3; length<=sSize; length++) {
        for (int startIndex=0; startIndex<(sSize-length+1); startIndex++) {
            int endIndex = startIndex + length - 1;
            if (gTable[startIndex + 1][endIndex - 1] && (s[startIndex] == s[endIndex])) {
                gTable[startIndex][endIndex] = 1;
                if (length > longestLength) {
                    longestLength = length;
                    longestSubstringStartIndex = startIndex;
                }
            }
        }
    }
    
    // free the memory
    for (int i=0; i<sSize; i++) {
        free(gTable[i]);
    }
    
    free(gTable);
    
    char* substring = malloc(sizeof(char) * (longestLength+1));
    for (int i=0; i<longestLength; i++) {
        substring[i] = s[longestSubstringStartIndex + i];
    }
    
    substring[longestLength] = '\0';
    return substring;
}