int hammingDistance(int x, int y){
    int difference = x ^ y;
    int distance = 0;
    while (difference > 0) {
        difference = difference & (difference-1);
        distance++;
    }
    
    return distance;
}