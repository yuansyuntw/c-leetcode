char** g_board;
int g_boardSize;
int g_boardColSize;

char* g_word;
int g_wordSize;

bool solve(int seenCount, int targetR, int targetC) {
    if ((targetR < 0) || (targetR >= g_boardSize) || (targetC < 0) || (targetC >= g_boardColSize) || (g_board[targetR][targetC] == '-')) {
        return false;
    }
    
    if (g_board[targetR][targetC] != g_word[seenCount]) {
        return false;
    } 
    
    g_board[targetR][targetC] = '-';
    seenCount++;

    if (seenCount == g_wordSize) return true;
    
    bool isSolve = false;
    
    // up
    if (!isSolve && solve(seenCount, targetR - 1, targetC)) {
        isSolve = true;
    }
    
    // right
    if (!isSolve && solve(seenCount, targetR, targetC + 1)) {
        isSolve = true;
    }
    
    // down
    if (!isSolve && solve(seenCount, targetR + 1, targetC)) {
        isSolve = true;
    }
    
    // left
    if (!isSolve && solve(seenCount, targetR, targetC - 1)) {
        isSolve = true;
    }

    // Cancel the seen tag
    if (!isSolve) {    
        g_board[targetR][targetC] = g_word[seenCount - 1];
    }
    
    return isSolve;
}


bool exist(char** board, int boardSize, int* boardColSize, char * word){
    g_board = board;
    g_boardSize = boardSize;
    g_boardColSize = *boardColSize;
    
    g_word = word;
    g_wordSize = strlen(word);
    
    for (int r=0; r<boardSize; r++) {
        for (int c=0; c<g_boardColSize; c++) {
            if (board[r][c] == word[0]) {
                int seenCount = 0;
                bool isSolve = false;
                if (solve(seenCount, r, c)) isSolve = true;
                if (isSolve) return true;
            }
        }
    }
    
    return false;
}