int caseToLower(char c) {
    int c_int = (int)c;
    if ((c_int >= (int)'A') && (c_int<=(int)'Z')) {
        return c + 32;
    }
    
    if ((c_int >= (int)'a') && (c_int <= (int)'z')) {
        return c_int;
    }
    
    if ((c_int >= (int)'0') && (c_int <= (int)'9')) {
        return c_int;
    }
    
    // skip this character
    return -1;
}

bool isPalindrome(char * s){
    int s_size = 0;
    while (s[s_size] != '\0') {
        s_size ++;
    }
    
    int backward_index = 0;
    int forward_index = s_size - 1;
    while(forward_index > backward_index) {
        int backward_char = caseToLower(s[backward_index]);
        while(backward_char == -1) {
            backward_index ++;
            if (backward_index == s_size) {
                return true;
            }
            
            backward_char = caseToLower(s[backward_index]);
        }
        
        int forward_char = caseToLower(s[forward_index]);
        while(forward_char == -1) {
            forward_index --;
            if (forward_index == -1) {
                return true;
            }
            
            forward_char = caseToLower(s[forward_index]);
        }
        
        if (forward_index <= backward_index) {
            break;
        }
        
        if (backward_char != forward_char) {
            return false;
        }
        
        forward_index --;
        backward_index ++;
    }
    
    return true;
}