int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int leftIndex = 0;
    int rightIndex = numbersSize - 1;
    
    while(leftIndex < rightIndex) {
        int sum = numbers[leftIndex] + numbers[rightIndex];
        
        if (sum > target) {
            rightIndex--;
        } else if (sum < target) {
            leftIndex++;
        } else {
            break;
        }
    }
    
    (*returnSize) = 2;
    int* results = (int*)calloc(2, sizeof(int));
    results[0] = leftIndex + 1;
    results[1] = rightIndex + 1;
    
    return results;
}
