int gNumCourses;

struct CourseInfo {
    int dependentCount;
    int* dependentCourse;
};

struct Course** gCourseInfos;

int* gIsVisitedArray;
int* gInVisitedInOneRoundArray;

bool canDiscover(int course) {
    // Beacuse we had seen all dependency for current course before, so we don't need to check again.
    if (gIsVisitedArray[course]) return true;
    
    // The node had visited that mean this cause a cycle.
    if (gInVisitedInOneRoundArray[course]) return false;
    
    // Make to one for checking cycle.
    gInVisitedInOneRoundArray[course] = 1;
    
    struct CourseInfo* courseInfo = gCourseInfos[course];
    int dependentCount = courseInfo->dependentCount;
    for (int d=0;d<dependentCount;d++) {
        int dependentCourse = courseInfo->dependentCourse[d];
        // The course had dependent course, but not visied, we check the course whether had finished.
        if (!canDiscover(dependentCourse)) {
            return false;
        }
    }
    
    // Cancel visited for backward recursive. We accomplish this by DFS's feature instead of using a stack.
    gInVisitedInOneRoundArray[course] = 0;

    // Visited all dependent course, make it to visited for skipping in next time.
    gIsVisitedArray[course] = 1;
    
    return true;
}

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize){
    gNumCourses = numCourses;
    gCourseInfos = malloc(sizeof(struct CourseInfo *) * numCourses);
    for (int c=0;c<numCourses;c++) {
        gCourseInfos[c] = malloc(sizeof(struct CourseInfo) * numCourses);
        struct CourseInfo* courseInfo = gCourseInfos[c];
        courseInfo->dependentCount = 0;
        courseInfo->dependentCourse = malloc(sizeof(int) * numCourses);
    }
    
    for (int p=0;p<prerequisitesSize;p++) {
        int course = prerequisites[p][0];
        int dependencyCourse = prerequisites[p][1];
        
        struct CourseInfo* courseInfo = gCourseInfos[course];
        int currentDependentCount = courseInfo->dependentCount;
        courseInfo->dependentCourse[currentDependentCount++] = dependencyCourse;
        courseInfo->dependentCount = currentDependentCount;
    }
    
    bool isCanFinish = true;
    gIsVisitedArray = calloc(sizeof(int), numCourses);
    for (int c=0;c<numCourses;c++) {
        // Only visit no checked course
        if (gIsVisitedArray[c] == 0) {
            gInVisitedInOneRoundArray = calloc(sizeof(int), numCourses);
            isCanFinish = canDiscover(c);
            free(gInVisitedInOneRoundArray);
            
            if (!isCanFinish) break;
        }
    }
    
    free(gIsVisitedArray);
    
    for (int c=0;c<numCourses;c++) {
        struct CourseInfo* courseInfo = gCourseInfos[c];
        free(courseInfo->dependentCourse);
        free(gCourseInfos[c]);
    }
    free(gCourseInfos);
    
    return isCanFinish;
}