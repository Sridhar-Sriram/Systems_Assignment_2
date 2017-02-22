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

        metaData Node=createNode(requested_size,'y');
        memcpy(&myblock[0],&Node,sizeof(metaData));
        if(5000-requested_size-sizeof(metaData)>=(sizeof(metaData)+1)){
    
        	metaData post_node= createNode(5000-requested_size - sizeof(metaData)*2, 'n');

            memcpy(&myblock[sizeof(metaData)*2+requested_size],&post_node,sizeof(metaData));
            //should I make separate function
        }
        //printf("search size: %c\n",search->use);
        return &myblock[0] + sizeof(metaData);
        //return &((void*)((char*)Node+1));
    }

    int iterator=0;
    while(iterator<=5000){
    	
    	if(search==NULL){
        	search=(metaData*)&myblock[iterator];
        	iterator+=1;
        	continue;
        }
       //printf("search size: %zu\n",search->size);
        if(search->size > requested_size && search->use == 'n' ){
 
            // create a "used" metadata node with corresponding size
            int size_of_current_node = search->size;
            search->use='y';
            search->size=requested_size;
    
            size_t remaining_size =size_of_current_node - (sizeof(metaData) + requested_size);
            
            if(remaining_size >= (sizeof(metaData) + 1)){
                metaData post_node= createNode(remaining_size - sizeof(metaData), 'n');
                memcpy(&myblock[iterator+(int)sizeof(metaData)+search->size],&post_node,sizeof(metaData));
            }
                return &myblock[iterator] + sizeof(metaData);
                //return &((void*)((char*)search + 1)+search->size);
        }

        iterator+=(int)sizeof(metaData)+search->size;
        //printf("iterator: %i\n",iterator);
        // printf("address of search before pointer: %p\n",search);

        search=(metaData*)&myblock[iterator];
        // printf("address of search after pointer: %p\n",search);
        //search = (metaData*)(((char*)search + 1) +search->size);

    }

    printf("No space available.\n");
    
    return NULL;
    
}

int main(int argc, char **argv){
	int i;
	printf("address of array: %p\n",myblock);
	for(i=0;i<=3;i++){
		void * pointer=mymalloc(10);
		printf("address of pointer: %p\n",pointer);
	}

	
}
