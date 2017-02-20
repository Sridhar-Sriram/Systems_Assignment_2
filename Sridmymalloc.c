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

// creating Nodes for proper usage
metaData* createNode(size_t pointerSize, char usage){
	metaData* new_node = (metaData*)malloc(sizeof(metaData));
	Node->size=pointerSize;
	Node->use=usage;
	return new_node;
}

void * mymalloc(size_t size){
	if(myblock[0]==NULL){
		metaData Node=createNode(size,'y');
		return void * ptr=&myblock[sizeof(Node)];
	}




}
