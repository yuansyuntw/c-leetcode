int uniquePaths(int m, int n){
    int** table = calloc(sizeof(int *), m);
    for (int i=0;i<m;i++) {
        table[i] = calloc(sizeof(int), n);
        if (i==0) {
            for (int j=0;j<n;j++) {
                table[i][j] = 1;
            }
        } else {
            table[i][0] = 1;
        }
    }
    
    for (int i=1;i<m;i++) {
        for (int j=1;j<n;j++) {
            table[i][j] = table[i-1][j] + table[i][j-1];
        }
    }
    
    int reuslt = table[m-1][n-1];
    for (int i=0;i<m;i++) free(table[i]);
    free(table);
    return reuslt;
}