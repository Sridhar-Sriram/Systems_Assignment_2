#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

static char myblock[5000];

typedef Struct _metaData{
	size_t size;
	char use;

}metaData;

createNode(size_t pointerSize,char usage){
	metaData->size=pointerSize;
	metaData->use=usage;
}

void * malloc(size_t size){
	metaData * meta=createNode



}