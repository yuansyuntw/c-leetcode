int longestPalindrome(char * s){
    int countTableSize = 26*2;
    int* countTable = malloc(sizeof(int) * countTableSize);
    for(int i=0; i<countTableSize; i++) {
        countTable[i] = 0;
    }
    
    int index = 0;
    while(s[index] != '\0') {
        int lowercaseIndex = s[index] - 'a';
        int uppercaseIndex = s[index] - 'A';
        if ((lowercaseIndex >= 0) && (lowercaseIndex <= 25)) {
            countTable[lowercaseIndex]++;
        }
        
        if ((uppercaseIndex >= 0) && (uppercaseIndex <= 25)) {
            countTable[uppercaseIndex + 26]++;
        }
        
        index++;
    }
    
    bool hasOddChar = false;
    int result = 0;
    int oddCharCount = 0;
    for (int i=0; i<countTableSize; i++) {
        if (countTable[i] > 0) {
            if ((countTable[i]%2) == 1) {
                oddCharCount++;
            }
            
            result += countTable[i];
        }
    }
    
    // Only let one for an odd count of char, others count become an even count by minus one
    if (oddCharCount > 0) {
        result = result - (oddCharCount - 1);
    }
    
    free(countTable);
    
    return result;
}