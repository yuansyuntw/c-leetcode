int dpSize = 4;
int aheadThreeCellIndex = 0;
int aheadTwoCellIndex = 1;
int aheadOneCellIndex = 2;
int currentCellIndex = 3;

void setCurrentCellMoney(int* dp, int currentCellMoney) {
    int moneyAheadTwoCell = currentCellMoney + dp[aheadTwoCellIndex];
    int moneyAheadThreeCell = currentCellMoney + dp[aheadThreeCellIndex];

    int result;
    if (moneyAheadTwoCell > moneyAheadThreeCell) {
        result = moneyAheadTwoCell;
    } else {
        result = moneyAheadThreeCell;
    }
    
    dp[currentCellIndex] = result;
}

int rob(int* nums, int numsSize){
    int max = nums[0];
    
    for (int i=0;((i<dpSize)&&(i<numsSize));i++) {
        if (nums[i] > max) max = nums[i];
    }
    
    if (numsSize > currentCellIndex) {
        int money = nums[aheadThreeCellIndex] + nums[aheadOneCellIndex];
        if (money > max) max = money;
    }
    
    if (numsSize < dpSize) return max;
    
    int* dp = calloc(sizeof(int), dpSize);          
    int* lastOneDP = calloc(sizeof(int), dpSize);
    
    dp[aheadThreeCellIndex] = nums[aheadThreeCellIndex];
    dp[aheadTwoCellIndex] = nums[aheadTwoCellIndex];
    dp[aheadOneCellIndex] = nums[aheadOneCellIndex] + dp[aheadThreeCellIndex];
                     
    lastOneDP[aheadThreeCellIndex] = 0; // the last one dp can't take the first house.
    lastOneDP[aheadTwoCellIndex] = nums[aheadTwoCellIndex];
    lastOneDP[aheadOneCellIndex] = nums[aheadOneCellIndex] + lastOneDP[aheadThreeCellIndex];

    int lastOneIndex = numsSize-1;
    for (int i=currentCellIndex;i<numsSize;i++) {
        // Give up the last one
        if (i < lastOneIndex) {
            setCurrentCellMoney(dp, nums[i]);
            if (dp[currentCellIndex] > max) max = dp[currentCellIndex];
        }
        
        // Give up the first one
        setCurrentCellMoney(lastOneDP, nums[i]);
        if ((i == lastOneIndex) && (lastOneDP[currentCellIndex] > max)) {
            max = lastOneDP[currentCellIndex];
        }
        
        // shift
        for (int c=0;c<dpSize-1;c++) {
            dp[c] = dp[c+1];
            lastOneDP[c] = lastOneDP[c+1];
        }
    }
    
    free(dp);
    free(lastOneDP);
    
    return max;
}