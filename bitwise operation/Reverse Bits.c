uint32_t reverseBits(uint32_t n) {
    unsigned int result = 0;
    for(int i=0; i<=31; i++) {
        if ((n & 1) > 0) {
            result ++;
        }

        n = n >> 1;
        if (i < 31) {
            result = result << 1;
        }
    }
    
    return result;
}