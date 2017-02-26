#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mymalloc.h"
<<<<<<< HEAD



=======
#include "Micamymalloc.c"
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)
>>>>>>> e99e1aafb4817a2970e8434163e487873ff4373b

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
<<<<<<< HEAD
        run++;
=======
    run++;
>>>>>>> e99e1aafb4817a2970e8434163e487873ff4373b
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
<<<<<<< HEAD
        run++;
=======
    run++;
>>>>>>> e99e1aafb4817a2970e8434163e487873ff4373b
    }
    return time/100;
}

int testC(){
    int run=0,time=0;
    while(run<100){
        struct timeval start, end;
        gettimeofday(&start, NULL);
<<<<<<< HEAD
        int num_malloc_calls=0,place=0;
=======
        int iterator=0,place=0;
>>>>>>> e99e1aafb4817a2970e8434163e487873ff4373b
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
<<<<<<< HEAD
                
                num_malloc_calls++;
                place++;
            }
            
=======
                place++;
                iterator++; 
            }

>>>>>>> e99e1aafb4817a2970e8434163e487873ff4373b
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
<<<<<<< HEAD
                pointerArray[place] = NULL;
=======
>>>>>>> e99e1aafb4817a2970e8434163e487873ff4373b
            }
            //            if(num_malloc_calls==1000){
            //                printf("lit i'm about to increment\n");
            //                break;
            //            }
            
        }
        printf("exited the iterator loop!\n");
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
<<<<<<< HEAD
        run++;
=======
    run++;
>>>>>>> e99e1aafb4817a2970e8434163e487873ff4373b
    }
    return time/100;
    
}

int testD(){
    int run=0,time=0;
<<<<<<< HEAD
    while(run<100){
        struct timeval start, end;
        gettimeofday(&start, NULL);
        int num_malloc_calls=0,place=0;
=======
    // while(run<100){
        struct timeval start, end;
        gettimeofday(&start, NULL);
        int iterator=0,place=0;
>>>>>>> e99e1aafb4817a2970e8434163e487873ff4373b
        char *pointerArray[1000];
        while(num_malloc_calls<1000){
            printf("iterator : %d\n", num_malloc_calls);
            int random = rand() % 2;
            // printf("random: %d\n",random);
            // printf("iterator: %d\n",iterator);
            int randomFree = rand() % 64 +1;
            //printf("randomFree %d \n",randomFree);
            if(random==0){
                pointerArray[place]=(char*)malloc(randomFree);
<<<<<<< HEAD
                
                if(pointerArray[place]==NULL){
                    free(pointerArray[place-1]);
                    pointerArray[place-1] = NULL;
                    continue;
                }
                place++;
                num_malloc_calls++;
            }
            
            else if(random==1){
                
=======

                if(pointerArray[place]==NULL){
                    random=1;
                    continue;
                }
                place++;
                iterator++;
            }
            
            if(random==1){

>>>>>>> e99e1aafb4817a2970e8434163e487873ff4373b
                if(place<=0){
                    place=0;
                    continue;
                }
                if(pointerArray[place]==NULL){
                    continue;
                }
                place--;
                free(pointerArray[place]);
<<<<<<< HEAD
                pointerArray[place] = NULL;
=======
>>>>>>> e99e1aafb4817a2970e8434163e487873ff4373b
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
<<<<<<< HEAD
        run++;
    }
=======
    run++;
    // }
>>>>>>> e99e1aafb4817a2970e8434163e487873ff4373b
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
    while(run<100){
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
        place = 1;
        while(place<placerep){
            if(pointerArray[place] == NULL){
                continue;
            }
            free(pointerArray[place]);
            pointerArray[place]=NULL;
            place+=3;
        }
        
        gettimeofday(&end, NULL);
        time+=(end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec);
        run++;
    }
    return time/100;
    //
}

void testF(){
    
}

int main(int argc, char** argv){
<<<<<<< HEAD
    
    printf("Test A's average time: %d microseconds\n", testA());
    printf("Test B's average time: %d microseconds\n", testB());
    printf("Test C's average time: %d microseconds\n", testC());
    printf("Test D's average time: %d microseconds\n", testD());
    printf("Test E's average time was %d microseconds\n", testE());
=======

    char * p=(char*)malloc(1);
    printf("address of p: %p\n",p);
p=(char*)malloc(1);
printf("address of p: %p\n",p);
   //  printf("Test A's time: %d microseconds\n", testA());
   //  printf("Test B's time: %d microseconds\n", testB());
   // printf("Test C's time: %d microseconds\n", testC());
   //  printf("Test D's time: %d microseconds\n", testD());
    // printf("Test E's average time was %d microseconds\n", testE());
>>>>>>> e99e1aafb4817a2970e8434163e487873ff4373b
    // printf("Test F's average time was %d microseconds\n", testF());
    return 0;
}
