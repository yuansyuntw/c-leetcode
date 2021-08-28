bool isAnagram(char * s, char * t){
    int *s_letters = (int *)malloc(26 * sizeof(int));
    int *t_letters = (int *)malloc(26 * sizeof(int));
    
    int s_index = 0;
    while (s[s_index] != '\0') {
        int s_key = s[s_index] - 'a';
        s_letters[s_key]++;
        s_index++;
    }
    
    int t_index = 0;
    while (t[t_index] != '\0') {
        int t_key = t[t_index] - 'a';
        t_letters[t_key]++;
        t_index++;
    }
    
    if (s_index != t_index) {
        return false;
    }
    
    for (int i=0;i<26;i++) {
        if (s_letters[i] != t_letters[i]) {
            return false;
        }
    }
    
    return true;
}