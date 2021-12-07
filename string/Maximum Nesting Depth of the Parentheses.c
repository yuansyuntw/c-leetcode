

int maxDepth(char * s){
    int* stack = malloc(sizeof(int) * 100);
    int stackIndex = 0;
    for (int i=0; i<100; i++) {
        stack[i] = -1;
    }
    
    int sIndex = 0;
    while (s[sIndex] != '\0') {
        if (s[sIndex] == '(') {
            stack[stackIndex++] = 0;
        } else if (s[sIndex] == ')'){
            int maxDepth = 0;
            int findLeftParenthesesIndex = stackIndex-1;
            while (findLeftParenthesesIndex >= 0) {
                if (stack[findLeftParenthesesIndex] == 0) {
                    for(int i=(stackIndex-1); i>=(findLeftParenthesesIndex + 1); i--) {
                        stack[i] = -1;
                    }
                    
                    stack[findLeftParenthesesIndex] = maxDepth + 1;
                    stackIndex = findLeftParenthesesIndex + 1;
                    break;
                } else {
                    if (stack[findLeftParenthesesIndex] > maxDepth) {
                        maxDepth = stack[findLeftParenthesesIndex];
                    }
                }
                
                findLeftParenthesesIndex--;
            }
        }
        
        sIndex++;
    }
    
    int maxDepth = 0;
    for (int i=0; i<stackIndex; i++) {
        if (stack[i] > maxDepth) {
            maxDepth = stack[i];
        }
    }
    
    free(stack);
    
    return maxDepth;
}