#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// Returns the index where the key should be stored
int HashIndex(const char* key) {
    int sum = 0; // intialized with 0
    for (const char* c = key; *c != '\0'; c++) {
        sum = (sum + *c)%MAP_MAX;
    }
    return sum;
}

// Allocates memory for the HashMap
HashMap* HashInit() {
    HashMap* map = malloc(sizeof(HashMap));
    if (map) {
        memset(map->data, 0, sizeof(map->data));
    }
    return map;
}

// Inserts PairValue into the map, if the value exists, increase ValueCount
void HashAdd(HashMap *map, PairValue *value) {
    if (map == NULL || value == NULL) {
        return;
    }

    // Check if the key already exists in the map
    PairValue* existing = HashFind(map, value->KeyName);
    if (existing) {
        // Key exists: increment the ValueCount
        existing->ValueCount++;
        return;
    }

    // Key does not exist: insert the new PairValue
    int idx = HashIndex(value->KeyName);
    value->Next = map->data[idx];
    map->data[idx] = value;
}

// Returns PairValue from the map if a given key is found
PairValue* HashFind(HashMap *map, const char* key) {
    if (map == NULL || key == NULL) {
        return NULL;
    }

    unsigned idx = HashIndex(key);
    for (PairValue* val = map->data[idx]; val != NULL; val = val->Next) {
        if (strcmp(val->KeyName, key) == 0) {
            return val;
        }
    }
    return NULL;
}

// Deletes the entry with the given key from the map
void HashDelete(HashMap *map, const char* key) {
    if (map == NULL || key == NULL) {
        return;
    }

    unsigned idx = HashIndex(key);
    for (PairValue* val = map->data[idx], *prev = NULL; val != NULL; prev = val, val = val->Next) {
        if (strcmp(val->KeyName, key) == 0) {
            if (prev)
                prev->Next = val->Next;
            else
                map->data[idx] = val->Next;
            return;
        }
    }
}

// Prints all content of the map
void HashDump(HashMap *map) {
    if (map == NULL) {
        return;
    }

    for (unsigned i = 0; i < MAP_MAX; i++) {
        for (PairValue* val = map->data[i]; val != NULL; val = val->Next) {
            printf("%s %u\n", val->KeyName, val->ValueCount);
        }
    }
}

int main() {
    HashMap* map = HashInit();
    printf("%s\n", "HashInit() Successful");
    
    PairValue pv1 = { .KeyName = "test_key", .ValueCount = 1, .Next = NULL };
    PairValue pv2 = { .KeyName = "other_key", .ValueCount = 1, .Next = NULL };
    
    printf("HashAdd(map, '%s')\n", pv1.KeyName);
    HashAdd(map, &pv1);

    printf("HashAdd(map, '%s')\n", pv1.KeyName);
    HashAdd(map, &pv1);

    printf("HashAdd(map, '%s')\n", pv2.KeyName);
    HashAdd(map, &pv2);

    printf("HashFind(map, %s) = ", pv1.KeyName);
    PairValue* result = HashFind(map, pv1.KeyName);
    if(result) {
        printf("{'%s': %d}\n", result->KeyName, result->ValueCount);
    }
    else {
        printf("%s\n", "Not found");
    }
    
    printf("%s", "HashDump(map) = ");
    HashDump(map);

    printf("HashDelete(map, '%s')\n", pv1.KeyName);
    HashDelete(map, pv1.KeyName);

    printf("HashFind(map, %s) = ", pv1.KeyName);
    result = HashFind(map, pv1.KeyName); 
    if(result) {
        printf("{'%s': %d}\n", result->KeyName, result->ValueCount);
    }
    else {
        printf("%s\n", "Not found");
    }

    printf("%s", "HashDump(map) = ");
    HashDump(map);

    free(map);
}