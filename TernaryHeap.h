#ifndef TrenaryHeap
#define TrenaryHeap

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
typedef struct trenaryHeap
{
	int * heap;
	int maxSize;
	int heapSize;
}trenaryHeap, *TRheap;

int Parent(int i);
int Left(int i);
int Center(int i);
int Right(int i);
trenaryHeap createTRheap(int maxSize);
void heapify3Down(TRheap Treheap, int i);
void heapify3Up(TRheap Treheap, int i);
void BulidTrHeap(int* A, int n, TRheap Treheap);
void insertTrheap(TRheap Treheap, int key);
int minTrHeap(TRheap Treheap);
int extracMinTrHeap(TRheap Treheap);
void ChangeKeyTrheap(TRheap Treheap, int i, int key);
void dispalyTreHeap(TRheap TreHeap, int n);

#endif