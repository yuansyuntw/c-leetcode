
long getSum(int an) {
    int d = an;
    return ((long)(1 + an)*d)/2;
}

int arrangeCoins(int n){
    long left = 1;
    long right = n;
    long middle;
    long spaceSize;
    while (left <= right) {
        middle = (left + right)/2;
        spaceSize = getSum(middle);
        if ((spaceSize - n) == 0) {
            return middle;
        }
            
        if ((spaceSize - n) < 0) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    
    return right;
}
