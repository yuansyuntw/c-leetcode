bool isPaindromic(char* s, int startIndex, int endIndex) {
    int middleIndex = (endIndex + startIndex) / 2;
    int range = endIndex - startIndex + 1;
    int halfOfRange = range / 2;
    for (int i = 0; i < halfOfRange; i++) {
        if (s[startIndex + i] != s[endIndex - i]) {
            return false;
        }
    }

    return true;
}

int countSubstrings(char* s) {
    int stringLength = strlen(s);

    int result = 0;
    for (int c = 0; c < stringLength; c++) {
        for (int r = c; r < stringLength; r++) {
            if (c == r) {
                result++;
                continue;
            }

            bool paindromic = isPaindromic(s, c, r);
            if (paindromic) {
                result++;
            }
            
        }
    }
    
    return result;
}