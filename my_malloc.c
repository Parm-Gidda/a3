#include "my_malloc.h"
#include "list.h"

//void *my_malloc(size_t size);
//void my_free(void *ptr);
//void *mem_init();

char* mainBlock;
List* allBlocks;
int blockSize;
struct Node_s* blockAderesses[100];


//void findEmty 

void testPrint(){

    for(int i = 0; i < 100; i++){

        if(blockAderesses[i]->inuse == true){
        printf("%d: in-use,   %d, f:%p, b: %p, - %p\n", i, blockAderesses[i]->NodesInBlock, blockAderesses[i]->frontOfBlock, blockAderesses[i]->backOfBlock, blockAderesses[i]);
        }
        else{
        printf("%d: not-used, %d, %p, %p, - %p\n", i, blockAderesses[i]->NodesInBlock, blockAderesses[i]->frontOfBlock, blockAderesses[i]->backOfBlock,blockAderesses[i]);
        }
    }


    printf("\n\n\n\n\n");
}

void *my_malloc(size_t size){

    int amountBlockNeeded = 1;
    struct Node_s* blockStart;

    if(size > blockSize){
        amountBlockNeeded = blocksNeeded(size);
    }

    //printf("blocks needed: %d\n", amountBlockNeeded);

    blockStart = findBlock(amountBlockNeeded);

    if(blockStart == NULL){
        return NULL;
    }
    else{

        //for(int i = 0; i < 10; i++){
          //  printf("%d: %p\n", i, blockAderesses[i]->item);
        //}

    
        splitBlock(amountBlockNeeded, blockStart);
 
        return blockStart->item;
      //  printf("testing: %p\n", blockStart->frontOfBlock);
    }


    return NULL;



}

void* splitBlock(int blocksNeeded, struct Node_s* startOfBlock){

        struct Node_s* endOfBlock;
        int originalAmountOfNodes = startOfBlock->NodesInBlock;

        struct Node_s* startOfSecondHalf;
        struct Node_s* endOfSecondHalf;

        endOfBlock = blockAderesses[startOfBlock->nodeNumber + blocksNeeded - 1];
        
        endOfSecondHalf = blockAderesses[startOfBlock->nodeNumber + startOfBlock->NodesInBlock - 1];

        if(blocksNeeded == startOfBlock->NodesInBlock){

            startOfBlock->inuse = true;
            startOfBlock->NodesInBlock = blocksNeeded;
            startOfBlock->frontOfBlock = startOfBlock;
            startOfBlock->backOfBlock = endOfBlock;

            endOfBlock->inuse = true;
            endOfBlock->NodesInBlock = blocksNeeded;
            endOfBlock->frontOfBlock = startOfBlock;
            endOfBlock->backOfBlock = endOfBlock;

            return startOfBlock->item;
        }
        else{

  
            startOfBlock->inuse = true;
            startOfBlock->NodesInBlock = blocksNeeded;
            startOfBlock->frontOfBlock = startOfBlock;

    
            startOfBlock->backOfBlock = endOfBlock;

            endOfBlock->inuse = true;
            endOfBlock->NodesInBlock = blocksNeeded;
            endOfBlock->frontOfBlock = startOfBlock;
            endOfBlock->backOfBlock = endOfBlock;

            startOfSecondHalf = blockAderesses[startOfBlock->nodeNumber + blocksNeeded];

            startOfSecondHalf->inuse = false;
            startOfSecondHalf->NodesInBlock = originalAmountOfNodes - blocksNeeded;
            startOfSecondHalf->frontOfBlock = startOfSecondHalf;
            startOfSecondHalf->backOfBlock = endOfSecondHalf;

            endOfSecondHalf->inuse = false;

            endOfSecondHalf->NodesInBlock = startOfSecondHalf->NodesInBlock;

            endOfSecondHalf->frontOfBlock = startOfSecondHalf;
            endOfSecondHalf->backOfBlock = endOfSecondHalf;
           
            return startOfBlock->item;
        }

        return NULL;
}

struct Node_s* findBlock(int blocksNeeded){

    List_first(allBlocks);
    int amountOfNodesInBlock = 0;
    struct Node_s* potentialBlockStart = allBlocks->currentItem;

    printf("------------------\n\n");

    while(true){
        
        printf("loop\n");
        //current block is being used
        if(potentialBlockStart->inuse == true){
            printf("brodie\n");
            amountOfNodesInBlock = potentialBlockStart->NodesInBlock;

            if(amountOfNodesInBlock + potentialBlockStart->nodeNumber <= 99){
                printf("hih\n");
                potentialBlockStart = blockAderesses[amountOfNodesInBlock + potentialBlockStart->nodeNumber]; 
                continue;
            }
            else{

                return NULL;
               
            }

        }
        //current block is not being used
        else if( potentialBlockStart->inuse == false){

            amountOfNodesInBlock = potentialBlockStart->NodesInBlock;
            
            //we can split block

            if(amountOfNodesInBlock >= blocksNeeded){

          
                return potentialBlockStart;
            }
            else{
        
                if(amountOfNodesInBlock + potentialBlockStart->nodeNumber <= 99){
                potentialBlockStart = blockAderesses[amountOfNodesInBlock + potentialBlockStart->nodeNumber]; 
                continue;

                }
                else{
                    return NULL;
                }
            }


            
        }
     
    }

