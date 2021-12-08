int maxLengthBetweenEqualCharacters(char * s){
    char* stack = malloc(sizeof(char) * 300);
    int stackIndex = 0;
    
    int maxLength = -1;
    int sIndex = 0;
    while (s[sIndex] != '\0') {
        stack[stackIndex++] = s[sIndex];
        for (int i=stackIndex-1; i>=0; i--) {
            if (stack[i] == s[sIndex]) {
                int length = sIndex - i - 1;
                if (length > maxLength) {
                    maxLength = length;
                }
            }
        }
        
        sIndex++;
    }
    
    free(stack);
    
    return maxLength;
}