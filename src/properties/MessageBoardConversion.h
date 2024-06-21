//
// Created by janha on 28/04/2024.
//

#ifndef MEP_MESSAGEBOARDCONVERSION_H
#define MEP_MESSAGEBOARDCONVERSION_H
#include <cstdlib>

int stringToIntSafe(const char *str, int backup) {
    int endValue;
    char * conversionError = nullptr;
    endValue = strtol(str, &conversionError, 10);
    if(*conversionError){
        return backup;
    }
    return endValue;
}

#endif //MEP_MESSAGEBOARDCONVERSION_H
