int hammingWeight(uint32_t n) {
    if (n == 1) {
        return 1;
    }
    
    int count = n&1;
    unsigned int pow = 1;
    for (int i=1; i<=31; i++) {
        pow = 2 * pow;
        if ((n/pow) < 1) {
            break;
        }
        
        if ((n&pow) > 0) {
            count++;
        }
    }

    return count;
}