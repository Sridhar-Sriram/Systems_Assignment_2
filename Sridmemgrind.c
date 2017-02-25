#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include "mymalloc.h"




int testA(){
    int run=0,time=0;
    
    while(run<100){
        struct timeval start, end;
        gettimeofday(&start, NULL);
        int i;
        char * pointerArray[1000];
        for(i=0,i<1000,i++){
            pointerArray[i]=(char*)malloc(1);
            if(pointerArray[i]==NULL){
                break;
            }
        }
        
        for(i=0,i<1000,i++){
            free(pointerArray[i]);
            i++;
        }
        gettimeofday(&end, NULL);
        time+=(end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec);
    }
    return time/100;
    
}

void testB(){
    int run=0;
    while(run<100){
        int i;
        for(i =1 ; i <=1000; i++){
            char*testPointer = (char*)malloc(sizeof(char));
            free(testPointer);
        }
    }
}

void testC(){
    int run=0;
    while(run<100){
        int iterator=0,place=0;
        char *pointerArray[1000];
        while(iterator!=1000){
            int random = rand() % 2;
            if(random==0){
                pointerArray[place]=malloc(1);
                if(pointerArray[place]==NULL){
                    //no more space
                    break;
                }
                place++;
                iterator++;
                
            }
            else if(random==1){
                if(place<0){
                    place=0;
                    continue;
                }
                if(pointerArray[place]==NULL){
                    continue;
                }
                free(pointerArray[place]);
                place--;
            }
        }
        int length=0;
        //Freeing all pointers after malloc 1000 times.
        while(length<1000){
            if(pointerArray[length]==NULL){
                break;
            }
            free(pointerArray[length]);
            length++;
        }
    }
    
}

void testD(){
    int run=0
    while(run<100){
        int iterator=0,place=0;
        char *pointerArray[1000];
        while(iterator!=1000){
            int random = rand() % 2;
            int randomFree = rand() % 64 +1;
            if(random==0){
                pointerArray[place]=malloc(randomFree);
                if(pointerArray[place]==NULL){
                    place--;
                    random=1;
                }
                else{
                    place++;
                    iterator++;
                }
            }
            
            if(random==1){
                if(place<0){
                    place=0;
                    continue;
                }
                if(pointerArray[place]==NULL){
                    continue;
                }
                free(pointerArray[place]);
                place--;
            }
        }
        int length=0;
        //Freeing all pointers after malloc 1000 times.
        while(length<1000){
            if(pointerArray[length]==NULL){
                break;
            }
            free(pointerArray[length]);
            length++;
        }
    }
    
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
