#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mymalloc.h"
#include "Micamymalloc.c"
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

int testA(){
    int run=0,time=0;
    
    while(run<100){
        struct timeval start, end;
        gettimeofday(&start, NULL);
        int i;
        char * pointerArray[1000];
        for(i=0;i<1000;i++){
            pointerArray[i]=(char*)malloc(1);
            if(pointerArray[i]==NULL){
                break;
            }
        }
        
        for(i=0;i<1000;i++){
            //printf("i: %d\n",i);
            //printf("address of: %p\n",pointerArray[i]);
            if(pointerArray[i]==NULL){
                
                break;
            }
            free(pointerArray[i]);
        }
        gettimeofday(&end, NULL);
        time+=(end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec);
    run++;
    }
    return time/100;
    
}

int testB(){
    int run=0,time=0;
    while(run<100){
        struct timeval start, end;
        gettimeofday(&start, NULL);
        int i;
        for(i =1 ; i <=1000; i++){
            char*testPointer = (char*)malloc(sizeof(char));
            free(testPointer);
        }
        gettimeofday(&end, NULL);
        time+=(end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec);
    run++;
    }
    return time/100;
}

int testC(){
    int run=0,time=0;
    while(run<100){
        struct timeval start, end;
        gettimeofday(&start, NULL);
        int iterator=0,place=0;
        char *pointerArray[1000];
        while(iterator!=1000){
            int random = rand() % 2;
            if(random==0){
                pointerArray[place]=(char*)malloc(1);
                if(pointerArray[place]==NULL){
                    //no more space
                    //printf("BREAKING\n");
                    break;
                }
                place++;
                iterator++; 
            }

            else if(random==1){
                if(place<=0){
                    place=0;
                    continue;
                }
                if(pointerArray[place]==NULL){
                    continue;
                }
                place--;
                free(pointerArray[place]);
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
        gettimeofday(&end, NULL);
        time+=(end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec);
    run++;
    }
    return time/100;
    
}

int testD(){
    int run=0,time=0;
    // while(run<100){
        struct timeval start, end;
        gettimeofday(&start, NULL);
        int iterator=0,place=0;
        char *pointerArray[1000];
        while(iterator!=1000){
            int random = rand() % 2;
            // printf("random: %d\n",random);
            // printf("iterator: %d\n",iterator);
            int randomFree = rand() % 64 +1;
            if(random==0){
                pointerArray[place]=(char*)malloc(randomFree);

                if(pointerArray[place]==NULL){
                    random=1;
                    continue;
                }
                place++;
                iterator++;
            }
            
            if(random==1){

                if(place<=0){
                    place=0;
                    continue;
                }
                if(pointerArray[place]==NULL){
                    continue;
                }
                place--;
                free(pointerArray[place]);
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
        gettimeofday(&end, NULL);
        time+=(end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec);
    run++;
    // }
    return time/100;
    
}

void testE(){
    
}

void testF(){
    
}

int main(int argc, char** argv){

    printf("Test A's time: %d microseconds\n", testA());
    printf("Test B's time: %d microseconds\n", testB());
   printf("Test C's time: %d microseconds\n", testC());
    printf("Test D's time: %d microseconds\n", testD());
    // printf("Test E's average time was %d microseconds\n", testE());
    // printf("Test F's average time was %d microseconds\n", testF());
    return 0;
}
