int myAtoi(char * s){
    int start_index = 0;
    while (s[start_index] != '\0') {
        if (s[start_index] != ' ') {
            break;
        }
        
        start_index++;
    }
    
    printf("start index: %d\n", start_index);
    
    bool is_positive_number = true;
    if (s[start_index] == '+') {
        is_positive_number = true;
        start_index++;
    } else if (s[start_index] == '-') {
        is_positive_number = false;
        start_index++;
    }
    
    printf("is postive number: %d\n", is_positive_number);
    
    if ((s[start_index] < '0') || (s[start_index] > '9')){
        return 0;
    }
    
    // Remove useless zero number
    while(s[start_index] != '\0') {
        if (s[start_index] == '0') {
            start_index++;
        } else {
            break;
        }
    }
    
    int max_digits[] = {2, 1, 4, 7, 4, 8, 3, 6, 4, 8};
    size_t max_digits_size = sizeof(max_digits) / sizeof(int);
    if (is_positive_number) {
        max_digits[max_digits_size - 1] -= 1;
    }

    int *digits = (int *)malloc(max_digits_size * sizeof(int));    
    int reading_index = start_index;
    int digits_index = 0;
    bool is_overflow = false;
    while(s[reading_index] != '\0') {
        if ((s[reading_index] >= '0') && (s[reading_index] <= '9')) {
            if (digits_index >= max_digits_size) {
                is_overflow = true;
                break;
            }
            
            digits[digits_index] = s[reading_index] - '0';
            printf("digits[%d]=%d\n", digits_index, digits[digits_index]);
            
            digits_index++;
        } else {
            break;
        }
        
        reading_index ++;
    }
    
    int digits_size = digits_index;
    if ((is_overflow == false) && (digits_size == max_digits_size)) {
        for (int i=0; i<digits_size; i++) {
            if (digits[i] > max_digits[i]) {
                is_overflow = true;
                break;
            } else if (digits[i] < max_digits[i]) {
                is_overflow = false;
                break;
            }
        }
    }
    
    if (is_overflow) {
        digits = max_digits;
    }
    
    printf("digits size: %d\n", digits_size);
    printf("is overflow: %d\n", is_overflow);
    
    int result = 0;
    int positive_factor = 1;
    if (is_positive_number == false) {
        positive_factor= -1;
    }
    
    for (int i=0;i<digits_size; i++) {
        result += positive_factor * digits[i] * pow(10, digits_size - i - 1);
    }
    
    return result;
}