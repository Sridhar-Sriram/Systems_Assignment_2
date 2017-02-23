#include<stdio.h>
#include<stdlib.h>

void testA();
void testB();
void testC();
void testD();
void testE();
void testF();
metaData*createNode(size_t, char);

typedef Struct _metaData{
    size_t size;
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
