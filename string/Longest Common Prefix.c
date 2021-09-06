char * longestCommonPrefix(char ** strs, int strsSize){
    if (strsSize == 1) {
        return strs[0];
    }
    
    int indexOfMinLengthString = 0;
    int minLength = strlen(strs[0]);
    for (int i=1; i<strsSize; i++) {
        int length = strlen(strs[i]);
        if (length < minLength) {
            indexOfMinLengthString = i;
            minLength = length;
        }
    }
    
    if (minLength == 0) {
        return "";
    }
    
    char *prefix = malloc(sizeof(char) * minLength + 1);
    sprintf(prefix, "");
    
    char *minLengthString = strs[indexOfMinLengthString];
    for (int i=0; i<minLength; i++) {
        char checkedChar = minLengthString[i];
        for (int j=0; j<strsSize; j++) {
            if (j == indexOfMinLengthString) {
                continue;
            }
            
            if (checkedChar != strs[j][i]) {
                return prefix;
            }
        }
        
        sprintf(prefix, "%s%c", prefix, checkedChar);
    }
        
    return prefix;
}