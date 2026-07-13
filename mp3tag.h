#ifndef MP3TAG_H
#define MP3TAG_H

#include <stdio.h>
#include "types.h"

typedef struct
{
    char *filename;
    FILE *fptr;
    char *modify_option;
    char *modify_value;

} TagInfo;

#endif