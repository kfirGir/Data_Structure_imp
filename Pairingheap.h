#ifndef PringHeap
#define PringHeap
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
/* ADT of a generic Stack  */
typedef struct ParingHeapNode
{
	int  key;
	struct  ParingHeapNode*    child;
	struct  ParingHeapNode*    next;
	struct  ParingHeapNode*    prev;

}ParingHeapNode, *Pheap; 

Pheap mergeSubHeap(Pheap heap, Pheap NewHeap);
Pheap combine_List(Pheap heap);
Pheap insertPheap(Pheap heap, int key);
Pheap DeleteMinPheap(int *min, Pheap heap);
void dispalyPheap(Pheap root);
void printNodePheap(Pheap heap);
void msg_error(char * str);

#endif