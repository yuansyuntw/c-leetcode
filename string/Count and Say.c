char * countAndSay(int n){
    if (n == 1) {
        return "1";
    }
    
    char *newSay = strdup("11");
    for (int i=2; i<n; i++) {
        const char *oldChar = newSay;
        
        newSay = malloc(sizeof(char) * 1024 * 5);
        newSay[0] = '\0';
        for (int i=0; i<strlen(oldChar); i++) {
            char countedChar = oldChar[i];

            int count = 1;
            for (int j=i+1; j<strlen(oldChar); j++) {
                if (oldChar[j] == countedChar) {
                    count++;
                    i = j;
                } else {
                    break;
                }
            }

            sprintf(newSay, "%s%d%c", newSay, count, oldChar[i]);
        }
        
        free (oldChar);
    }
        
    return newSay;
}