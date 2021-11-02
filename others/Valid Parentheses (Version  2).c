char openParenthesesTable(char openingParentheses) {
    switch (openingParentheses) {
        case ')': {
            return '(';
        }
        case '}': {
            return '{';
        }
        case ']': {
            return '[';
        }
        default: {
            break;
        } 
    }
    
    return '\0';
}


bool isValid(char * s){
    char *stackBuffer = malloc(sizeof(char) * 10001);
    int stackIndex = 0;
    
    int readingIndex = 0;
    while (s[readingIndex] != '\0') {
        switch (s[readingIndex]) {
            case '(':
            case '{':
            case '[': {
                stackBuffer[stackIndex++] = s[readingIndex];
                break;
            }
            case ')':
            case ']':
            case '}': {
                char matchOpenParentheses = openParenthesesTable(s[readingIndex]);
                if (matchOpenParentheses == '\0') {
                    // No found the match parentheses
                    return false;
                }
                
                if ((stackIndex == 0) || stackBuffer[stackIndex-1] != matchOpenParentheses) {
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