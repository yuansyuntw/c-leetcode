int max(int* nums, int numsSize) {
    int max = INT_MIN;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
    }

    return max;
}

int sum(int* nums, int numsSize) {
    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
    }

    return sum;
}

bool canSplit(int* nums, int numsSize, int groupNumber, int targetSum) {
    int subarrayCount = 0;

    int currentSum = 0;
    for (int i = 0; i < numsSize; i++) {
        currentSum += nums[i];
        if (currentSum > targetSum) {
            subarrayCount++;
            currentSum = nums[i];
        }
    }

    bool isCanSplit = (subarrayCount + 1) <= groupNumber;
    return isCanSplit;
}

int splitArray(int* nums, int numsSize, int m) {
    int lowerBound = max(nums, numsSize);
    int upperBound = sum(nums, numsSize);

    int result = upperBound;
    while (lowerBound <= upperBound) {
        int middleBound = (lowerBound + upperBound) / 2;
        if (canSplit(nums, numsSize, m, middleBound)) {
            result = middleBound;
            upperBound = middleBound - 1;
        }
        else {
            lowerBound = middleBound + 1;
        }
    }

    return result;
}