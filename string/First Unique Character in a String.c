int firstUniqChar(char * s){
    const int INIT_VALUE = -1;
    const int REPEATED_VALUE = -2;
    
    int* dict = (int*)malloc(sizeof(int) * 26);
    for (int i=0; i<26; i++) {
        dict[i] = INIT_VALUE;
    }
    
    int index = 0;
    while(s[index] != '\0') {
        int key = s[index] - 'a';
        if (dict[key] == INIT_VALUE) {
            dict[key] = index;
        } else {
            // repeated char
            if (dict[key] != REPEATED_VALUE) {
                dict[key] = REPEATED_VALUE;
            }
        }

        index++;
    }
    
    int min_index = index;
    for(int i=0 ;i<26 ;i++) {
        if (dict[i] == INIT_VALUE) {
            continue;
        }
        
        if (dict[i] == REPEATED_VALUE) {
            continue;
        }
        
        if (dict[i] < min_index) {
            min_index = dict[i];
        }
    }
    
    if (min_index == index) {
        min_index = -1;
    }
    
    free(dict);

    return min_index;
}