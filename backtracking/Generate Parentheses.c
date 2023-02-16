int gN;
int solutionCount;
char **solutions;

void addToSolutions(char *solution)
{
    int length = strlen(solution) + 1;
    char *newSolution = (char *)calloc(length, sizeof(char));
    sprintf(newSolution, "%s", solution);
    solutions[solutionCount++] = newSolution;
}

void removeLastChar(char *string)
{
    int length = strlen(string);
    string[length - 1] = '\0';
}

void backtracking(int openCount, int closeCount, char *solution)
{
    if ((openCount == gN) && (closeCount == gN))
    {
        addToSolutions(solution);
        return;
    }

    bool canAddOpenParenthesis = (openCount < gN);
    if (canAddOpenParenthesis)
    {
        sprintf(solution, "%s(", solution);
        backtracking(openCount + 1, closeCount, solution);
        removeLastChar(solution);
    }

    bool canAddCloseParenthesis = (closeCount < openCount);
    if (canAddCloseParenthesis)
    {
        sprintf(solution, "%s)", solution);
        backtracking(openCount, closeCount + 1, solution);
        removeLastChar(solution);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **generateParenthesis(int n, int *returnSize)
{
    gN = n;

    solutionCount = 0;
    int maxSolutionCount = 2;
    for (int i = 2; i <= n; i++)
    {
        maxSolutionCount = maxSolutionCount * (i + 1);
    }
    solutions = (char **)calloc(maxSolutionCount, sizeof(char *));

    int solutionLength = (n * 2 + 1);
    char *solution = (char *)calloc(solutionLength, sizeof(char));
    backtracking(0, 0, solution);
    free(solution);

    *returnSize = solutionCount;
    return solutions;
}
