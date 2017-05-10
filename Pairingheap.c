#include "Pringheap.h"

Pheap insertPheap(Pheap heap, int key)
{
	Pheap node;

	if (!(node = (Pheap)malloc(sizeof(ParingHeapNode))))msg_error("memory not aloocated\n");
	node->key = key;
	node->child = node->next = node->prev = NULL;
	if (heap == NULL)return node;
	else
		return mergeSubHeap(heap, node);
}
Pheap DeleteMinPheap(int *min, Pheap heap)
{
	Pheap new_root;

	if (heap == NULL) return NULL;
	else
	{
		*min = heap->key;
		if (heap->child != NULL)new_root = combine_List(heap->child);
		free(heap);
	}
	return new_root;
}
Pheap combine_List(Pheap heap)
{
	Pheap *OrderArray;
	Pheap temp;
	int i, count, len;
	if (heap->next == NULL)return heap;
	temp = heap;
	for (len = 0; temp != NULL; len++)temp = temp->next;
	if (!(OrderArray = (Pheap*)malloc(len*sizeof(Pheap))))
		msg_error("memory not aloocated\n");

	for (i = 0; i<len; i++)
	{
		OrderArray[i] = heap;
		heap->prev->next = NULL;
		heap = heap->next;
		OrderArray[i]->next = NULL;
		OrderArray[i]->prev = NULL;
	}
	for (i = len - 1; i > 0; i--)
		OrderArray[i - 1] = mergeSubHeap(OrderArray[i], OrderArray[i - 1]);

	return *OrderArray;
}
Pheap mergeSubHeap(Pheap heap, Pheap newHeap)
{
	if (newHeap == NULL) return heap;
	else if (heap->key <= newHeap->key)
	{
		newHeap->prev = heap;
		heap->next = newHeap->next;
		if (heap->next != NULL)heap->next->prev = heap;
		newHeap->next = heap->child;
		if (newHeap->next != NULL)newHeap->next->prev = newHeap;
		heap->child = newHeap;
		return heap;
	}
	else
	{
		newHeap->prev = heap->prev;
		heap->prev = newHeap;
		heap->next = newHeap->child;
		if (heap->next != NULL) heap->next->prev = heap;
		newHeap->child = heap;
		return newHeap;
	}
}
void printNodePheap(Pheap heap)
{
	printf("(%d,", heap->key);
	printf("child: ");
	if (!(heap->child))printf("non,");
	else printf("%d,", heap->child->key);
	printf("prev: ");
	if (!(heap->prev))printf("non,");
	else printf("%d,", heap->prev->key);
	printf("next: ");
	if (!(heap->next))printf("non)\n");
	else printf("%d)\n", heap->next->key);
}
void dispalyPheap(Pheap heap)
{
	if (!heap)return;
	printNodePheap(heap);
	dispalyPheap(heap->next);
	dispalyPheap(heap->child);
}

