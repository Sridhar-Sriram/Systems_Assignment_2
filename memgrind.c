#include <stdio.h>
 #include <string.h>
 #include <ctype.h>
 #include <stdlib.h>
 #include <errno.h>
 #include <unistd.h>
 
 typedef Struct _metaData{
 	size_t size;
 	char use;
 
 }metaData;
 
 metaData * createNode(size_t pointerSize,char usage){
 	metaData * meta=malloc(sizeof(metaData));
 	metaData->size=pointerSize;
	metaData->use=usage;
 	
 }
 
 int main(int argc, char ** argv){
 	printf(sizeof(metaData));
 	return 0;
 }
