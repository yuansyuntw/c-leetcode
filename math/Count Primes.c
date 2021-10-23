int countPrimes(int n){
    if (n == 0) {
        return 0;
    }
    
    if (n == 1) {
        return 0;
    }
    
    bool* notPrimeTable = calloc((n+1), sizeof(bool));
    notPrimeTable[0] = true;
    notPrimeTable[1] = true;
    
    // i <= sqrt(n)
    for (int i=2; i*i<=n; i++) {
        if (notPrimeTable[i] == false) {
            for(int j=i*i; j<=n; j+=i) {
                notPrimeTable[j] = true;
            }
        }
    }
    
    int count = 0;
    for (int i=2; i<n; i++) {
        if (notPrimeTable[i] == false) {
            count++;
        }
    }
    
    free(notPrimeTable);
    return count;
}