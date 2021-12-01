int minOperations(char * s){
    int index = 0;
    
    int startWithZeroCount = 0;
    int startWihtOneCount = 0;
    while (s[index] != '\0') {
        // start with zero
        if ((index%2) == 0) {
            if (s[index] != '0') startWithZeroCount++;
        } else {
            if (s[index] != '1') startWithZeroCount++;
        }
        
        // start with one
        if ((index%2) == 0) {
            if (s[index] != '1') startWihtOneCount++;
        } else {
            if (s[index] != '0') startWihtOneCount++;
        }
        
        index++;
    }
    
    int count = startWithZeroCount;
    if (startWihtOneCount < startWithZeroCount) {
        count = startWihtOneCount;
    }
    
    return count;
}