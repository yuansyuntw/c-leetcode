int countSegments(char * s){
    int index = 0;
    int count = 0;
    while(s[index] != '\0') {
        if (s[index] == ' ') {
            while ((s[index] == ' ') && (s[index] != '\0')) {
                index++;
            }
        } else {
            count++;
            while ((s[index] != ' ') && (s[index] != '\0')) {
                index++;
            }
        }
    }
    
    return count;
}