#ifndef MALLOC_H_
#define MALLOC_H_

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)

void * mymalloc(size_t requested_size,char * file, int line);
void myfree(void * ptr,char * file, int line);

#endif

