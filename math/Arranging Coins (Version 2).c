long getSum(int a, int an, int n) {
    return ((long)(a + an)*n)/2;
}

int arrangeCoins(int n){
    int j= floor(sqrt(n));
    long size = getSum(1, j, j);
    while (size <= n) {
        j++;
        size = getSum(1, j, j);
    }
    
    if (size == n) {
        return j;
    } else {
        return j - 1;
    }
}