// Задача 1.2. Порядок обхода
// Дано число N < 10^6 и последовательность целых чисел из[-2^31..2^31] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
// то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
// 1_2.Выведите элементы в порядке pre - order(сверху вниз).


#include <iostream>
#include <fstream>
#include <stack>
using namespace std;


class MyTree {
private:
	struct CNode {
		int data;
		CNode* left;
		CNode* right;

		CNode(int key) :data(key), left(NULL), right(NULL) {}
	};
	CNode* root;

	void DFS_Destr();

public:
	MyTree() : root(NULL) {}
	~MyTree() { DFS_Destr(); }

	void Insert(int key);
	void Show();
};

void MyTree::Show()
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
		cout << Node->data << " ";
		if (Node->right != NULL)
			STACK.push(Node->right);
		if (Node->left != NULL)
			STACK.push(Node->left);
	}
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



int main()
{
	int n, key;
	MyTree tree;
	ifstream inp("input.txt");
	inp >> n;
	for (int i = 0; i < n; ++i)
	{
		inp >> key;
		tree.Insert(key);
	}
	tree.Show();

	return 0;
}