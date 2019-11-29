#include <iostream>
#include <fstream>
using namespace std;

class Deque {
public:
	int *buffer;
	int bufferSize;
	int size;
	int first;

	Deque();
	~Deque();

	void push_back(int a);
	void push_front(int a);

	int pop_back();
	int pop_front();

	void grow();
};

Deque::Deque() {
	size = 0;
	first = -1;
	bufferSize = 2000;
	buffer = new int[bufferSize]; 
}

Deque::~Deque() {
	delete[] buffer;
}

void Deque::push_front(int a) {
	if (size + first + 1 > bufferSize)
		grow();
	if (first != -1) {
		buffer[size + first] = a;
	} else {
		first = 0;
		buffer[first] = a;
	}
	size++;
}

int Deque::pop_front() {
	if (size != 0) {
		size--;
		int x = buffer[size + first];
		return x;
	} else {
		return -1;	
	}
}

void Deque::push_back(int a) {
	if (first == -1) {
		first = 0;
		buffer[first] = a;
	} else {
		if (first == 0) {
			if (size + first + 1000 > bufferSize)
				grow();
			for (int i = 0; i < size; ++i)
				buffer[i + 1000] = buffer[i];
			first += 1000;
		}
		first--;
		buffer[first] = a;
	}
	size++;
}

int Deque::pop_back() {
	if (size != 0) {
		int x = buffer[first];
		first++;
		size--;
		if (first == 2000) {
			for (int i = 0; i < size; ++i)
				buffer[i + 1000] = buffer[i + 2000];
			first -= 1000;
		}
		return x;
	} else {
		return -1;		
	}
}

void Deque::grow() {
	bufferSize *= 2;
	int *newBuffer = new int[bufferSize];
	for (int i = first; i < size + first; ++i) 
		newBuffer[i] = buffer[i];
	delete[] buffer;
	buffer = newBuffer;
}

int main() {
	Deque D;  
	long int n, a, b;
	bool ok = true;
	ifstream inp( "input.txt" );
	inp >> n;
	for (int i = 0; i < n; i++) {
		inp >> a >> b;
		if (a == 1)
			D.push_front(b);
		if (a == 2) 
			if (b != D.pop_front()) 
				ok = false;
		if (a == 3)
			D.push_back(b);
		if (a == 4)
			if (b != D.pop_back())
				ok = false;
	}

	if (ok)
		cout << "YES";
	else
		cout << "NO";


	return 0;
}
