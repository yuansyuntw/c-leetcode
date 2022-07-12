int countPalindromic(char* s, int leftIndex, int rightIndex) {
    int result = 0;
    int stringLength = strlen(s);
    while ((leftIndex >= 0) && (rightIndex < stringLength) && s[leftIndex] == s[rightIndex]) {
        result++;
        
        // expanding
        leftIndex--;
        rightIndex++;
    }

    return result;
}

int countSubstrings(char* s) {
    int result = 0;

    int stringLength = strlen(s);
    for (int i = 0; i < stringLength; i++) {
        // odd
        int leftIndex = i;
        int rightIndex = i;
        result += countPalindromic(s, leftIndex, rightIndex);

        // even
        leftIndex = i;
        rightIndex = leftIndex + 1;
        result += countPalindromic(s, leftIndex, rightIndex);
    }

    return result;
}