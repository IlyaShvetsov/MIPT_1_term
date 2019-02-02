// 4.1. —ама€ удаленна€ вершина
// ƒано невзвешенное дерево. –ассто€нием между двум€ вершинами будем называть количество ребер в пути, 
// соедин€ющем эти две вершины. ƒл€ каждой вершины определите рассто€ние до самой удаленной 
// от нее вершины. ¬рем€ работы должно быть O(n).

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


class CTree
{
private:
	struct CNode
	{
		int number;
		int content;
		int max_subtree;
		int second_subtree;
		int max;
		int index;		// от какого ребенка самое большое поддерево (ѕо content-у)
		int second;
		int* children;
		int size;
		int real_size;

		CNode(int i) : number(-1), content(i), real_size(0), index(-1),
			max_subtree(0), max(0), size(10), second(0), second_subtree(0)
		{
			children = new int[10];
		}
		~CNode() { delete[] children; }
		void grow()
		{
			size *= 2;
			int* new_children = children;
			children = new int[size];
			for (int i = 0; i < size / 2; ++i)
				children[i] = new_children[i];
			delete[] new_children;
		}
	};
	CNode **arr;
	int count;

	int find_subtree(CNode* Node);
	void find_max(CNode* Node, CNode* Parent);
	void sort();
	void Merge(CNode** a, int aLen, CNode** b, int bLen, CNode** c);
	void MergeSort(CNode** a, int aLen);

public:
	CTree(int n);
	~CTree();
	void add(int a, int b);
	void go();
};

CTree::CTree(int n)
{
	count = 0;
	arr = new CNode*[n];
	for (int i = 0; i < n; ++i)
		arr[i] = new CNode(i);
}

CTree::~CTree()
{
	for (int i = 0; i < count; ++i)
		delete arr[i];
	delete[] arr;
}

void CTree::add(int a, int b)
{
	if (arr[a]->number == -1)
	{
		arr[a]->number = count;
		count++;
	}
	if (arr[b]->number == -1)
	{
		arr[b]->number = count;
		count++;
	}
	if (b < a)
	{
		arr[b]->children[arr[b]->real_size] = a;
		arr[b]->real_size++;
		if (arr[b]->real_size == arr[b]->size)
			arr[b]->grow();
	}
	else
	{
		arr[a]->children[arr[a]->real_size] = b;
		arr[a]->real_size++;
		if (arr[a]->real_size == arr[a]->size)
			arr[a]->grow();
	}
}

void CTree::go()
{
	find_subtree(arr[0]);
	arr[0]->max = arr[0]->max_subtree;
	arr[0]->second = arr[0]->second_subtree;
	for (int i = 0; i < arr[0]->real_size; ++i)
		find_max(arr[arr[0]->children[i]], arr[0]);
	sort();
	for (int i = 0; i < count; ++i)
		cout << arr[i]->max << endl;
}

int CTree::find_subtree(CNode* Node) // поиск самого высокого поддерева
{
	if (!Node->real_size)
		return 1;
	int x;
	for (int i = 0; i < Node->real_size; ++i)
	{
		x = find_subtree(arr[Node->children[i]]);
		if (x >= Node->max_subtree)
		{
			Node->second_subtree = Node->max_subtree;
			Node->max_subtree = x;
			Node->index = arr[Node->children[i]]->content;
		}
		else
			if (x > Node->second_subtree)
				Node->second_subtree = x;
	}
	return Node->max_subtree + 1;
}

void CTree::find_max(CNode* Node, CNode* Parent) // поиск максимального рассто€ни€
{
	if (Node->content == Parent->index)
	{
		if (Node->max_subtree > Parent->second + 1)
		{
			Node->max = Node->max_subtree;
			if (Node->second_subtree > Parent->second + 1)
				Node->second = Node->second_subtree;
			else
				Node->second = Parent->second + 1;
		}
		else
		{
			Node->index = -1;
			Node->max = Parent->second + 1;
			Node->second = Node->max_subtree;
		}
	}
	else
	{
		Node->index = -1;
		if (Node->max_subtree > Parent->max + 1)
		{
			Node->max = Node->max_subtree;
			if (Node->second_subtree > Parent->max + 1)
				Node->second = Node->second_subtree;
			else
				Node->second = Parent->max + 1;
		}
		else
		{
			Node->max = Parent->max + 1;
			if (Node->max_subtree > Parent->second + 1)
				Node->second = Node->max_subtree;
			else
				Node->second = Parent->second + 1;
		}
	}
	for (int i = 0; i < Node->real_size; ++i)
		find_max(arr[Node->children[i]], Node);
}

void CTree::sort()
{
	MergeSort(arr, count);
}

void CTree::Merge(CNode** a, int aLen, CNode** b, int bLen, CNode** c)
{
	int i = 0, j = 0;
	while (i < aLen && j < bLen)
	{
		if (a[i]->number < b[j]->number)
		{
			c[i + j] = a[i];
			++i;
		}
		else
		{
			c[i + j] = b[j];
			++j;
		}
	}
	if (i == aLen)
		for (; j < bLen; ++j)
			c[i + j] = b[j];
	else
		for (; i < aLen; ++i)
			c[i + j] = a[i];
}

void CTree::MergeSort(CNode** a, int aLen)
{
	if (aLen <= 1)
		return;
	int Len1 = aLen / 2;
	int Len2 = aLen - Len1;
	MergeSort(a, Len1);
	MergeSort(a + Len1, Len2);
	CNode** c = new CNode*[aLen];
	Merge(a, Len1, a + Len1, Len2, c);
	memcpy(a, c, sizeof(CNode*)*aLen);
	delete[]c;
}





int main()
{
	ifstream inp("input.txt");
	int n, a, b;
	inp >> n;
	CTree tree(n);
	for (int i = 1; i < n; ++i)
	{
		inp >> a >> b;
		tree.add(a, b);
	}
	tree.go();
	return 0;
}