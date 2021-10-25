bool isPowerOfThree(int n){
    if (n <= 0) {
        return false;
    }
    
    int quotient = n;
    while(quotient >= 3) {
        if (quotient % 3 != 0) {
            return false;
        }
        
        quotient = quotient / 3;
    }
    
    if (quotient == 1) {
        return true;
    }
    
    return false;
}