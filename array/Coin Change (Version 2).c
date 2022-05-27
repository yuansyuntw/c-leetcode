// For this solution, I chose the number of the first coin in the first step.

int coinChange(int* coins, int coinsSize, int amount){
    if (amount == 0) return 0;

    int** dp = (int**)calloc(sizeof(int*), coinsSize);
    for (int i = 0; i < coinsSize; i++) {
        dp[i] = (int *)calloc(sizeof(int), amount+1);
        if (dp[i] == NULL) return -1;
    }
    if (dp == NULL) return -1;

    int min = INT_MAX;
    for (int coinIndex = coinsSize-1; coinIndex >= 0; coinIndex--) {
        int currentCoin = coins[coinIndex];
        for (int remainAmount = amount; remainAmount >=0; remainAmount--) {
            if (coinIndex == (coinsSize - 1)) {
                if (remainAmount != 0) {
                    if ((remainAmount % currentCoin) == 0) {
                        dp[coinIndex][remainAmount] = remainAmount / currentCoin;
                    }
                    else {
                        dp[coinIndex][remainAmount] = -1;
                    }
                }
            }
            else {
                int minCoinNumber = INT_MAX;
                for (int coinNumber = 0; (coinNumber * currentCoin) <= remainAmount; coinNumber++) {
                    int newRemainAmount = remainAmount - (coinNumber * currentCoin);
                    if (dp[coinIndex + 1][newRemainAmount] != -1) {
                        int localMinCoinNumber = coinNumber + dp[coinIndex + 1][newRemainAmount];
                        if (localMinCoinNumber < minCoinNumber) {
                            minCoinNumber = localMinCoinNumber;
                        }
                    }
                }

                if (minCoinNumber != INT_MAX) {
                    dp[coinIndex][remainAmount] = minCoinNumber;
                }
                else {
                    dp[coinIndex][remainAmount] = -1;
                }
            }

            if ((coinIndex == 0) && (remainAmount == amount)) {
                min = dp[coinIndex][remainAmount];
                break;
            }
        }
    }

    for (int i = 0; i < coinsSize; i++) {
        free(dp[i]);
    }
    free(dp);

    return min;
}