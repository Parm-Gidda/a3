#ifndef _MY_MALLOC_H_
#define _MY_MALLOC_H_

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//allocate a main block of size 20000
#define MAIN_BLOCK_SIZE 20000

void *my_malloc(size_t size);
void my_free(void *ptr);
void mem_init();
int blocksNeeded(size_t size);
struct Node_s* findBlock(int blocksNeeded);

void* splitBlock(int blocksNeeded, struct Node_s* startOfBlock);

void testPrint();
struct Node_s* findStartingBlock(void *freeAdderess);
void combineAdjBlocks(struct Node_s* startOfBlock, bool hasFrontNeighbor, bool hasBackNeighbor);

#endif