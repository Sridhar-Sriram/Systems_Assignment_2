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

void myfree(void*ptr){

	int iterator=0;
	while(myblock[iterator]=='\0'){
		iterator++;
	}
    metaData*current_pointer = (metaData*)&myblock[iterator];
    metaData*prev = NULL;
    
    while(current_pointer+1!= (metaData*)&ptr){
    	iterator+=(int)sizeof(metaData)+current_pointer->size;
        prev = current_pointer;
        current_pointer = (metaData*)&myblock[iterator];
        
    }
    iterator+=(int)sizeof(metaData)+current_pointer->size;
    metaData*post=(metaData*)&myblock[iterator];

    if(current_pointer!=NULL && current_pointer->use == 'y'){
        current_pointer->use = 'n';
    }else if(current_pointer==NULL || current_pointer->use=='n' ){
        printf("invalid free \n");
        return;
    }if(prev!=NULL){
        if(prev->use == 'n'){
            prev->size = prev->size + sizeof(metaData) + current_pointer->size;
        }
        if(post!=NULL&&post->use=='n'){
        	prev->size=post->size+sizeof(metaData);
        }
    }
}

void * mymalloc(size_t requested_size){

	metaData * search = (metaData*)&myblock[0];
	//printf("meta: %zu\n",sizeof(metaData));

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
            printf("iterator: %i\n",iterator);
                return &myblock[iterator];
        }

        iterator+=(int)sizeof(metaData)+search->size;

        search=(metaData*)&myblock[iterator];

    }

    printf("No space available.\n");
    
    return NULL;
    
}

int main(int argc, char **argv){
	int i;
	printf("address of array: %p\n",myblock);
	for(i=1;i<=10;i++){
		void * pointer=mymalloc(i);
		printf("address of pointer: %p\n",pointer);
		free(pointer);
	}
	
}