    return NULL;
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


void my_free(void *ptr){

    struct Node_s* startOfBlock = findStartingBlock(ptr);
    bool hasBackNeighbor = false;
    bool hasFrontNeighbor = false;
  
    if(startOfBlock->previousItem != NULL && startOfBlock ->nextItem != NULL){
        hasFrontNeighbor = true;
        hasBackNeighbor = true;
    }
    else if(startOfBlock->previousItem == NULL && startOfBlock ->nextItem != NULL){
        hasFrontNeighbor = true;
        hasBackNeighbor = false;
    }   
    else if(startOfBlock->previousItem != NULL && startOfBlock ->nextItem == NULL){
        hasFrontNeighbor = false;
        hasBackNeighbor = true;
    }

    combineAdjBlocks(startOfBlock, hasFrontNeighbor, hasBackNeighbor);


}

void combineAdjBlocks(struct Node_s* startOfBlock, bool hasFrontNeighbor, bool hasBackNeighbor){

    if(hasFrontNeighbor == true && hasBackNeighbor == true){
      //  printf("AAAAAAAA\n");

        if(startOfBlock->previousItem->inuse == false && blockAderesses[startOfBlock->nodeNumber + startOfBlock->NodesInBlock]->inuse == false){

        //    printf("aaaaaa\n");
            
            startOfBlock->previousItem->NodesInBlock = startOfBlock->NodesInBlock + startOfBlock->nextItem->NodesInBlock + startOfBlock->previousItem->NodesInBlock;
            startOfBlock->nextItem->NodesInBlock = startOfBlock->previousItem->NodesInBlock;

        } 
        else if(startOfBlock->previousItem->inuse == true && blockAderesses[startOfBlock->nodeNumber + startOfBlock->NodesInBlock]->inuse == false){
          //   printf("bbbbbbbbbbbb\n");
           
            startOfBlock->nextItem->NodesInBlock = startOfBlock->NodesInBlock + startOfBlock->nextItem->NodesInBlock;

        }
         else if(startOfBlock->previousItem->inuse == false && blockAderesses[startOfBlock->nodeNumber + startOfBlock->NodesInBlock]->inuse == true){
            //  printf("cccccccccccccccc\n");
           
            startOfBlock->previousItem->NodesInBlock = startOfBlock->NodesInBlock + startOfBlock->previousItem->NodesInBlock;

        }
    }
    else if(hasFrontNeighbor == false && hasBackNeighbor == true){

              //  printf("BBBBBBBBBBBB\n");
        if(startOfBlock->previousItem->inuse == false){

            startOfBlock->previousItem->NodesInBlock = startOfBlock->NodesInBlock + startOfBlock->previousItem->NodesInBlock;
        }
    }
    else if(hasFrontNeighbor == true && hasBackNeighbor == false){

                //printf("CCCCCCCCCCCCC\n");

        if(blockAderesses[startOfBlock->nodeNumber + startOfBlock->NodesInBlock]->inuse == false){

            startOfBlock->nextItem->NodesInBlock = startOfBlock->NodesInBlock + startOfBlock->nextItem->NodesInBlock;
        }
    }

    struct Node_s* endOfStartBlock = startOfBlock->backOfBlock;

        startOfBlock->inuse = false;
        endOfStartBlock->inuse = false;

}

struct Node_s* findStartingBlock(void *freeAdderess){

   // printf("free addy: %p\n", freeAdderess);
   // printf("og block addy: %p\n", mainBlock);

    int adderessDifference = (char*)freeAdderess - mainBlock;

    if(adderessDifference % 200 != 0){
        return NULL;
    }

    int adderessIndex = adderessDifference / 200;

    if(adderessIndex < 0 || adderessIndex > 99){
        return NULL;
    }

   // printf("diff: %d", adderessDifference);
    return blockAderesses[adderessIndex];

}

void mem_init(){

    allBlocks = List_create();

    struct Node_s* originalFrontOfBlock;
    struct Node_s* originalBackOfBlock;

    mainBlock = (char*)malloc(MAIN_BLOCK_SIZE);

    blockSize = MAIN_BLOCK_SIZE/100;
    printf("block size: %d\n", blockSize);

    for(int i = 0; i < 100; i++){

        char* block = (char*)malloc(sizeof(char));

        block = mainBlock + i*blockSize;


        List_append(allBlocks, block);

         blockAderesses[i] = allBlocks->currentItem;

        if(i == 0){
            originalFrontOfBlock = allBlocks->currentItem;
        }
        else if(i == 99){
            originalBackOfBlock = allBlocks->currentItem;
        }

        allBlocks->currentItem->inuse = false;
        allBlocks->currentItem->NodesInBlock = 100;
        allBlocks->currentItem->frontOfBlock = originalFrontOfBlock;
        allBlocks->currentItem->backOfBlock =  originalBackOfBlock;

    }

    List_first(allBlocks);

   // printTest(allBlocks);



    

}

//93956788164272