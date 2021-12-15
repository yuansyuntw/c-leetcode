int titleToNumber(char * columnTitle){
    int number = 0;
    
    int columnSize = strlen(columnTitle);
    for (int i=0; i<columnSize; i++) {
        number += ((int)(columnTitle[i] - 'A') + 1) * pow(26, columnSize - i - 1);
    }
    
    return number;
}