int fib(int n) {
    if (n == 0) {
        return 0;
    }
    
    int previousFib = 0;
    int currentFib = 1;
    int newFib;
    for (int i=0;i<n;i++) {
        newFib = previousFib + currentFib;
        previousFib = currentFib;
        currentFib = newFib;
    }
    
    return currentFib;
}

int climbStairs(int n){
    return fib(n);
}