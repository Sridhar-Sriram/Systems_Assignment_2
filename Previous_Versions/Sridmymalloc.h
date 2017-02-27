#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)

typedef struct _metaData{
	size_t size;
	char use;

}metaData;
 
void * mymalloc(size_t requested_size,char * file, int line);
void myfree(void * ptr,char * file, int line);
