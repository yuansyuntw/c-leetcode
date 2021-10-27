int charToInt(char input) {
    switch(input) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return -1;
    }
}

int romanToInt(char * s){
    int sum = 0;
    int startRange = 0;
    int endRange;
    int currentValue;
    int nextValue;
    while(s[startRange] != '\0') {
        endRange = startRange;
        
        currentValue = charToInt(s[startRange]);
        nextValue = charToInt(s[endRange+1]);
        if ((nextValue / currentValue == 5) || (nextValue / currentValue == 10)) {
            endRange ++;
        }
        
        if (endRange == startRange) {
            sum += currentValue;
        } else {
            sum += nextValue - currentValue;
        }
        
        startRange = endRange+1;
    }
    
    return sum;
}