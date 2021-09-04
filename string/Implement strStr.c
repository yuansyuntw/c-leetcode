int strStr(char * haystack, char * needle){
    size_t haystackLength = strlen(haystack);
    size_t needleLength = strlen(needle);

    if (needleLength == 0) {
        return 0;
    }
    
    if (needleLength > haystackLength) {
        return -1;
    }
    
    char startChar = needle[0];
    char endChar = needle[needleLength-1];
    int stackIndex = 0;
    while (haystack[stackIndex] != '\0') {
        int stackEndIndex = stackIndex + needleLength - 1;
        if (stackEndIndex >= haystackLength) {
            break;
        }
        
        if ((haystack[stackIndex] == startChar) && (haystack[stackEndIndex] == endChar)) {
            int needleIndex = 0;
            while (needle[needleIndex] != '\0') {
                if (haystack[stackIndex + needleIndex] != needle[needleIndex]) {
                    break;
                }
                
                needleIndex++;
                if (needle[needleIndex] == '\0') {
                    return stackIndex;
                }
            }
        }
        
        stackIndex++;
    }

    return -1;
}