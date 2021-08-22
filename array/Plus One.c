int* plusOne(int* digits, int digitsSize, int* returnSize){
    *returnSize = digitsSize;
    
    for (int i=digitsSize-1; i>=0; i--) {
        if ((i == 0) && (digits[i] + 1) >= 10) {
            *returnSize = digitsSize + 1;
            
            digits = (int *)malloc(sizeof(int) * (*returnSize));
            digits[0] = 1;
            for (int j=1; j<*returnSize; j++) {
                digits[j] = 0;
            }
            
            break;
        }
        
        if ((digits[i] + 1) >= 10) {
            digits[i] = 0;
        } else {
            digits[i]++;
            break;
        }
    }
    
    return digits;
}