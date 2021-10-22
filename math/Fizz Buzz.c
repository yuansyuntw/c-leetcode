typedef struct {
    int index;
    char* appendedContent;
} Information;


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** fizzBuzz(int n, int* returnSize){
    char** returnArray = malloc(sizeof(char*) * n);
    *returnSize = n;
    
    int informationsSize = 2;
    Information** informations = malloc(sizeof(Information*) * informationsSize);
    
    informations[0] = malloc(sizeof(Information));
    informations[0]->index = 3;
    informations[0]->appendedContent = "Fizz";
    
    informations[1] = malloc(sizeof(Information));
    informations[1]->index = 5;
    informations[1]->appendedContent = "Buzz";
    
    for(int i=0; i<n; i++) {
        returnArray[i] = (char*)malloc(sizeof(char)*10);
        sprintf(returnArray[i], "");
        
        bool isAppendContent = false;
        for(int j=0; j<informationsSize; j++) {
            if (((i+1) % informations[j]->index) == 0) {
                isAppendContent = true;
                sprintf(returnArray[i], "%s%s", returnArray[i], informations[j]->appendedContent);
            }
        }
        
        if (!isAppendContent) {
            sprintf(returnArray[i], "%s%d", returnArray[i], i+1);
        }
    }
    
    for (int i=0; i<informationsSize; i++) {
        free(informations[i]);
    }

    free(informations);
    return returnArray;
}