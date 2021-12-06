bool isOneBitCharacter(int* bits, int bitsSize){
    int decodedIndex = 0;
    
    // The last one must be 'zero'
    while (decodedIndex < bitsSize - 1) {
        if (bits[decodedIndex] == 0) {
            decodedIndex += 1;
        } else {
            decodedIndex += 2;
        }
    }
    
    // The last one must be 'zero'
    bool isOneBitCharacter = false;
    if (decodedIndex == bitsSize - 1) {
        isOneBitCharacter = true;
    }
    
    return isOneBitCharacter;
}