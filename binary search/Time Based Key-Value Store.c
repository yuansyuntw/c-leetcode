typedef struct {
    int timestamp;
    char* value;
} Timestamp;

typedef struct {
    char* key;
    int timestampSize;
    int timestampCount;
    Timestamp** timestamps;
    UT_hash_handle hh;
} Bucket;

typedef struct {
    Bucket *hashtable;
} TimeMap;

TimeMap* timeMapCreate() {
    TimeMap* timeMap = calloc(sizeof(TimeMap), 1);
    timeMap->hashtable = NULL;
    return timeMap;
}

void timeMapSet(TimeMap* obj, char * key, char * value, int timestamp) {
    Bucket* bucket = NULL;
    HASH_FIND_STR(obj->hashtable, key, bucket);
    
    bool isNotInit = (bucket == NULL);
    if (isNotInit) {
        bucket = calloc(sizeof(Bucket), 1);
        bucket->key = key;
        bucket->timestampSize = 200000;
        bucket->timestampCount = 0;
        bucket->timestamps = calloc(sizeof(Timestamp *), bucket->timestampSize);
        if (bucket->timestamps == NULL) {
            printf("Out of memory\n");
            return;
        }
        
        HASH_ADD_KEYPTR(hh, obj->hashtable, key, strlen(key), bucket);
    }
    
    Timestamp* newTimestamp = calloc(sizeof(Timestamp), 1);
    newTimestamp->timestamp = timestamp;
    newTimestamp->value = value;

    // Because the timestamp was add by increased so that we can append the value into the array
    bucket->timestamps[bucket->timestampCount++] = newTimestamp;
}

char * timeMapGet(TimeMap* obj, char * key, int timestamp) {
    Bucket* bucket = NULL;
    HASH_FIND_STR(obj->hashtable, key, bucket);
    
    bool isNotFound = (bucket == NULL);
    if (isNotFound) {
        return "";
    }
    
    int lowerBound = 0;
    int upperBound = bucket->timestampCount - 1;
    
    char* result = "";
    while (lowerBound <= upperBound) {
        int middleIndex = (lowerBound + upperBound) / 2;

        // The key point is here. We find the value in a sorted timestamp array
        // This only has log(n). But, if we use a for-loop, it needs a (n) time complexity.
        if (bucket->timestamps[middleIndex]->timestamp <= timestamp) {
            result = bucket->timestamps[middleIndex]->value;
            if (bucket->timestamps[middleIndex]->timestamp == timestamp) {
                break;
            }
            
            lowerBound = middleIndex + 1;
        } else {
            upperBound = middleIndex - 1;
        }
    }
    
    return result;
}

void timeMapFree(TimeMap* obj) {
    Bucket* bucket = NULL;
    Bucket* temp = NULL;
    HASH_ITER(hh, obj->hashtable, bucket, temp) {
        for (int t=0; t<bucket->timestampCount; t++) {
            free(bucket->timestamps[t]);
        }

        free(bucket->timestamps);
    };
    
    free(obj);
}

/**
 * Your TimeMap struct will be instantiated and called as such:
 * TimeMap* obj = timeMapCreate();
 * timeMapSet(obj, key, value, timestamp);
 
 * char * param_2 = timeMapGet(obj, key, timestamp);
 
 * timeMapFree(obj);
*/