void clearINode(int size, int **dependency, int *dependencyColSize, int node)
{
    for (int i = 0; i < size; i++)
    {
        if ((dependencyColSize[i] > 0) && (dependency[i][node] == 1))
        {
            dependencyColSize[i]--;
        }
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findOrder(int numCourses, int **prerequisites, int prerequisitesSize, int *prerequisitesColSize, int *returnSize)
{
    int *result = (int *)calloc(numCourses, sizeof(int));
    int resultCount = 0;

    int size = numCourses;

    int *isSkip = (int *)calloc(size, sizeof(int));
    int **dependency = (int **)calloc(size, sizeof(int *));
    int *dependencyColSize = (int *)calloc(size, sizeof(int));
    for (int i = 0; i < size; i++)
    {
        dependency[i] = (int *)calloc(size, sizeof(int));
    }

    for (int i = 0; i < prerequisitesSize; i++)
    {
        int colSize = prerequisitesColSize[i];
        if (colSize == 2)
        {
            int basicCourse = prerequisites[i][0];
            int prerequiredCourse = prerequisites[i][1];

            bool wasAdded = (dependency[basicCourse][prerequiredCourse] == 1);
            if (!wasAdded)
            {
                dependency[basicCourse][prerequiredCourse] = 1;
                dependencyColSize[basicCourse]++;
            }
        }
    }

    while (resultCount < numCourses)
    {
        bool isStop = true;

        for (int i = 0; i < numCourses; i++)
        {
            if (isSkip[i])
            {
                continue;
            }

            if (dependencyColSize[i] == 0)
            {
                isStop = false;
                result[resultCount] = i;
                resultCount++;
                if (resultCount >= numCourses)
                {
                    break;
                }

                isSkip[i] = 1;
                clearINode(size, dependency, dependencyColSize, i);
            }
        }

        if (isStop)
        {
            // Can not find a schedule
            resultCount = 0;
            break;
        }
    }

    for (int i=0; i<size; i++) {
        free(dependency[i]);
    }
    free(isSkip);
    free(dependencyColSize);

    *returnSize = resultCount;
    return result;
}
