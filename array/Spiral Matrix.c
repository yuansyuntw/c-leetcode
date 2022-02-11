
enum DirectionEnum {DirectionRight, DirectionDown, DirectionLeft, DirectionUp};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize){
    enum DirectionEnum currentDirection = DirectionRight;
    int currentCount = 0;
    int maxCount = matrixSize * (*matrixColSize);
    int currentX = 0, currentY = 0;
    
    int* resulttArray = calloc(maxCount, sizeof(int));
    resulttArray[currentCount++] = matrix[0][0];
    
    int m = (*matrixColSize);
    int n = matrixSize;
    int changeDirectionCount = 0;
    int limitedX = m;
    int limitedY = n;
    
    while (currentCount < maxCount) {
        bool isChangeRotation = false;
        switch (currentDirection) {
            case DirectionRight: {
                if ((currentX + 1) >= limitedX) {
                    currentDirection = DirectionDown;
                    isChangeRotation = true;
                    break;
                }
                
                currentX++;
                break;
            }
            case DirectionDown: {
                if ((currentY + 1) >= limitedY) {
                    currentDirection = DirectionLeft;
                    isChangeRotation = true;
                    break;
                }
                
                currentY++;
                break;
            }
            case DirectionLeft: {
                if ((currentX - 1) < limitedX) {
                    currentDirection = DirectionUp;
                    isChangeRotation = true;
                    break;
                }
                
                currentX--;
                break;
            }
            case DirectionUp: {
                if ((currentY - 1) < limitedY) {
                    currentDirection = DirectionRight;
                    isChangeRotation = true;
                    break;
                }
                
                currentY--;
                break;
            }
        }
        
        if (isChangeRotation) {
            changeDirectionCount++;
            if (changeDirectionCount >= 3) {
                if ((currentDirection == DirectionDown) || (currentDirection == DirectionUp)) {
                    n--;
                } else {
                    m--;
                }
            }
            
            switch (currentDirection) {
                case DirectionRight: {
                    limitedX = currentX + m;
                    break;
                }
                case DirectionDown: {
                    limitedY = currentY + n; 
                    break;
                }
                case DirectionLeft: {
                    limitedX = currentX + 1 - m;
                    break;
                }
                case DirectionUp: {
                    limitedY = currentY + 1 - n;
                    break;
                }
            }

            continue;
        }
        
        resulttArray[currentCount++] = matrix[currentY][currentX];
    }
    
    *returnSize = currentCount;
    return resulttArray;
}