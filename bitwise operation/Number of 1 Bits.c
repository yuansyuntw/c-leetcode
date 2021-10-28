int hammingWeight(uint32_t n) {
    if (n == 0) {
        return 0;
    }
    
    short count = 1;
    n = n & (n-1);
    while (n > 0) {
        n = n & (n-1);
        count++;
    }

    return count;
}