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


metaData createNode(size_t, char);
void * mymalloc (size_t);
void myfree(address);


// creating Nodes for proper usage
metaData createNode(size_t pointerSize, char usage){
    metaData Node;
    Node.size=pointerSize;
    Node.use=usage;

    return Node;
}
void myfree(void*ptr){
    metaData*search = &myblock[0];
    metaData*prev = NULL;
    while(((char*)search + 1) != &ptr){
        prev = search;
        search = (metaData*)(((char*)search + 1) +size);
        
    }
    if(search!=NULL && search->use == 'y'){
        search->use = 'n';
    }else if(search==NULL || search->use=='n' ){
        printf("invalid free \n");
        return;
    }if(prev!=NULL){
        if(prev->use == 'n'){
            prev->size = prev->size + sizeof(metaData) + search->size;
        }
    }
}
void * mymalloc(size_t requested_size){
    if(myblock[0]=='\0'){
        metaData firstNode=createNode(requested_size,'y');
        memcpy(myblock[0], &firstNode, sizeof(metaData));
        return void * ptr=&myblock[sizeof(Node)];
    }

    metaData*search = &myblock[0];
    while(search!= NULL){
        int size_of_current_node = search->size;
        if(search->size >requested_size && search->use == 'n' ){
            /*
             1. copy the current node into another node
            
             2. change the usage and size to accommodate to requested size
            
             
             */
            metaData* post_node = search;
            search->size = requested_size;
            search->use = 'y';
             /*
            1. check to see if remaining space is enough to hold metadata AND whatever information may proceed in the future
                a. how to do so: 
              
                if(size_of_current_node - (sizeof(metadata) + precede_node->size) > sizeof(metaData) + 1)
              
            2. if not at least metadata +1 space, THEN: 
              
              -> return address of (char*)precede_node +1
              -> no created node
              
            3. if there is enough space, create a post_node with appropriate spacing
              -> return address of (char*)precede_node +1
              
              */
            size_t remaining_size =size_of_current_node - ((sizeof(metadata) + precede_node->size);
            
            if(remaining_size >= (sizeof(metaData) + 1)){
                metaData*post_node= createNode(remaining_size - sizeof(metaData), 'y');
                return &((void*) ((char*)precede_node + 1));
            }else{
                return &((void*) ((char*)precede_node + 1));
            }
        }else{
            search = (metaData*)(((char*)search + 1) +size);
        }
    }
    
    return void* NULL;
}
