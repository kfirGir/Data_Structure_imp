#ifndef TwTreTree
#define TwTreTree

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
/* ADT of a generic Stack  */
typedef struct TwoThreeNode {
	int key;
	int  high, low;
	struct TwoThreeNode* right;
	struct TwoThreeNode* left;
	struct TwoThreeNode* center;
	struct TwoThreeNode* parent;
}TwoThreeNode, *Pnode;

typedef struct TwoThreeTree {
	Pnode max;
	Pnode min;
	Pnode root;
}TwoThreeTree, *Ptree;


typedef enum { False, True } boolean;
typedef void * Node;

void msg_error(char * str);
TwoThreeTree createTree();
int NumSon(Pnode elem);
boolean isLeaf(Pnode elem);
Pnode searchInTree(Pnode root, int key);
Pnode createLeaf(int key);
Pnode createNode(int high, int low);
boolean insertToTree(Pnode root, int key, Pnode **maxTree, Pnode **minTree);
boolean removeInTree(Pnode root, int key, Pnode ** maxTree, Pnode ** minTree);
boolean ChangePriority(Pnode *Proot, int key, int NewKey, Pnode ** maxTree, Pnode ** minTree);
Pnode getMaxTree(TwoThreeTree tree);
void OrderMax(int ** Parr, int n);
Pnode getMinTree(TwoThreeTree tree);
void dispalyTree(Pnode root);

#endif