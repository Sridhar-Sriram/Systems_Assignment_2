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


// metaData createNode(size_t, char);
// void * mymalloc (size_t);

// creating Nodes for proper usage
metaData createNode(size_t pointerSize, char usage){
    metaData Node;
    Node.size=pointerSize;
    Node.use=usage;
  
    return Node;
}

void * mymalloc(size_t requested_size){

	metaData * search = (metaData*)&myblock[0];

    if(myblock[0]=='\0'){
        metaData Node=createNode(requested_size,'n');
        memcpy(&myblock[0],&Node,sizeof(metaData));
        return &myblock[0] + sizeof(metaData);
        //return &((void*)((char*)Node+1));
    }
    int iterator=0;
    while(iterator<=5000){

    	if(search==NULL){
        	search=(metaData*)(((char*)search + 1)+sizeof(char));
        	iterator+=1;
        	continue;
        }
        
        if(search->size > requested_size && search->use == 'n' ){
            // create a "used" metadata node with corresponding size
            int size_of_current_node = search->size;
            search->use='y';
            search->size=requested_size;
    
            size_t remaining_size =size_of_current_node - (sizeof(metaData) + requested_size);
            
            if(remaining_size >= (sizeof(metaData) + 1)){
                metaData post_node= createNode(remaining_size - sizeof(metaData), 'n');
                memcpy(&myblock[iterator],&post_node,sizeof(metaData));
            }
                return &myblock[iterator] + sizeof(metaData);
                //return &((void*)((char*)search + 1)+search->size);
        }

        iterator+=sizeof(metaData)+search->size;
        search = (metaData*)(((char*)search + 1) +search->size);

    }

    printf("No space available.");
    
    return NULL;
    
}

int main(int argc, char **argv){

	void * pointer=mymalloc(10);
	printf("%p\n",pointer);
}
