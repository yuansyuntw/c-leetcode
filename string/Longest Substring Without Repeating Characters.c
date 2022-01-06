void clearDictionary(int * dictionary, int size) {
    for (int i=0; i<size; i++) {
        dictionary[i] = 0;
    }
}

int charToDictionaryIndex(char c) {
    return ((int)c - (int)' ');
}

void setValueForDictionary(int *dictionary, char key, int value) {
    int index = charToDictionaryIndex(key);
    dictionary[index] = value;
}

int getValueForDictionary(int *dictionary, char key) {
    int index = charToDictionaryIndex(key);
    return dictionary[index];
}

int lengthOfLongestSubstring(char * s) {
    int sSize = 0;
    while(s[sSize] != '\0') {
        sSize++;
    }
    
    if (sSize == 1) {
        return 1;
    }
    
    // find the repeated index
    int maxLength = 0;
    
    int recordDictionarySize = 96;
    int *recordDictionary = (int *)malloc(recordDictionarySize * sizeof(int));
    clearDictionary(recordDictionary, recordDictionarySize);
    
    for (int i=0;i<sSize;i++) {
        for (int j=i; j<sSize; j++) {
            int jValue = getValueForDictionary(recordDictionary, s[j]);
            setValueForDictionary(recordDictionary, s[j], jValue + 1);
            
            if(jValue > 0) {                
                // Move i index to repeated index.
                while(s[i] != s[j]) {
                    i++;
                }
                
                break;
            }
            
            int length = j-i+1;
            if (length > maxLength) {
                maxLength = length;
            }
        }
        
        if (i+maxLength >= sSize) break;
        
        clearDictionary(recordDictionary, recordDictionarySize);
    }
    
    // clear dictionary
    free(recordDictionary);
    
    // get the longest rang
    return maxLength;
}