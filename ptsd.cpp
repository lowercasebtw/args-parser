#include "ptsd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ptsd::strslice(char* input, int start, int end) {
    // check if eof
    int input_len = strlen(input);
    if (end > input_len) 
        end = input_len;
    if (start < 0)
        start = 0;

    // Make sure no weirdness!
    if (end < start)
        end = start;
    if (start > end)
        start = end;

    int length = end - start;
    char* output = (char*) malloc(length + 1);
    if (output == nullptr) {
        fprintf(stderr, "ERROR: failed to malloc! buy ram LOL");
        return nullptr;
    }
        
    memcpy(output, input + start, length);
    output[length] = 0;
    return output;
}

int ptsd::strindexof(char* str, char ch) {
    int len = strlen(str);
    if (len == 0)
        return -1;
    for (int i = 0; i < len; ++i)
        if (str[i] == ch)
            return i;
    return -1;
}

bool ptsd::strcontains(char* str, char ch) {
    return strindexof(str, ch) != -1;
}