// 1. find the row
// 2. find the col
// 3. return the reuslt

bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target)
{

    int min = matrix[0][0];
    int max = matrix[matrixSize - 1][matrixColSize[0] - 1];
    if ((target < min) || (target > max))
    {
        return false;
    }

    int top = 0;
    int bottom = matrixSize - 1; 
    while (top <= bottom)
    {
        int middle = (top + bottom) / 2;    
        int middleValue = matrix[middle][0]; 
        if (middleValue == target)
        {
            return true;
        }
        else if (middleValue >= target)
        {
            bottom = middle - 1;
        }
        else
        {
            top = middle + 1;
        }
    }

    int row = 0;
    if (top > matrixSize - 1) {
        // Only one row case.
        row = matrixSize - 1;
    } else {
        if (target > matrix[top][0])
        {
            row = top;
        }
        else
        {
            row = top - 1; 
        }
    }

    int left = 0;                       
    int right = matrixColSize[row] - 1; 
    while (left <= right)
    {
        int middle = (left + right) / 2;       
        int middleValue = matrix[row][middle]; 
        if (middleValue == target)
        {
            return true;
        }
        else if (middleValue >= target)
        {
            right = middle - 1;
        }
        else
        {
            left = middle + 1; 
        }
    }

    return false;
}