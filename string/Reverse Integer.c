int reverse(int x){
    bool is_positive_number;
    int max_digits[] = {2,1,4,7,4,8,3,6,4,8};
    if (x > 0) {
        is_positive_number = true;
        max_digits[9] = 7;
    } else {
        is_positive_number = false;
    }

    int max_digits_size = 10;
    int* digits = (int *)malloc(max_digits_size * sizeof(int));
    int digits_size = max_digits_size;
    for (int index = 0; index<max_digits_size; index++) {
        digits[index] = x % 10;
        if (is_positive_number == false) {
            digits[index] *= -1;
        }
        
        x = x / 10;
        if (x == 0) {
            digits_size = index + 1;
            break;
        }
    }
    
    // check for overflow
    bool is_overflow = false;
    if (max_digits_size == digits_size) {
        for (int index = 0; index < max_digits_size; index++) {
            if (max_digits[index] > digits[index]) {
                is_overflow = false;
                break;
            } else if (max_digits[index] < digits[index]) {
                is_overflow = true;
                break;
            }
        }
    }
    
    if (is_overflow) {
        return 0;
    }
    
    int reverse_digit = 0;
    for (int index=0; index<digits_size; index++) {
        reverse_digit += digits[index] * pow(10, digits_size - index - 1);
    }
    
    free(digits);
    
    if (!is_positive_number) {
        reverse_digit = reverse_digit * -1;
    }

    return reverse_digit;
}