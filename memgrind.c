#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

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
    int iterator=0,place=0;
    char **pointerArray[1000];
    while(iterator!=1000){
        int r = rand() % 2;
        if(r=0){
            char * pointer=malloc(1);
            pointerArray[place];
            place++;
            iterator++;
            
        }
        if(r=1){
            if(place<=0){
                continue;
            }
            free(pointerArray[place]);
            place--;
        }
    }
    //need to free all the leftover pointers
    
}

void testD(){
    
}

void testE(){
    
}

void testF(){
    
}

int main(int argc, char** argv){
    printf("Testing testB \n");
    testB();
    return 0;
}
