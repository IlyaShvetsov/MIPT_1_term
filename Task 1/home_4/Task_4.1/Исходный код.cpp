#include <iostream>
#include <cstdio>
#include <fstream>
using namespace std;

using std::cout;
using std::cin;

// ���������, �������� ��������� ������ ������
#define INITIAL_CAPACITY 4


class Queue {
public:
	long int size;               // ������� ������ �������
	long int capacity;           // ����������� ������
	long int *data;              // ��������� �� �����, ��� �������� ��������
	long int first;				 // ������ ������� ��������

	void grow();        

public:
	Queue();                  
	~Queue();                 

	void push_back(long int val);     
	long int pop_front();			  

};

Queue::Queue() : size(0),	capacity(INITIAL_CAPACITY),   first(-1)
{
	data = new long int[capacity];
}

Queue::~Queue()
{
	delete[] data;
}

void Queue::grow()
{
	long int new_capacity = capacity * 2;                // ��������� ������ ������ ������
	long int *new_buffer = new long int[new_capacity];   // �������� ����� �����
	for (long int i = 0; i < size + first; ++i)                  // �������� ������ � ����� �����
		new_buffer[i] = data[i];
	delete[] data;                             // ������� ������ �����
	data = new_buffer;                         // �������� ��������� �� ����� �����
	capacity = new_capacity;                   // ��������� �����������
}

void Queue::push_back(long int val)
{
	if (size == 0)
		first = 0;
	if (size + first + 1 > capacity)
		grow();
	data[size+first] = val;
	size++;
}

long Queue::pop_front()
{
	if (size == 0)
		return -1;
	else
	{
		long int x = data[first];
		size--;
		first++;
		if (first == 1000)
		{
			first -= 1000;
			for (long int i = 0; i < size; i++) 
				data[i] = data[i + 1000];
		}
		return x;
	}
}


int main()
{
	Queue q;  
	long int n, a, b;
	bool ok = true;
	ifstream inp( "input.txt" );
	inp >> n;
	for (int i = 0; i < n; i++) 
	{
		inp >> a >> b;
		if (a == 2)
			if (b != q.pop_front())
				ok = false;
		if (a == 3)
			q.push_back(b);
	}

	if (ok)
		cout << "YES";
	else
		cout << "NO";

	return 0;
}

