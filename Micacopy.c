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
    
    while(iterator<=5000){
    	if(current_pointer+1!= (metaData*)&ptr){
    		
    		break;
    	}
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
    }if(prev==NULL&&post!=NULL){

    	if(post->use=='n'){
    		printf("hello\n");
    		current_pointer->size=current_pointer->size+sizeof(metaData)+post->size;
    		return;
   		 }
    }
    if(prev!=NULL&&prev->use == 'n'){
        prev->size = prev->size + sizeof(metaData) + current_pointer->size;
    }
    if(post!=NULL&&post->use=='n'){
      	prev->size=post->size+sizeof(metaData);
    }
}

void * mymalloc(size_t requested_size){
    //checking to see if invalid size is asked for
    if((int)requested_size >=(5000-(int)sizeof(metaData))){
        printf("no space available. \n");
        return NULL;
    }
//    metaData * check_search = (metaData*)&myblock[0];
//    int check_iterator = 0;
//    while(check_iterator <5000){
//        if(&myblock[iterator]==)
//        iterator =
//    }
	metaData * search = (metaData*)&myblock[0];
	//printf("meta: %zu\n",sizeof(metaData));

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
        	//printf("post use: %c\n",post_node.use);
            memcpy(&myblock[sizeof(metaData)+requested_size],&post_node,sizeof(metaData));
            //should I make separate function
        }
        ///*
        // ALL THAT FOLLOWS ARE CHECK STATEMENTS FOR DESCRIPTIONS OF WHERE IN THE ARRAY WE ARE
         
        printf("address of metadata node: %p\n", &myblock[0]);
        printf("usage, size @ node: %c, %d \n ", search->use, (int)search->size);
        printf("address of allocated space to be written into: %p\n",(&myblock[0] + (int)sizeof(metaData)));
        printf("address of metadata node AFTER space: %p \n",(&myblock[0] + (int)sizeof(metaData)+search->size));
        int afterlocation =0 + (int)sizeof(metaData)+search->size;
        metaData * after =(metaData*)&myblock[afterlocation];
        printf("usage, size @ node: %c, %d\n", after->use, (int)after->size);
       // */
        
        return &myblock[0] + sizeof(metaData);
}
    /* 
    - ACTUAL SEARCH
    -
    */

    int iterator=0;
    while(iterator<=5000){
    	
        //WHAT DOES THIS DO
    	
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
        if(search->size > requested_size && search->use == 'n' ){
 
            // create a "used" metadata node with corresponding size
            int size_of_current_node = search->size;
            search->use='y';
            search->size=requested_size;
    
            int remaining_size =size_of_current_node - requested_size;
            if(iterator==0){
            	iterator=(int)sizeof(metaData);
            }
            
            if(remaining_size >= (sizeof(metaData) + 1)){
                metaData post_node= createNode(remaining_size - sizeof(metaData), 'n');
                memcpy(&myblock[iterator+(int)sizeof(metaData)+search->size],&post_node,sizeof(metaData));
                //printf("address of metadata node AFTER space: %p \n",&myblock[iterator+(int)sizeof(metaData)+search->size]);
            }
            ///*
             //ALL THAT FOLLOWS ARE CHECK STATEMENTS FOR DESCRIPTIONS OF WHERE IN THE ARRAY WE ARE
            printf("iterator: %i\n",iterator);
            printf("address of metadata node: %p\n", &myblock[iterator]);
            printf("usage, size @ node: %c, %d\n", search->use, (int)search->size);
            printf("address of allocated space to be written into: %p\n",(&myblock[iterator+(int)sizeof(metaData)]));
             printf("address of metadata node AFTER space: %p \n",(&myblock[iterator] + (int)sizeof(metaData)+search->size));
            int afterlocation =iterator + (int)sizeof(metaData)+search->size;
            metaData * after =(metaData*)&myblock[afterlocation];
            printf("usage, size @ node: %c, %d\n", after->use, (int)after->size);
            //*/
            iterator = iterator + (int)sizeof(metaData);
            return &myblock[iterator];
        }

        iterator+=((int)sizeof(metaData)+search->size);

        search=(metaData*)&myblock[iterator];

    }

    printf("No space available.\n");
    
    return NULL;
    
}

int main(int argc, char **argv){
    
	printf("address of array: %p\n",myblock);
    printf("\n");
	void * pointer=mymalloc(985);
	printf("address of pointer: %p\n",pointer);
    printf("\n");
	void * pointer2=mymalloc(985);
	printf("address of pointer2: %p\n",pointer2);
    printf("\n");
    void*pointer3=mymalloc(985);
    printf("address of pointer3: %p \n",pointer3);
    printf("\n");
    void*pointer4=mymalloc(985);
    printf("address of pointer4: %p \n",pointer4);
    printf("\n");
    void*pointer5=mymalloc(963);
    printf("address of pointer5: %p \n",pointer5);
    printf("\n");
    return 0;
}
