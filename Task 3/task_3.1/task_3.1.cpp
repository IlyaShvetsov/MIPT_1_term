// Задача 3.1. Солдаты
// В одной военной части решили построить в одну шеренгу по росту.
// Т.к.часть была далеко не образцовая, то солдаты часто приходили не вовремя,
// а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
// Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены 
// по росту – сначала самые высокие, а в конце – самые низкие.
// За расстановку солдат отвечал прапорщик, который заметил интересную особенность – 
// все солдаты в части разного роста. Ваша задача состоит в том, 
// чтобы помочь прапорщику правильно расставлять солдат, а именно 
// для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
// Требуемая скорость выполнения команды - O(log n).


#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct CNode {
	int data;
	CNode* left;
	CNode* right;
	int height;
	int count;

	CNode(int key) :data(key), left(NULL), right(NULL), height(1), count(1) {}
};

class Ginger {
private:
	CNode* RootOfGinger; // будоражит кровь мою и сердце

	int height(CNode* p);
	int bfactor(CNode* p);
	void fixheight(CNode* p);
	CNode* rotateRight(CNode* p);
	CNode* rotateLeft(CNode* q);
	CNode* balance(CNode* p);
	void DFS_Destr(CNode* Node);
	CNode* Ins(CNode* Node, int key, int& index);
	int getCount(CNode* Node);
	int DeleteByIndex(CNode* Node, int index);
	CNode* remove_min(CNode* Node);
	CNode* findmin(CNode* Node);

public:
	Ginger() : RootOfGinger(NULL) {}
	~Ginger() { DFS_Destr(RootOfGinger); }

	CNode* DeleteByKey(CNode* Node, int key);
	int Insert(int key);
	void Delete(int index);

	void printAsTree(CNode* Node, int currentLevel);
	void show();
};

void Ginger::DFS_Destr(CNode* Node) 
{
	if (Node == NULL)
		return;
	DFS_Destr(Node->left);
	DFS_Destr(Node->right);
	delete Node;
}

int Ginger::Insert(int key)
{
	int index = 0;
	RootOfGinger = Ins(RootOfGinger, key, index);
	return index;
}

CNode* Ginger::Ins(CNode* Node, int key, int& index) // вставка ключа k в дерево с корнем p
{
	if (Node == NULL)
		return new CNode(key);
	if (key < Node->data)
	{
		index += getCount(Node->right) + 1;
		Node->left = Ins(Node->left, key, index);
	}
	else
		Node->right = Ins(Node->right, key, index);
	return balance(Node);
}

CNode* Ginger::findmin(CNode* Node)
{
	return Node->left != NULL ? findmin(Node->left) : Node;
}

CNode* Ginger::remove_min(CNode* Node)
{
	if (Node->left == NULL)
		return Node->right;
	Node->left = remove_min(Node->left);
	Node = balance(Node);
	return Node;
}

CNode* Ginger::DeleteByKey(CNode* Node, int key)
{
	if (Node == NULL) 
		return 0;
	if (key < Node->data)
		Node->left = DeleteByKey(Node->left, key);
	else 
		if (key > Node->data)
			Node->right = DeleteByKey(Node->right, key);
	else
	{
		CNode* left = Node->left;
		CNode* right = Node->right;
		delete Node;
		if (!right) return left;
		CNode* min = findmin(right);
		min->right = remove_min(right);
		min->left = left;
		return balance(min);
	}
	return balance(Node);
}

int Ginger::DeleteByIndex(CNode* Node, int index)
{
	int count_right = getCount(Node->right);
	if (count_right == index)
		return Node->data;
	if (index < count_right)
		return DeleteByIndex(Node->right, index);
	return DeleteByIndex(Node->left, index - 1 - count_right);
}

void Ginger::Delete(int index)
{
	if (RootOfGinger == NULL || index < 0 || index > getCount(RootOfGinger) - 1)
		return;
	RootOfGinger = DeleteByKey(RootOfGinger, DeleteByIndex(RootOfGinger, index));
}

int Ginger::height(CNode* Node)
{
	return Node ? Node->height : 0;
}

int Ginger::bfactor(CNode* Node)
{
	return height(Node->right) - height(Node->left);
}

void Ginger::fixheight(CNode* Node)
{
	int hl = height(Node->left);
	int hr = height(Node->right);
	Node->height = (hl > hr ? hl : hr) + 1;
	Node->count = getCount(Node->left) + getCount(Node->right) + 1;
}

int Ginger::getCount(CNode* Node)
{
	return Node == NULL ? 0 : Node->count;
}

CNode* Ginger::rotateRight(CNode* p) // правый поворот вокруг p
{
	CNode* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

CNode* Ginger::rotateLeft(CNode* q) // левый поворот вокруг q
{
	CNode* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

CNode* Ginger::balance(CNode* Node) // балансировка узла p
{
	fixheight(Node);
	if (bfactor(Node) == 2)
	{
		if (bfactor(Node->right) < 0)
			Node->right = rotateRight(Node->right);
		return rotateLeft(Node);
	}
	if (bfactor(Node) == -2)
	{
		if (bfactor(Node->left) > 0)
			Node->left = rotateLeft(Node->left);
		return rotateRight(Node);
	}
	return Node;
}



///  Вывод

void Ginger::printAsTree(CNode* Node, int currentLevel)
{
	if (Node == 0) {
		return;
	}
	printAsTree(Node->right, currentLevel + 1);
	cout << string(currentLevel, '\t') << Node->data << " " << Node->count << endl;
	printAsTree(Node->left, currentLevel + 1);
}

void Ginger::show() 
{
	printAsTree(RootOfGinger, 0);
}

///



int main()
{
	int n, instruction, key;
	Ginger tree;
	ifstream inp("input.txt");
	inp >> n;
	for (int i = 0; i < n; ++i)
	{
		inp >> instruction >> key;
		if (instruction == 1)
			cout << tree.Insert(key) << endl;
		if (instruction == 2)
			tree.Delete(key);
	}
	return 0;
}