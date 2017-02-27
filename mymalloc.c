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

// creating Nodes for proper usage
metaData createNode(size_t pointerSize, char usage){
    metaData Node;
    Node.size=pointerSize;
    Node.use=usage;
    return Node;
}

void myfree(void*pointer_to_be_freed, char * file, int line){
    
    int iterator = 0;
    metaData * search = (metaData*)&myblock[0];
    metaData*prev = NULL;
    metaData*post = NULL;
    
    while(iterator<5000){
        
        if(search + 1== (metaData*)pointer_to_be_freed){
            break;
        }
        prev= search;
        iterator+=(int)sizeof(metaData) + search->size;
        search = (metaData*)&myblock[iterator];
        
    }
    iterator+=(int)sizeof(metaData)+search->size;
    post = (metaData*)&myblock[iterator];
    
    /* FOR FOLLOWING CASES, y INDICATES USER DATA, n INDICATES UNUSED SPACE
     */
    
    if(search!=NULL){
        if(search->use=='n' ||search->use=='\0'){
            fprintf(stderr, "ERROR: invalid free @ %s line %d \n", file, line);
            return;
        }else if(search->use =='y'){
            // printf("address of search: %p \n", search);
            search->use = 'n';
            //case 2: unused space preceding freed area, user data proceeding area: N current_location Y
            if(prev == NULL){
                if(post !=NULL){
                    if(post->use == 'n'){
                        search->size += (int)sizeof(metaData)+post->size;
                        return;
                    }
                }else{
                    return;
                }
            }else{
                if(prev->use == 'n'&&post->use == 'y'){
                    prev->size+= (int)sizeof(metaData)+search->size;
                    return;
                }
                //case 3: user data preceding freed area, unused space following: Y current_location N
                else if(prev->use == 'y'&&post->use == 'n'){
                    // search->use = 'n';
                    search->size += (int)sizeof(metaData)+post->size;
                    return;
                }
                // case 4: unused space preceding and proceeding freed area: N current_location N
                else if(prev->use == 'n'&&post->use == 'n'){
                    prev->size = (int)sizeof(metaData)*2 + search->size + post->size;
                    return;
                }
                
            }
            
        }
    }else{
        fprintf(stderr, "ERROR: Pointer not found @ %s line %d \n", file, line);
        return;
    }
    return;
}

void * mymalloc(size_t requested_size, char * file, int line){

    //printf("size of meta data: %lu\n",sizeof(metaData));
    //checking to see if invalid size is asked for
    if((int)requested_size >(5000-(int)sizeof(metaData))){
        fprintf(stderr,"ERROR: No space available @ %s line %d \n", file, line);
        return NULL;
    }
    metaData * search = (metaData*)&myblock[0];
    
    /*
     - check to see if the array has been accessed yet
     - only applicable during first run of malloc
     - if there is enough space to create another metadata node to store other memory, then a "post_node" is created
     */
    if(myblock[0]=='\0'){
        
        metaData Node=createNode(requested_size,'y');
        memcpy(&myblock[0],&Node,sizeof(metaData));
        if((5000-requested_size-(int)sizeof(metaData))>=(int)(sizeof(metaData)+1)){
            metaData post_node= createNode(5000-requested_size - ((int)sizeof(metaData)*2), 'n');
            memcpy(&myblock[sizeof(metaData)+requested_size],&post_node,sizeof(metaData));
        }
        return &myblock[0] + sizeof(metaData);
    }
    int iterator=0;
    while(iterator<=5000){
        
        if(search==NULL){
            search=(metaData*)&myblock[iterator];
            iterator+=1;
            continue;
        }
        /*
         1. We check to see if, at current node, there is enough space for the amount of memory being requested AND that this space in memory is NOT in use
         
         2. Then, we check to see if there is enough space in memory AFTER the allocated memory for any other potential data to be written -> sizeof(metaData)+1
         - if enough space exists, then we create a node to follow the contiguous memory that we have set aside
         
         3. Then, by incrementing the iterator by the sizeof(metaData) we reach the index in the array that indicates that memory can be written into.  In other words, this is the address that we return
         -
         */
        if(search->size >= requested_size && search->use == 'n' ){
            
            // create a "used" metadata node with corresponding size
            int size_of_current_node = search->size;
            search->use='y';
            search->size=requested_size;
            
            int remaining_size =size_of_current_node - requested_size;
            if(remaining_size >= (sizeof(metaData) + 1)){
                metaData post_node= createNode(remaining_size, 'n');
                memcpy(&myblock[iterator+(int)sizeof(metaData)+search->size],&post_node,sizeof(metaData));
            }
            iterator+=(int)sizeof(metaData);
            return &myblock[iterator];
        }
        iterator+=((int)sizeof(metaData)+search->size);
        search=(metaData*)&myblock[iterator];
    }
    
    fprintf(stderr,"ERROR: No space available @ %s line %d \n", file, line);
    return NULL;
}

