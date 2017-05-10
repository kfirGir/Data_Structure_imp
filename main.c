#include "23Tree.h"
#include "Pringheap.h"
#include "TernaryHeap.h"

int main()
{
	int rnd=1, min;
	int n = 0, i, j = 0;
	int A[100] = { 0 };
	TwoThreeTree tree = createTree();
	trenaryHeap TreHeap = createTRheap(100);
	Pheap ParHeap = NULL;
	srand(time(0));
	for (i = 0; i <10; i++)
	{
		rnd += rand() % 4 + 1;
		insertToTree(&tree.root, rnd, &tree.max, &tree.min);
		ParHeap = insertPheap(ParHeap, rnd);
		A[i] = rnd;
		n++;
	}
	BulidTrHeap(A, n, &TreHeap);
	printf("\n\n					TreHeap					\n\n");
	dispalyTreHeap(TreHeap.heap, TreHeap.heapSize);
	printf("\n\n\n					ParHeap					\n\n");
	dispalyPheap(ParHeap);
	printf("\n\n\n\n\n\n					23Tree					\n\n");
	dispalyTree(tree.root);
	for (j = 0; j < 8; j++)
	{
		for (i = 0; i < 2; i++)
		{
			removeInTree(&tree.root, tree.min->key, &tree.max, &tree.min);
			ParHeap = DeleteMinPheap(&min, ParHeap);
			extracMinTrHeap(&TreHeap);
			n--;
		}
		rnd = rand() % 100 + 1;
		ChangePriority(&tree.root, tree.min->key, rnd, &tree.max, &tree.min);
		ChangeKeyTrheap(&TreHeap, 1, rnd);
		for (i = 0; i < 10; i++)
		{
			rnd = rand() % 100 + 1;
			insertToTree(&tree.root, rnd, &tree.max, &tree.min);
			ParHeap = insertPheap(ParHeap, rnd);
			insertTrheap(&TreHeap, rnd);
		}
		printf("\n\n					TreHeap					\n\n");
		dispalyTreHeap(TreHeap.heap, TreHeap.heapSize);
		printf("\n\n\n					ParHeap					\n\n");
		dispalyPheap(ParHeap);
		printf("\n\n\n\n\n\n					23Tree					\n\n");
		dispalyTree(tree.root);
	}

	_getch();
	return 0;
}