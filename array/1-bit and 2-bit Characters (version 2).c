bool isOneBitCharacter(int* bits, int bitsSize){
    bool* characterResult = malloc(sizeof(bool) * bitsSize);
    int characterIndex = 0;
    int decodedIndex = 0;
    
    while (decodedIndex < bitsSize) {
        if (bits[decodedIndex] == 0) {
            characterResult[characterIndex++] = 0;
            decodedIndex += 1;
        } else {
            characterResult[characterIndex++] = 1;
            decodedIndex += 2;
        }
    }
    
    bool isOneBitCharacter = false;
    if (characterResult[characterIndex-1] == 0) {
        isOneBitCharacter = true;
    }
    
    free(characterResult);
    
    return isOneBitCharacter;
}