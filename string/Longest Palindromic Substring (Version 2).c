bool isPalindrome(char * s, int startIndex, int endIndex) {
    int checkSize = ((endIndex - startIndex + 1)/2) + 1;
    for (int i=0; i<checkSize; i++) {
        if (s[startIndex + i] != s[endIndex - i]) {
            return false;
        }
    }
    
    return true;
}

char * longestPalindrome(char * s){
    int sSize = strlen(s);
    int longestLength = 0;
    int longestStartIndex = 0;
    for (int i=0; i<sSize; i++) {
        for(int j=0; j<=i; j++) {
            int startIndex = j;
            int endIndex = i;
            int length = endIndex - startIndex + 1;
            if (length <= longestLength) {
                break;
            }
            
            if (isPalindrome(s, startIndex, endIndex)) {
                longestLength = length;
                longestStartIndex = startIndex;
            }
        }
    }
    
    char *answer = (char *)malloc(sizeof(char) * (longestLength+1));
    for (int i=0;i<longestLength;i++) {
        answer[i] = s[longestStartIndex + i];
    }
    
    answer[longestLength] = '\0';
    return answer;
}