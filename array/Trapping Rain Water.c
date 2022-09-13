int max(int valueA, int valueB) {
    if (valueA > valueB) {
        return valueA;
    }

    return valueB;
}

int trap(int* height, int heightSize) {
    int maxLeft = height[0];
    int maxRight = height[heightSize-1];
    int result = 0;

    int l = 0;
    int r = heightSize - 1;

    // this method put two processing together:
    while (l < r) {
        // 1. pick the smaller height
        if (maxLeft < maxRight) {
            // check whether is a trap
            if ((maxLeft - height[l]) > 0) {
                result += (maxLeft - height[l]);
            }

            // 2. forward the max left value
            l++;
            maxLeft = max(maxLeft, height[l]);
        }
        else {
            if ((maxRight - height[r]) > 0) {
                result += (maxRight - height[r]);
            }

            r--;
            maxRight = max(maxRight, height[r]);
        }
    }

    return result;
}