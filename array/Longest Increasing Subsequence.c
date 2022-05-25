int lengthOfLIS(int* nums, int numsSize) {
    int* dp = (int *)calloc(sizeof(int), numsSize);

    int maxResult = 0;
    for (int i = numsSize - 1; i >= 0; i--) {
        int maxLISNum = INT_MAX;
        int maxLIS = 0;
        for (int searchIndex = i + 1; searchIndex < numsSize; searchIndex++) {
            if ((nums[searchIndex] > nums[i]) && (nums[searchIndex] < maxLISNum) && (dp[searchIndex] > maxLIS)) {
                maxLISNum = nums[searchIndex];
                maxLIS = dp[searchIndex];
            }
        }

        dp[i] = maxLIS + 1;
        if (dp[i] > maxResult) {
            maxResult = dp[i];
        }
    }

    free(dp);

    return maxResult;
}