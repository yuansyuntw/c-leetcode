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
    int currentValue;
    int maxLength = strlen(s);
    for (int i=maxLength-1; i>=0; i--) {
        currentValue = charToInt(s[i]);
        if (sum/currentValue > 4) {
            sum -= currentValue;
        } else {
            sum += currentValue;
        }
    }
    
    return sum;
}