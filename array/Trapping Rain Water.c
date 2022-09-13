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

    while (l < r) {
        if (maxLeft < maxRight) {
            if ((maxLeft - height[l]) > 0) {
                result += (maxLeft - height[l]);
            }

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