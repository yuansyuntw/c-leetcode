
int characterReplacement(char* s, int k) {
    int leftIndex = 0;
    int rightIndex = 0;

    int letterSize = 26;
    int* lettersCount = (int*)calloc(sizeof(int), letterSize);

    int result = 0;
    int maxCount = 0;
    int sLength = strlen(s);
    for (; rightIndex < sLength; rightIndex++) {
        int letterindex = s[rightIndex] - 'A';
        lettersCount[letterindex]++;
        if (lettersCount[letterindex] > maxCount) {
            // Only increasing the max count makes the result more height
            // So we update the max count when increating the letter count.
            maxCount = lettersCount[letterindex];
        }

        int windowsLength = rightIndex - leftIndex + 1;
        if ((windowsLength - maxCount) > k) {
            // When we can't move right, we move the left index (sliding windows)
            letterindex = s[leftIndex] - 'A';
            lettersCount[letterindex]--;
            leftIndex++;
        }

        windowsLength = rightIndex - leftIndex + 1;
        if (windowsLength > result) {
            result = windowsLength;
        }
    }

    free(lettersCount);

    return result;
}