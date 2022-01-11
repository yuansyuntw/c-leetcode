int maxArea(int* height, int heightSize){

    int result = 0;
    for (int i=0; i<heightSize; i++) {
        for (int j=0; j<i; j++) {
            int minHeight;
            if (height[j] < height[i]) {
                minHeight = height[j];
            } else {
                minHeight = height[i];
            }
            
            int area = minHeight * (i - j);
            if (area > result) {
                result = area;;
            }
            
            if (height[j] > height[i]) {
                break;
            }
        }
    }
    
    return result;
}