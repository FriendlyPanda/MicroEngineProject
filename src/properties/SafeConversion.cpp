//
// Created by janha on 14/03/2024.
//
#include <cstdlib>

int stringToIntSafe(char *str, int backup) {
    int endValue;
    char * conversionError = nullptr;
    endValue = strtol(str, &conversionError, 10);
    if(*conversionError){
        return backup;
    }
    return endValue;
}