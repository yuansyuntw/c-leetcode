int subtractProductAndSum(int n){
    int digit = n % 10;
    int productResult = digit;
    int sumResult = digit;
    n = n / 10;

    while(n > 0) {
        digit = n % 10;
        productResult = productResult * digit;
        sumResult = sumResult + digit;
        n = n / 10;
    }
    
    return productResult - sumResult;   
}