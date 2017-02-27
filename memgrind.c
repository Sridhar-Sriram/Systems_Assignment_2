#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mymalloc.h"
#include "mymalloc.c"

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
        int num_malloc_calls=0,place=0;
        char *pointerArray[1000];
        //num_malloc_calls keeps track of the number of malloc calls made
        while(num_malloc_calls<1000){
            printf("iterator : %d\n",num_malloc_calls);
            int random = rand() % 2;
            if(random==0){
                pointerArray[place]=(char*)malloc(1);
                if(pointerArray[place]==NULL){
                    //no more space
                    //printf("BREAKING\n");
                    break;
                }   
                num_malloc_calls++;
                place++;
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
                pointerArray[place] = NULL;

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
    while(run<100){
        struct timeval start, end;
        gettimeofday(&start, NULL);
        int num_malloc_calls=0,place=0;
        char *pointerArray[1000];
        while(num_malloc_calls<1000){
            //printf("iterator : %d\n", num_malloc_calls);
            int random = rand() % 2;
            int randomFree = rand() % 64 +1;
            if(random==0){
                pointerArray[place]=(char*)malloc(randomFree);
                if(pointerArray[place]==NULL){
                    free(pointerArray[place-1]);
                    pointerArray[place-1] = NULL;
                    continue;
                }
                place++;
                num_malloc_calls++;
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
                pointerArray[place] = NULL;

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

int testE(){
    /*
     continuous malloc calls of size 1 to capacity
     then, free every OTHER element
     then, again until capacity
     testing robustness
     */
    int run=0,time=0;
    //while(run<100){
        struct timeval start, end;
        gettimeofday(&start, NULL);
        int iterator=0,place=0;
        char *pointerArray[1000];
        while(iterator <1000){
            pointerArray[place] = (char*)malloc(5);
            if(pointerArray[place] == NULL){
                break;
            }
            place++;
        }
        int placerep = place;
        place = 0;
        while(place<placerep){
            free(pointerArray[place]);
            pointerArray[place] = NULL;
            place +=2;
        }
        gettimeofday(&end, NULL);
        time+=(end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec);
        run++;
    // }
    return time/100;
}

int testF(){
     int run=0,time=0;
    //while(run<100){
        struct timeval start, end;
        gettimeofday(&start, NULL);
        int iterator=0,place=0;
        char *pointerArray[1000];
        while(iterator <1000){
            pointerArray[place] = (char*)malloc(5);
            if(pointerArray[place] == NULL){
                break;
            }
            place++;
        }
        int placerep = place;
        place = 0;
        for(place=0;place<placerep-2;place++){
            free(pointerArray[place]);
            place++;
            free(pointerArray[place]);
            place++;
        }
        gettimeofday(&end, NULL);
        time+=(end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec);
        run++;
    // }
    return time/100;
    
}

int main(int argc, char** argv){
    if(argc>1){
        fprintf(stderr, "ERROR: Incorrect amount of arguments.\n");
        return -1;
    }

    // printf("Test A's average time: %d microseconds\n", testA());
    // printf("Test B's average time: %d microseconds\n", testB());
    // printf("Test C's average time: %d microseconds\n", testC());
     printf("Test D's average time: %d microseconds\n", testD());
    //printf("Test E's average time was %d microseconds\n", testE());
     //printf("Test F's average time was %d microseconds\n", testF());
    return 0;
}
