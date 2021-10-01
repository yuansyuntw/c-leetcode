int maxProfit(int* prices, int pricesSize){
    if (pricesSize == 1) {
        return 0;
    }
    
    int maxValue = 0;
    int minValue = prices[0];
    
    for (int i=0;i<pricesSize;i++) {
        if (prices[i] < minValue) {
            minValue = prices[i];
        }
        
        int value = prices[i] - minValue;
        if (value > maxValue) {
            maxValue = value;
        }
    }
    
    return maxValue;
}