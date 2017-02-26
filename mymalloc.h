#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 
void * mymalloc(size_t requested_size, char * file, int line);
void myfree(void * ptr, char * file, int line);