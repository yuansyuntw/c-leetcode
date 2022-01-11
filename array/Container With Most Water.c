int maxArea(int* height, int heightSize){
    int result = 0;
    int leftIndex = 0;
    int rightIndex = heightSize - 1;
    while (leftIndex < rightIndex) {
        if (height[leftIndex] < height[rightIndex]) {
            int area = height[leftIndex] * (rightIndex - leftIndex);
            if (area > result) result = area;
            // Key point is here.
            // Because the left index is smaller than the right index,
            // we hope to get a large height by increasing the left index.
            leftIndex++;
        } else {
            int area = height[rightIndex] * (rightIndex - leftIndex);
            if (area > result) result = area;
            rightIndex--;
        }
    }
    
    return result;
}