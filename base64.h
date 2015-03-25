#ifndef BASE64_H
#define BASE64_H

#include <stdio.h>
typedef unsigned char BYTE;
extern void encode(FILE* in, FILE *out);
extern void decode(FILE* in, FILE *out);

#endif
