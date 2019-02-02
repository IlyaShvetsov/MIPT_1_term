// 2.2 Декартово дерево.Разница ширин
// Дано число N < 10^6 и последовательность пар целых чисел из[-2^31..2^31] длиной N. Построить декартово дерево из N узлов, 
// характеризующихся парами чисел Xi, Yi. Каждая пара чисел Xi, Yi определяет ключ Xi и приоритет Yi в декартовом дереве.
// Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции :
// При добавлении узла(x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте найденное поддерево по ключу x так, 
// чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла(x, y).
// Новый узел вставьте на место узла P.Построить также наивное дерево поиска по ключам Xi методом из задачи 1.
// Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска.
// Вывести их разницу. Разница может быть отрицательна.


#include <iostream>
#include <stack>
#include <fstream>
using namespace std;


struct CNode_Dec
{
	int Key;
	int Priority;
	CNode_Dec* left;
	CNode_Dec* right;

	CNode_Dec(int _key, int _priority) : Key(_key), Priority(_priority), left(0), right(0) {}
};

class Tree_Dec {
public:
	Tree_Dec();
	~Tree_Dec();

	void Insert(CNode_Dec*& Node, int key, int priority);
	int max();
	CNode_Dec* root;

//private:
	int *arr;

	void DFS_Destr(CNode_Dec* Node);
	void split(CNode_Dec* Node, int key, CNode_Dec*& leftTree, CNode_Dec*& rightTree);
	CNode_Dec* merge(CNode_Dec* leftTree, CNode_Dec* rightTree);
	void label(CNode_Dec* Node, int currentLevel);
};

Tree_Dec::Tree_Dec()
{
	root = NULL;
	arr = new int[1000000];
	for (int i = 0; i < 1000000; ++i)
		arr[i] = 0;
}

Tree_Dec::~Tree_Dec()
{
	DFS_Destr(root);
}

void Tree_Dec::DFS_Destr(CNode_Dec* Node)
{
	if (Node == NULL)
		return;
	DFS_Destr(Node->left);
	DFS_Destr(Node->right);
	delete Node;
}

void Tree_Dec::split(CNode_Dec* Node, int key, CNode_Dec*& leftTree, CNode_Dec*& rightTree)
{
	if (Node == 0) 
	{
		leftTree = 0;
		rightTree = 0;
		return;
	}
	if (Node->Key <= key)
	{
		split(Node->right, key, Node->right, rightTree);
		leftTree = Node;
	}
	else 
	{
		split(Node->left, key, leftTree, Node->left);
		rightTree = Node;
	}
}

CNode_Dec* Tree_Dec::merge(CNode_Dec* leftTree, CNode_Dec* rightTree)
{
	if (leftTree == 0) 
		return rightTree;
	if (rightTree == 0) 
		return leftTree;

	if (rightTree->Priority > leftTree->Priority) 
	{
		rightTree->left = merge(leftTree, rightTree->left);
		return rightTree;
	}
	else 
	{
		leftTree->right = merge(leftTree->right, rightTree);
		return leftTree;
	}
}

void Tree_Dec::Insert(CNode_Dec*& Node, int key, int priority)
{
	if (root == NULL)
	{
		root = new CNode_Dec(key, priority);
		return;
	}
	if (Node->Priority < priority)
	{
		CNode_Dec* leftTree;
		CNode_Dec* rightTree;
		split(Node, key, leftTree, rightTree);
		CNode_Dec* NewNode = new CNode_Dec(key, priority);
		NewNode->left = leftTree;
		NewNode->right = rightTree;
		Node = NewNode;
		return;
	}
	if (Node->Key <= key)
		if (Node->right != NULL)
			Insert(Node->right, key, priority);
		else
			Node->right = new CNode_Dec(key, priority);
	else
		if (Node->left != NULL)
			Insert(Node->left, key, priority);
		else
			Node->left = new CNode_Dec(key, priority);;
}

void Tree_Dec::label(CNode_Dec* Node, int currentLevel)
{
	if (Node == NULL) 
		return;

	arr[currentLevel]++;
	label(Node->left, currentLevel + 1);
	label(Node->right, currentLevel + 1);
}

int Tree_Dec::max()
{
	label(root, 0);
	int max = 0;
	for (int i = 0; i < 1000; ++i)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}



class MyTree {
private:
	struct CNode {
		int data;
		CNode* left;
		CNode* right;

		CNode(int key) :data(key), left(NULL), right(NULL) {}
	};
	CNode* root;
	int *arr;

	void DFS_Destr();
	void label(CNode* Node, int currentLevel);

public:
	MyTree();
	~MyTree() { DFS_Destr(); }

	void Insert(int key);
	int max();
};

MyTree::MyTree()
{
	root = NULL;
	arr = new int[1000000];
	for (int i = 0; i < 1000000; ++i)
		arr[i] = 0;
}

void MyTree::DFS_Destr()
{
	if (root == NULL)
		return;
	CNode* Node = root;
	stack <CNode*> STACK;
	STACK.push(Node);
	while (!STACK.empty())
	{
		Node = STACK.top();
		STACK.pop();
		CNode* left = Node->left;
		CNode* right = Node->right;
		delete Node;
		if (right != NULL)
			STACK.push(right);
		if (left != NULL)
			STACK.push(left);
	}
}

void MyTree::Insert(int key)
{
	if (root == NULL)
	{
		root = new CNode(key);
		return;
	}
	CNode* Node = root;
	while (Node != NULL)
	{
		if (Node->data <= key)
			if (Node->right != NULL)
				Node = Node->right;
			else
			{
				Node->right = new CNode(key);
				return;
			}
		else
			if (Node->left != NULL)
				Node = Node->left;
			else
			{
				Node->left = new CNode(key);
				return;
			}
	}
}

void MyTree::label(CNode* Node, int currentLevel)
{
	if (Node == 0) {
		return;
	}
	arr[currentLevel]++;
	label(Node->left, currentLevel + 1);
	label(Node->right, currentLevel + 1);
}

int MyTree::max()
{
	label(root, 0);
	int max = 0;
	for (int i = 0; i < 1000; ++i)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}



int main() {
	MyTree tree_1;
	Tree_Dec tree_2;
	int x, y, n;
	ifstream inp("input.txt");

	inp >> n;
	for (int i = 0; i < n; ++i)
	{
		inp >> x >> y;
		//tree_1.Insert(x);
		tree_2.Insert(tree_2.root, x, y);
	}

	CNode_Dec* leftTree;
	CNode_Dec* rightTree;
	tree_2.split(tree_2.root, 7, leftTree, rightTree);

	//cout << tree_2.max() - tree_1.max() << endl;

	return 0;
}