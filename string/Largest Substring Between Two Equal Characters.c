int maxLengthBetweenEqualCharacters(char * s){
    const int charactersSize = 26;
    const int firstCharacterIndex = 0;
    const int lastCharacterIndex = 1;
    
    int** characters = malloc(sizeof(int *) * charactersSize);
    for (int i=0; i<charactersSize; i++) {
        characters[i] = (int *)malloc(sizeof(int) * 2);
        characters[i][firstCharacterIndex] = -1;
        characters[i][lastCharacterIndex] = -1;
    }
    
    int maxLength = -1;
    int sIndex = 0;
    while (s[sIndex] != '\0') {
        int charToIndex = s[sIndex] - 'a';
        if (characters[charToIndex][firstCharacterIndex] == -1) {
            characters[charToIndex][firstCharacterIndex] = sIndex;
        } else {
            characters[charToIndex][lastCharacterIndex] = sIndex;
            int length = sIndex - characters[charToIndex][firstCharacterIndex] - 1;
            if (length > maxLength) {
                maxLength = length;
            }
        }
        
        sIndex++;
    }
    
    for (int i=0; i<charactersSize;i++) {
        free(characters[i]);
    }
    
    free(characters);
    
    return maxLength;
}