int mySqrt(int x){
    long min = 1;
    long max = x;
    
    while (min <= max) {
        long middle = (min + max) /2;
        if (middle * middle <= x) {
            min = middle + 1;
        } else {
            max = middle - 1;
        }
    }

    return max;
}