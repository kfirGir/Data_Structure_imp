#include "TernaryHeap.h"

void msg_error(char * str)
{
	puts(str);
	exit(1);
}
int Parent(int i)
{
	return (i - 1) / 3;
}
int Left(int i)
{
	return (i * 3 + 1);
}
int Center(int i)
{
	return i * 3 + 2;
}
int Right(int i)
{
	return i * 3 + 3;
}
trenaryHeap createTRheap(int maxSize)
{
	TRheap TreHeap;
	TreHeap = (TRheap)malloc(sizeof(trenaryHeap));
	TreHeap->heap = (int *)malloc(sizeof(int)*maxSize);
	TreHeap->maxSize = maxSize;
	TreHeap->heapSize = 0;
	return *TreHeap;
}
void heapify3Down(TRheap Treheap, int i)
{
	int left, right, center, n, smallest, temp;
	if (Treheap == NULL || Treheap->heap == NULL || Treheap->heapSize == 0)
	{
		printf("you have a problem with your heap\n");
		return;
	}
	if (i > Treheap->heapSize)return;
	left = Left(i);
	right = Right(i);
	center = Center(i);
	n = Treheap->heapSize;
	smallest = i;
	if (left<n && *(Treheap->heap + left)<*(Treheap->heap + i)) smallest = left;
	if (center<n && *(Treheap->heap + center)<*(Treheap->heap + smallest)) smallest = center;
	if (right<n && *(Treheap->heap + right)<*(Treheap->heap + smallest)) smallest = right;
	if (smallest != i)
	{
		temp = *((Treheap->heap) + i);
		*(Treheap->heap + i) = *(Treheap->heap + smallest);
		*(Treheap->heap + smallest) = temp;
		heapify3Down(Treheap, smallest);
	}
}
void heapify3Up(TRheap Treheap, int i)
{
	int parent, n, temp;
	if (Treheap == NULL || Treheap->heap == NULL || Treheap->heapSize < 0)
	{
		printf("you have a problem with your heap\n");
		return;
	}
	if (i > Treheap->heapSize)
	{
		printf("incorrect place at the heap\n");
		return;
	}
	if (i < 1)return;
	parent = Parent(i);
	n = Treheap->heapSize;
	if (parent >= 0 && *((Treheap->heap) + parent) > *((Treheap->heap) + i))
	{
		temp = *((Treheap->heap) + i);
		*((Treheap->heap) + i) = *((Treheap->heap) + parent);
		*((Treheap->heap) + parent) = temp;
	}
	heapify3Up(Treheap, parent);
}
void BulidTrHeap(int* A, int n, TRheap Treheap)
{
	int i;
	if (Treheap == NULL || Treheap->heap == NULL)
	{
		printf("you have a problem with your heap\n");
		return;
	}
	if (n > Treheap->maxSize || A == NULL)
	{
		printf("you have a problem with your array\n");
		return;
	}
	for (i = 0; i < n; i++)
		insertTrheap(Treheap, A[i]);
}
void insertTrheap(TRheap Treheap, int key)
{
	int i;
	if (Treheap == NULL || Treheap->heap == NULL)
	{
		printf("you have a problem with your heap\n");
		return;
	}
	if (Treheap->heapSize == Treheap->maxSize)
	{
		printf("heap is full");
		return;
	}
	for (i = 0; i < Treheap->heapSize; i++)
		if (*(Treheap->heap + i) == key)return;
	*(Treheap->heap + Treheap->heapSize) = key;
	heapify3Up(Treheap, Treheap->heapSize);
	Treheap->heapSize++;
}
int minTrHeap(TRheap Treheap)
{
	if (Treheap == NULL || Treheap->heap == NULL || Treheap->heapSize == 0)
	{
		printf("you have a problem with your heap\n");
		return;
	}
	return *(Treheap->heap);
}
int extracMinTrHeap(TRheap Treheap)
{
	int min;
	if (Treheap == NULL || Treheap->heap == NULL || Treheap->heapSize == 0)
	{
		printf("you have a problem with your heap\n");
		return;
	}
	min = *(Treheap->heap);
	*(Treheap->heap) = *(Treheap->heap + Treheap->heapSize - 1);
	Treheap->heapSize--;
	if (Treheap->heapSize>0)heapify3Down(Treheap, 0);
	return min;
}
void ChangeKeyTrheap(TRheap Treheap, int i, int key)
{
	if (Treheap == NULL || Treheap->heap == NULL || Treheap->heapSize == 0)
	{
		printf("you have a problem with your heap\n");
		return;
	}
	*(Treheap->heap + (i - 1)) = key;
	heapify3Down(Treheap, i - 1);
	heapify3Up(Treheap, i - 1);
}
void dispalyTreHeap(TRheap TreHeap, int n)
{
	int *temp = TreHeap;
	int i;

	for (i = 0; i < n; i++)
	{
		printf("%d->", temp[i]);
	}
}
