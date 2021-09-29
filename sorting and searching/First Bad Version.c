// The API isBadVersion is defined for you.
// bool isBadVersion(int version);


int checkBadVersion(int startVersion, int endVersion) {
    if ((endVersion - startVersion) == 0) {
        if (isBadVersion(startVersion)) {
            return startVersion;
        } else {
            return startVersion + 1;
        }
    } else if ((endVersion - startVersion) < 0) {
        return startVersion;
    }
    
    int middleVersion = ((long)startVersion + (long)endVersion)/2;
    if (!isBadVersion(middleVersion)) {
        startVersion = middleVersion + 1;
        return checkBadVersion(startVersion, endVersion);
    } else {
        endVersion = middleVersion - 1;
        return checkBadVersion(startVersion, endVersion);
    }
}

int firstBadVersion(int n) {
    return checkBadVersion(1, n);
}