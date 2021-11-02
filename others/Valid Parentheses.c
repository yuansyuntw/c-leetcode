bool isValid(char * s){
    char *stackBuffer = malloc(sizeof(char) * 10001);
    int stackIndex = 0;
    
    int readingIndex = 0;
    while (s[readingIndex] != '\0') {
        switch (s[readingIndex]) {
            case '(': {
                stackBuffer[stackIndex++] = s[readingIndex];
                break;
            }
            case ')': {
                if ((stackIndex == 0) || stackBuffer[stackIndex-1] != '(') {
                    return false;
                }

                stackIndex--;
                break;
            }
            case '{': {
                stackBuffer[stackIndex++] = s[readingIndex];
                break;
            }
            case '}': {
                if ((stackIndex == 0) || stackBuffer[stackIndex-1] != '{') {
                    return false;
                }

                stackIndex--;
                break;
            }
            case '[': {
                stackBuffer[stackIndex++] = s[readingIndex];
                break;
            }
            case ']': {
                if ((stackIndex == 0) || stackBuffer[stackIndex-1] != '[') {
                    return false;
                }

                stackIndex--;
                break;
            }
            default: {
                break;
            }
        }
        
        readingIndex++;
    }
    
    if (stackIndex != 0) {
        return false;
    }
    
    return true;
}