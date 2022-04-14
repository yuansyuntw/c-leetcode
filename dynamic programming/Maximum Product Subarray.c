int max(int value1, int value2, int value3) {
    int result = value1;
    if (value2 > result) result = value2;
    if (value3 > result) result = value3;
    return result;
}

int min(int value1, int value2, int value3) {
    int result = value1;
    if (value2 < result) result = value2;
    if (value3 < result) result = value3;
    return result;
}

int maxProduct(int* nums, int numsSize){
    int result = nums[0];
    int minProduct = 1; // *Keep the min product. Because the result may be positive when the min product multiple a negative number
    int maxProduct = 1;
    
    for (int i=0;i<numsSize;i++) {
        if (nums[i] == 0) {
            if (nums[i] > result) result = nums[i];
            
            // Because any number multiple zero is zero. When encountering zero, we should reset the min product and max product.
            minProduct = 1;
            maxProduct = 1;
            continue;
        }
        
        int product1 = minProduct * nums[i];
        int product2 = maxProduct * nums[i];

        maxProduct = max(product1, product2, nums[i]);
        minProduct = min(product1, product2, nums[i]);

        if (maxProduct > result) result = maxProduct;
    }

    return result;
}