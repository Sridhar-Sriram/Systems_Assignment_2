#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

static char myblock[5000];

typedef struct _metaData{
	size_t size;
	char use;

}metaData;

metaData*createNode(size_t, char);
void * mymalloc (size_t);

// creating Nodes for proper usage
metaData* createNode(size_t pointerSize, char usage){
    metaData* new_node = (metaData*)malloc(sizeof(metaData));
	new_node->size=pointerSize;
	new_node->use=usage;
	return new_node;
}

void * mymalloc(size_t size){

}
