int getValue(int* bits, int bitsSize) {
    // Because we can't get the last bit of int, we need to use the unsigned int.
    uint result = 0;
    for (int i = (bitsSize - 1); i >= 0; i--) {
        result = result << 1;
        if (bits[i] == 1) {
            result |= 1;
        }
    }

    return (int)result;
}

int getBitSum(int bitA, int bitB) {
    int base = 0;
    if ((bitA & bitB) == 1) {
        base = 2;
    }
    else {
        base = bitA | bitB;
    }

    return base;
}

void addOneInBits(int* bits, int bitsSize, int index) {
    if (index >= bitsSize) {
        return;
    }

    int result = getBitSum(bits[index], 1);
    if (result == 2) {
        bits[index] = 0;
        addOneInBits(bits, bitsSize, index + 1);
    }
    else {
        bits[index] = result;
    }
}

int getSum(int a, int b) {
    int bitsSize = 32;
    int* bits = (int*)calloc(sizeof(int), bitsSize);

    // Because the 32 bits is a signed bit, we must use the unsigned int to get each bit of an int number.
    uint mask = 1;
    for (int i = 0; i < bitsSize; i++) {
        int bitA = ((a & mask) == mask) ? 1 : 0;
        int bitB = ((b & mask) == mask) ? 1 : 0;

        if (bitA) {
            addOneInBits(bits, bitsSize, i);
        }

        if (bitB) {
            addOneInBits(bits, bitsSize, i);
        }

        mask = (mask << 1);
    }

    int sum = getValue(bits, bitsSize);

    free(bits);

    return sum;
}