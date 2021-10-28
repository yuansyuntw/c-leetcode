int hammingWeight(uint32_t n) {
    if (n == 0) {
        return 0;
    }
    
    short count = 0;
    unsigned int mask = 1;
    for(int i=0;i<=31;i++) {
        if ((n & mask) > 0) {
            count++;
        }
        
        mask = mask << 1;
    }

    return count;
}