#include "23Tree.h"

TwoThreeTree createTree()
{
	Ptree t;
	t = (Ptree)malloc(sizeof(TwoThreeTree));
	if (t == NULL)msg_error("memory not aloocated");
	t->max = NULL;
	t->min = NULL;
	t->root = NULL;
	return *t;

}
int NumSon(Pnode elem)
{
	int count = 0;
	if (elem->center)count++;
	if (elem->right)count++;
	if (elem->left)count++;
	return count;
}
boolean isLeaf(Pnode elem)
{
	return((!elem->center) && (!elem->right) && (!elem->left));
}
Pnode searchInTree(Pnode root, int key)
{
	Pnode temp = root;
	while (temp)
	{
		if (isLeaf(temp) && temp->key == key)return temp;
		if (key >= temp->high)temp = temp->right;
		else
			if (temp->low && key >= temp->low)
				temp = temp->center;
			else
				temp = temp->left;

	}
	return NULL;
}
Pnode createLeaf(int key)
{
	Pnode newNode;
	newNode = (Pnode)malloc(sizeof(TwoThreeNode));
	if (!newNode)msg_error("memory not allocated");
	newNode->parent = newNode->center = newNode->right = newNode->left = NULL;
	newNode->high = newNode->low = NULL;
	newNode->key = key;
	return newNode;
}
Pnode createNode(int high, int low)
{
	Pnode newNode;
	newNode = (Pnode)malloc(sizeof(TwoThreeNode));
	if (!newNode)msg_error("memory not allocated");
	newNode->parent = newNode->center = newNode->right = newNode->left = NULL;
	newNode->high = high;
	newNode->low = low;
	newNode->key = NULL;
	return newNode;
}
void OrderMax(int *arr, int n)
{
	int c, d, swap;
	for (c = 0; c < (n - 1); c++)
	{
		for (d = 0; d < n - c - 1; d++)
		{
			if (arr[d] > arr[d + 1])
			{
				swap = arr[d];
				arr[d] = arr[d + 1];
				arr[d + 1] = swap;
			}
		}
	}
	return arr;
}
boolean insertToTree(Pnode* Proot, int key, Pnode * maxTree, Pnode * minTree)
{
	int arr[4] = { 0 };
	int n, flag = 0;
	Pnode root = *Proot;
	Pnode parent, grand, temp;
	Pnode Pleft, Pright, NewNode;
	if (searchInTree(root, key))return False;
	if (!root)
	{
		root = createLeaf(key);;
		*maxTree = root;
		*minTree = root;
		*Proot = root;
		return True;
	}
	parent = root->parent;
	if (isLeaf(root))
	{
		if (root->key < key)
		{
			NewNode = createNode(key, NULL);
			NewNode->right = createLeaf(key);
			NewNode->left = root;
			NewNode->right->parent = NewNode;
			root->parent = NewNode;
			*Proot = NewNode;
			root = *Proot;
			while (root&&!isLeaf(root))root = root->left;
			*minTree = root;
			root = *Proot;
			while (root&&!isLeaf(root))root = root->right;
			*maxTree = root;
			return True;
		}
		NewNode = createNode(root->key, NULL);
		NewNode->left = createLeaf(key);
		NewNode->right = root;
		NewNode->left->parent = NewNode;
		root->parent = NewNode;
		*Proot = NewNode;
		root = *Proot;
		while (root&&!isLeaf(root))root = root->left;
		*minTree = root;
		root = *Proot;
		while (root&&!isLeaf(root))root = root->right;
		*maxTree = root;
		return True;
	}
	parent = root;
	while (root != NULL&&!isLeaf(root))
	{

		if (root->left && NumSon(root) == 2 && isLeaf(root->left))
		{
			if (((root->left)->key) < key && (key < root->high))
			{
				root->center = createLeaf(key);;
				if (root->center)
				{
					root->low = key;
					root = *Proot;
					while (root&&!isLeaf(root))root = root->left;
					*minTree = root;
					root = *Proot;
					while (root&&!isLeaf(root))root = root->right;
					*maxTree = root;
					return True;
				}
			}
			else
			{
				parent = root;
				break;
			}
		}
		parent = root;
		if ((root->low && key < root->low) || (!root->low&&key<root->high))root = root->left;
		else if (key > root->high)root = root->right;
		else root = root->center;
	}
	arr[0] = key;
	arr[1] = parent->left->key;
	arr[2] = parent->right->key;
	n = 3;
	if (NumSon(parent) > 2)
	{
		arr[3] = parent->center->key;
		n = 4;
	}
	OrderMax(arr, n);
	if (n == 3)
	{
		parent->left->key = arr[0];
		parent->left->parent = parent;
		parent->right->parent = parent;
		parent->center = createLeaf(arr[1]);
		parent->center->parent = parent;
		parent->right->key = arr[2];
		parent->low = arr[1];
		parent->high = arr[2];
		root = *Proot;
		while (root&&!isLeaf(root))root = root->left;
		*minTree = root;
		root = *Proot;
		while (root&&!isLeaf(root))root = root->right;
		*maxTree = root;
		return True;
	}
	parent->left->key = arr[0];
	parent->center->key = arr[1];
	parent->right->key = arr[3];
	parent->low = arr[1];
	parent->high = arr[2];
	Pleft = createNode(arr[1], NULL);
	Pleft->left = parent->left;
	Pleft->right = parent->center;
	Pleft->left->parent = Pleft;
	Pleft->right->parent = Pleft;
	Pright = createNode(arr[3], NULL);
	Pright->left = createLeaf(arr[2]);
	Pright->left->parent = Pright;
	Pright->right = parent->right;
	Pright->right->parent = Pright;
	parent->center = NULL;
	if (!parent->parent)
	{
		parent->high = arr[2];
		parent->low = NULL;
		parent->center = NULL;
		parent->left = Pleft;
		parent->right = Pright;
		Pleft->parent = parent;
		Pright->parent = parent;
		root = *Proot;
		while (root&&!isLeaf(root))root = root->left;
		*minTree = root;
		root = *Proot;
		while (root&&!isLeaf(root))root = root->right;
		*maxTree = root;
		return True;
	}
	grand = parent->parent;
	while (grand)
	{
		n = NumSon(grand);
		flag = 0;
		if (n == 2)
		{
			if (parent == grand->left)
			{
				NewNode = parent;
				parent = grand;
				parent->center = Pright;
				parent->left = Pleft;
				Pleft->parent = parent;
				Pright->parent = parent;
				parent->low = arr[2];
				free(NewNode);
				root = *Proot;
				while (root&&!isLeaf(root))root = root->left;
				*minTree = root;
				root = *Proot;
				while (root&&!isLeaf(root))root = root->right;
				*maxTree = root;
				return True;
			}
			else
			{
				NewNode = parent;
				parent = grand;
				parent->center = Pleft;
				parent->right = Pright;
				Pleft->parent = parent;
				Pright->parent = parent;
				parent->low = parent->high;
				parent->high = arr[2];
				free(NewNode);
				root = *Proot;
				while (root&&!isLeaf(root))root = root->left;
				*minTree = root;
				root = *Proot;
				while (root&&!isLeaf(root))root = root->right;
				*maxTree = root;
				return True;
			}
		}
		if (parent == grand->right)
		{
			NewNode = createNode(grand->low, NULL);
			NewNode->left = grand->left;
			grand->left->parent = NewNode;
			NewNode->right = grand->center;
			grand->center->parent = NewNode;
			parent->left = Pleft;
			parent->right = Pright;
			grand->low = parent->low = parent->center = NULL;
			Pleft->parent = parent;
			Pright->parent = parent;
			if (!grand->parent)
			{
				grand->left = NewNode;
				NewNode->parent = grand;
				grand->right = parent;
				parent->parent = grand;
				grand->low = NULL;
				parent->center = NULL;
				grand->center = NULL;
				parent->low = NULL;
				root = *Proot;
				while (root&&!isLeaf(root))root = root->left;
				*minTree = root;
				root = *Proot;
				while (root&&!isLeaf(root))root = root->right;
				*maxTree = root;
				return True;
			}
			else
			{
				arr[2] = grand->high;
				Pleft = NewNode;
				Pright = parent;
				temp = grand->parent;
				parent = grand;
				grand = temp;
				flag = 1;
			}
		}
		if (!flag && parent == grand->center)
		{
			NewNode = createNode(grand->low, NULL);
			NewNode->left = grand->left;
			grand->left->parent = NewNode;
			NewNode->right = Pleft;
			parent->left = Pright;
			parent->right = grand->right;
			grand->right->parent = parent;
			parent->high = grand->high;
			Pleft->parent = NewNode;
			Pright->parent = parent;
			grand->high = arr[2];
			parent->low = grand->low = NULL;
			parent->center = NULL;
			if (!grand->parent)
			{
				grand->left = NewNode;
				NewNode->parent = grand;
				grand->right = parent;
				parent->parent = grand;
				grand->low = NULL;
				parent->center = NULL;
				grand->center = NULL;
				parent->low = NULL;
				root = *Proot;
				while (root&&!isLeaf(root))root = root->left;
				*minTree = root;
				root = *Proot;
				while (root&&!isLeaf(root))root = root->right;
				*maxTree = root;
				return True;
			}
			else
			{
				Pleft = NewNode;
				Pright = parent;
				temp = grand->parent;
				parent = grand;
				grand = temp;
				flag = 1;
			}
		}
		if (!flag && parent == grand->left)
		{
			NewNode = createNode(grand->high, NULL);
			NewNode->left = grand->center;
			grand->center->parent = NewNode;
			NewNode->right = grand->right;
			grand->right->parent = NewNode;
			parent->left = Pleft;
			parent->right = Pright;
			Pleft->parent = parent;
			Pright->parent = parent;
			grand->high = grand->low;
			parent->high = arr[2];
			parent->low = NULL;
			parent->center = NULL;
			if (!grand->parent)
			{
				grand->left = parent;
				parent->parent = grand;
				grand->right = NewNode;
				NewNode->parent = grand;
				grand->low = NULL;
				parent->center = NULL;
				grand->center = NULL;
				parent->low = NULL;
				root = *Proot;
				while (root&&!isLeaf(root))root = root->left;
				*minTree = root;
				root = *Proot;
				while (root&&!isLeaf(root))root = root->right;
				*maxTree = root;
				return True;
			}
			else
			{
				Pleft = parent;
				Pright = NewNode;
				arr[2] = grand->high;
				temp = grand->parent;
				parent = grand;
				grand = temp;
				flag = 1;
			}
		}
	}
	return False;

}
boolean removeInTree(Pnode *root, int key, Pnode * maxTree, Pnode * minTree)
{
	Pnode toDel, parent, grand, bro, temp;
	int flag = 0;
	int sortHigh[3] = { 0 };
	toDel = searchInTree(*root, key);
	if (toDel == NULL)return False;
	if (!toDel->parent)
	{
		free(*root);
		*root = NULL;
		*maxTree = *minTree = NULL;
		return True;
	}
	parent = toDel->parent;
	sortHigh[0] = parent->right->key;
	if (parent->center)sortHigh[1] = parent->center->key;
	sortHigh[2] = parent->left->key;
	if (NumSon(parent) > 2)
	{
		if (parent->center == toDel)
		{
			parent->low = NULL;
			parent->center = NULL;
			free(toDel);
			temp = *root;
			while (temp&&!isLeaf(temp))temp = temp->left;
			*minTree = temp;
			temp = *root;
			while (temp&&!isLeaf(temp))temp = temp->right;
			*maxTree = temp;
			return True;
		}
		if (parent->right == toDel)
		{
			parent->high = parent->low;
			parent->right = parent->center;
			parent->low = parent->center = NULL;
			free(toDel);
			temp = *root;
			while (temp&&!isLeaf(temp))temp = temp->left;
			*minTree = temp;
			temp = *root;
			while (temp&&!isLeaf(temp))temp = temp->right;
			*maxTree = temp;
			return True;
		}
		if (parent->left == toDel)
		{
			parent->left = parent->center;
			parent->low = parent->center = NULL;
			free(toDel);
			temp = *root;
			while (temp&&!isLeaf(temp))temp = temp->left;
			*minTree = temp;
			temp = *root;
			while (temp&&!isLeaf(temp))temp = temp->right;
			*maxTree = temp;
			return True;
		}
	}
	else
	{
		if (!(parent->parent))
		{
			if (parent->left == toDel)
			{
				parent->right->parent = NULL;
				*root = parent->right;
			}
			else
			{
				parent->left->parent = NULL;
				*root = parent->left;
			}
			free(toDel);
			free(parent);
			temp = *root;
			while (temp&&!isLeaf(temp))temp = temp->left;
			*minTree = temp;
			temp = *root;
			while (temp&&!isLeaf(temp))temp = temp->right;
			*maxTree = temp;
			return True;
		}
		grand = parent->parent;
		do
		{

			if (NumSon(grand) > 2)
			{
				if (parent == grand->left)
				{
					if (NumSon(grand->center) > 2)
					{
						bro = grand->center;
						if (parent->left == toDel)
						{
							parent->left = parent->right;
							parent->right = bro->left;
							parent->right->parent = parent;
							bro->left = bro->center;
							parent->high = grand->low;
							grand->low = bro->low;
							bro->center = NULL;
							bro->low = NULL;
							free(toDel);
							temp = *root;
							while (temp&&!isLeaf(temp))temp = temp->left;
							*minTree = temp;
							temp = *root;
							while (temp&&!isLeaf(temp))temp = temp->right;
							*maxTree = temp;
							return True;
						}
						else
						{
							parent->right = bro->left;
							parent->right->parent = parent;
							bro->left = bro->center;
							parent->high = grand->low;
							grand->low = bro->low;
							bro->center = NULL;
							bro->low = NULL;
							free(toDel);
							temp = *root;
							while (temp&&!isLeaf(temp))temp = temp->left;
							*minTree = temp;
							temp = *root;
							while (temp&&!isLeaf(temp))temp = temp->right;
							*maxTree = temp;
							return True;
						}
					}
					else
					{
						bro = grand->center;
						bro->center = bro->left;
						if (toDel == parent->left)bro->left = parent->right;
						else bro->left = parent->left;
						bro->left->parent = bro;
						bro->low = grand->low;
						grand->left = grand->center;
						grand->center = NULL;
						grand->low = NULL;
						free(toDel);
						free(parent);
						temp = *root;
						while (temp&&!isLeaf(temp))temp = temp->left;
						*minTree = temp;
						temp = *root;
						while (temp&&!isLeaf(temp))temp = temp->right;
						*maxTree = temp;
						return True;
					}
				}
				if (parent == grand->right&&NumSon(grand->center) > 2)
				{
					bro = grand->center;
					if (parent->right == toDel)
					{
						parent->right = parent->left;
						parent->left = bro->right;
						parent->left->parent = parent;
						bro->right = bro->center;
						parent->high = grand->high;
						grand->high = bro->high;
						bro->high = bro->low;
						bro->low = NULL;
						bro->center = NULL;
						free(toDel);
						temp = *root;
						while (temp&&!isLeaf(temp))temp = temp->left;
						*minTree = temp;
						temp = *root;
						while (temp&&!isLeaf(temp))temp = temp->right;
						*maxTree = temp;
						return True;
					}
					else
					{
						parent->left = bro->right;
						parent->left->parent = parent;
						bro->right = bro->center;
						grand->high = bro->high;
						bro->high = bro->low;
						bro->center = NULL;
						bro->low = NULL;
						free(toDel);
						temp = *root;
						while (temp&&!isLeaf(temp))temp = temp->left;
						*minTree = temp;
						temp = *root;
						while (temp&&!isLeaf(temp))temp = temp->right;
						*maxTree = temp;
						return True;
					}
				}
				if (parent == grand->right)
				{
					bro = grand->center;
					bro->center = bro->right;
					bro->low = bro->high;
					if (toDel == parent->left)
					{
						bro->right = parent->right;
						bro->right->parent = bro;
						bro->high = grand->high;
						grand->high = grand->low;
					}
					else
					{
						bro->right = parent->left;
						bro->right->parent = bro;
						bro->high = grand->high;
						grand->high = grand->low;
					}
					grand->right = grand->center;
					grand->center = NULL;
					grand->low = NULL;
					free(toDel);
					free(parent);
					temp = *root;
					while (temp&&!isLeaf(temp))temp = temp->left;
					*minTree = temp;
					temp = *root;
					while (temp&&!isLeaf(temp))temp = temp->right;
					*maxTree = temp;
					return True;
				}
			}
			if (parent == grand->center&&NumSon(grand->left) > 2)
			{
				bro = grand->left;
				if (parent->right == toDel)
				{
					parent->right = parent->left;
					parent->left = bro->right;
					parent->left->parent = parent;
					bro->right = bro->center;
					parent->high = grand->low;
					grand->low = bro->high;
					bro->high = bro->low;
					bro->center = NULL;
					bro->low = NULL;
					free(toDel);
					temp = *root;
					while (temp&&!isLeaf(temp))temp = temp->left;
					*minTree = temp;
					temp = *root;
					while (temp&&!isLeaf(temp))temp = temp->right;
					*maxTree = temp;
					return True;
				}
				else
				{
					parent->left = bro->right;
					parent->left->parent = parent;
					bro->right = bro->center;
					grand->low = bro->high;
					bro->high = bro->low;
					bro->center = NULL;
					bro->low = NULL;
					free(toDel);
					temp = *root;
					while (temp&&!isLeaf(temp))temp = temp->left;
					*minTree = temp;
					temp = *root;
					while (temp&&!isLeaf(temp))temp = temp->right;
					*maxTree = temp;
					return True;
				}
			}
			if (parent == grand->center&&NumSon(grand->right) > 2)
			{
				bro = grand->right;
				if (parent->left == toDel)
				{
					parent->left = parent->right;
					parent->right = bro->left;
					parent->right->parent = parent;
					bro->left = bro->center;
					grand->low = parent->high;
					parent->high = grand->high;
					grand->high = bro->low;
					bro->center = NULL;
					bro->low = NULL;
					free(toDel);
					temp = *root;
					while (temp&&!isLeaf(temp))temp = temp->left;
					*minTree = temp;
					temp = *root;
					while (temp&&!isLeaf(temp))temp = temp->right;
					*maxTree = temp;
					return True;
				}
				else
				{
					parent->right = bro->left;
					parent->right->parent = parent;
					bro->left = bro->center;
					grand->low = bro->high;
					parent->high = grand->high;
					grand->high = bro->low;
					bro->center = NULL;
					bro->low = NULL;
					free(toDel);
					temp = *root;
					while (temp&&!isLeaf(temp))temp = temp->left;
					*minTree = temp;
					temp = *root;
					while (temp&&!isLeaf(temp))temp = temp->right;
					*maxTree = temp;
					return True;
				}
			}
			if (parent == grand->center)
			{
				bro = grand->right;
				bro->center = bro->left;
				if (toDel == parent->left)
				{
					bro->left = parent->right;
					bro->left->parent = bro;
					bro->low = grand->high;
					grand->high = parent->high;
				}
				else
				{
					bro->left = parent->left;
					bro->left->parent = bro;
					bro->low = grand->high;
					grand->high = grand->low;
				}
				grand->center = NULL;
				grand->low = NULL;
				free(toDel);
				free(parent);
				temp = *root;
				while (temp&&!isLeaf(temp))temp = temp->left;
				*minTree = temp;
				temp = *root;
				while (temp&&!isLeaf(temp))temp = temp->right;
				*maxTree = temp;
				return True;
			}
			else
			{
				if (parent == grand->right&&NumSon(grand->left) > 2)
				{
					bro = grand->left;
					if (parent->right == toDel)
					{
						parent->right = parent->left;
						parent->left = bro->right;
						parent->left->parent = parent;
						bro->right = bro->center;
						parent->high = grand->high;
						grand->high = bro->high;
						bro->high = bro->low;
						bro->center = NULL;
						bro->low = NULL;
						free(toDel);
						temp = *root;
						while (temp&&!isLeaf(temp))temp = temp->left;
						*minTree = temp;
						temp = *root;
						while (temp&&!isLeaf(temp))temp = temp->right;
						*maxTree = temp;
						return True;
					}
					else
					{
						parent->left = bro->right;
						parent->left->parent = parent;
						bro->right = bro->center;
						grand->high = bro->high;
						bro->high = bro->low;
						bro->center = NULL;
						bro->low = NULL;
						free(toDel);
						return True;
					}
				}
				if (parent == grand->left&&NumSon(grand->right) > 2)
				{
					bro = grand->right;
					if (parent->left == toDel)
					{
						parent->left = parent->right;
						parent->right = bro->left;
						parent->right->parent = parent;
						bro->left = bro->center;
						parent->high = grand->high;
						grand->high = bro->low;
						bro->center = NULL;
						bro->low = NULL;
						free(toDel);
						temp = *root;
						while (temp&&!isLeaf(temp))temp = temp->left;
						*minTree = temp;
						temp = *root;
						while (temp&&!isLeaf(temp))temp = temp->right;
						*maxTree = temp;
						return True;
					}
					else
					{
						parent->right = bro->left;
						parent->right->parent = parent;
						bro->left = bro->center;
						parent->high = grand->high;
						grand->high = bro->low;
						bro->center = NULL;
						bro->low = NULL;
						free(toDel);
						temp = *root;
						while (temp&&!isLeaf(temp))temp = temp->left;
						*minTree = temp;
						temp = *root;
						while (temp&&!isLeaf(temp))temp = temp->right;
						*maxTree = temp;
						return True;
					}
				}
			}
			if (parent == grand->left)
			{
				bro = grand->right;
				bro->center = bro->left;
				if (toDel == parent->left)
				{
					bro->left = parent->right;
					parent->right->parent = bro;
					bro->low = grand->high;
					grand->high = parent->high;
				}
				else
				{
					bro->left = parent->left;
					parent->left->parent = bro;
					bro->low = grand->high;
					grand->high = sortHigh[2];
				}
				parent->low = parent->right = NULL;
				free(toDel);
				parent->high = parent->left = NULL;
				toDel = parent;
				parent = grand;
				grand = grand->parent;
				flag = 1;
			}
			else
			{
				bro = grand->left;
				bro->center = bro->right;
				if (toDel == parent->left)
				{
					bro->right = parent->right;
					parent->right->parent = bro;
					bro->low = bro->high;
					bro->high = parent->high;
					grand->high = parent->high;
				}
				else
				{
					bro->right = parent->left;
					parent->left->parent = bro;
					bro->low = bro->high;
					bro->high = grand->high;
				}
				parent->low = parent->right = NULL;
				free(toDel);
				parent->high = parent->left = NULL;
				toDel = parent;
				parent = grand;
				grand = grand->parent;
				flag = 1;
			}
		} while (flag == 1 && grand);
		bro->parent = NULL;
		*root = bro;
		parent->right = NULL;
		free(toDel);
		free(parent);
		temp = *root;
		while (temp&&!isLeaf(temp))temp = temp->left;
		*minTree = temp;
		temp = *root;
		while (temp&&!isLeaf(temp))temp = temp->right;
		*maxTree = temp;
		return True;
	}
}
boolean ChangePriority(Pnode *Proot, int key, int NewKey, Pnode * maxTree, Pnode * minTree)
{
	Pnode root = *Proot;
	Pnode toChange;
	if (!(toChange = searchInTree(root, key)))return False;
	removeInTree(Proot, key, maxTree, minTree);
	insertToTree(Proot, NewKey, maxTree, minTree);
	return True;
}
Pnode getMaxTree(TwoThreeTree tree)
{
	return tree.max;
}
Pnode getMinTree(TwoThreeTree tree)
{
	return tree.min;
}
void dispalyTree(Pnode root)
{
	if (!root)return;
	if (isLeaf(root))printf("%d->", root->key);
	else
	{
		if (root->low)printf("\n(%d,%d):\n", root->low, root->high);
		else printf("\n(%d):\n", root->high);
	}
	dispalyTree(root->left);
	dispalyTree(root->center);
	dispalyTree(root->right);
}