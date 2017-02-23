#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

void testA();
void testB();
void testC();
void testD();
void testE();
void testF();
metaData*createNode(size_t, char);

typedef Struct _metaData{
    sizet size;
    char use;
    
}metaData;

metaData * createNode(size_t pointerSize,char usage){
    metaData * meta=malloc(sizeof(metaData));
    metaData->size=pointerSize;
    metaData->use=usage;
    
}


int main(int argc, char** argv){
    printf("Testing testB \n");
    testB();
    return 0;
}

void testA(){
	int i;
	char ** pointer;
	for(i=0,i<1000,i++){
		pointer[i]=(char*)mymalloc(1);
	}

	for(i=0,i<1000,i++){
		pointer[i]=myfree();

	}
    
}

void testB(){
    int i =1;
    for(i =1 ; i <=1000; i++){
        char*testPointer = (char*)malloc(sizeof(char));
        free(testPointer);
    }
}

void testC(){
    
}

void testD(){
    
}

void testE(){
    
}

void testF(){
    
}
