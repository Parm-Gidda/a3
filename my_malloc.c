#include "my_malloc.h"
#include "list.h"

//void *my_malloc(size_t size);
//void my_free(void *ptr);
//void *mem_init();

char* mainBlock;
List* allBlocks;
int blockSize;

//void findEmty 

void *my_malloc(size_t size){

    int amountBlockNeeded = 1;

    if(size > blockSize){
        amountBlockNeeded = blocksNeeded(size);
    }

    printf("blocks needed: %d\n", amountBlockNeeded);


    return mainBlock;

}

int blocksNeeded(size_t size){

    int amountBlockNeeded = 0;

   
    if(size % blockSize == 0){

        amountBlockNeeded = size/blockSize;
        return amountBlockNeeded;
    }
    else{

        amountBlockNeeded = (size/blockSize) + 1;
    
        return amountBlockNeeded;
    }

}


void my_free(void *ptr){}

void mem_init(){

    allBlocks = List_create();

    

    mainBlock = (char*)malloc(MAIN_BLOCK_SIZE);

    blockSize = MAIN_BLOCK_SIZE/100;
    printf("block size: %d\n", blockSize);

    for(int i = 0; i < 100; i++){

        char* block = (char*)malloc(sizeof(char));

        block = mainBlock + i*blockSize;

        List_append(allBlocks, block);

    }

    List_first(allBlocks);

   // printTest(allBlocks);



    

}

//93956788164272