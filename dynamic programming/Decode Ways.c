int numDecodings(char * s){
    int sSize = strlen(s);
    
    int nextNum = 0;
    int nextNextNum = 0;
    if (s[sSize - 1] != '0') {
        nextNum = 1;
    }
    
    int result = nextNum;
    for (int i=sSize-2; i>=0; i--) {
        if (s[i] == '0') {
            result = 0;
            nextNextNum = nextNum;
            nextNum = 0;
            continue;
        }
        
        int num = 0;
        
        // [i,i]*[i+1, j]
        int nextIndex = i+1;
        if (nextIndex > sSize-1) {
            // reach the last one.
            if (s[i] != '0') {
                num++;
            }
        } else {
            num += nextNum;
        }
        
        // [i, i+1] * [i+2, j]
        if (i <= (sSize-2)) {
            int charNum = ((s[i] - '0') * 10) + (s[nextIndex] - '0');
            if ((charNum >= 10) && (charNum <= 26)) {
                int nextNextIndex = i+2;
                if (nextNextIndex > sSize-1) {
                    // reach the boundary
                    num++;
                } else { 
                    num += nextNextNum;
                }
            }
        }
        
        nextNextNum = nextNum;
        nextNum = num;
        
        result = num;
    }
    
    return result;
}