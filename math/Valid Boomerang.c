float getSlope(int x1, int y1, int x2, int y2) {
    float m;
    if ((x1 - x2) == 0) {
        m = -1000;
        if (y1 == y2) {
            m = -1001;
        }
    } else {
        m = (float)(y1 - y2) / (float)(x1 - x2);
    }
    
    return m;
}

bool isBoomerang(int** points, int pointsSize, int* pointsColSize){
    float m1 = getSlope(points[0][0], points[0][1], points[1][0], points[1][1]);
    float m2 = getSlope(points[0][0], points[0][1], points[2][0], points[2][1]);
    if ((m1 == -1001) || (m2 == -1001)) {
        return false;
    }
    
    if (m1 == m2) {
        return false;
    } else {
        return true;
    }
}