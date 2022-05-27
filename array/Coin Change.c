// For this solution, we chose a coin in the first step.
int coinChange(int* coins, int coinsSize, int amount){
    int* dp = (int *)calloc(sizeof(int), (amount + 1));
    for (int i = 0; i <= amount; i++) {
        dp[i] = amount+1;
    }
    dp[0] = 0;

    for (int a = 1; a <= amount; a++) {
        for (int i = 0; i < coinsSize; i++) {
            int coin = coins[i];
            if ((a - coin) >= 0) {
                int min = dp[a];
                int newNumer = 1 + dp[a - coin];
                if (newNumer < min) {
                    min = newNumer;
                }

                dp[a] = min;
            }
        }
    }

    int min = (dp[amount] != (amount + 1)) ? dp[amount] : -1;
    free(dp);

    return min;
}