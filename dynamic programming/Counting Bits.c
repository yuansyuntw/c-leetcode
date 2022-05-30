/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int n, int* returnSize){
    int resultSize = n + 1;
    *returnSize = resultSize;
    int* result = (int *)calloc(sizeof(int), resultSize);
    for (int i = 1; i < resultSize; i++) {
        int bitCount = 0;
        if ((i % 2) == 1) {
            bitCount += 1;
        }

        bitCount += result[i / 2];

        result[i] = bitCount;
    }

    return result;
}