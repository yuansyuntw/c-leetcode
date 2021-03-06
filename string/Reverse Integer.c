int reverse(int x){
    bool is_positive_number;
    int max_digits[] = {2,1,4,7,4,8,3,6,4,8};
    size_t max_digits_size = sizeof(max_digits) / sizeof(int);
    if (x > 0) {
        is_positive_number = true;
        max_digits[max_digits_size-1] -= 1;
    } else {
        is_positive_number = false;
    }

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
    
    int positive_factor = 1;
    if (is_positive_number == false) {
        positive_factor = -1;
    }
    
    int reverse_digit = 0;
    for (int index=0; index<digits_size; index++) {
        reverse_digit += positive_factor * digits[index] * pow(10, digits_size - index - 1);
    }
    
    free(digits);

    return reverse_digit;
}