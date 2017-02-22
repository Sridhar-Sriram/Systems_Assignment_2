#include<stdio.h>
#include<stdlib.h>

void testA();
void testB();
void testC();
void testD();
void testE();
void testF();


int main(int argc, char** argv){
	printf("Testing testB \n");
	testB();
	return 0;
}

void testA(){

}

void testB(){
	int i =1;
	for(i =1 ; i <=1000; i++){
		char*testPointer = (char*)malloc(sizeof(char));
		free(testPointer);
	}
}

void testC(){

}

void testD(){

}

void testE(){

}

void testF(){

}