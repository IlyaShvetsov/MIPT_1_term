#include <iostream>

using std::cout;
using std::cin;

struct Queue {
	int data;
	Queue* next;
	Queue* prev;

	Queue() : data(0), next(0), prev(0) {}

};

Queue* PushBack(Queue* first, Queue* last, int a, bool ok) {
	if (first != 0) {
		Queue* newElem = new Queue();
		newElem->data = a;
		newElem->next = first;
		first->prev = newElem;
		return newElem;
	}
	else {
		Queue* newElem = new Queue();
		newElem->data = a;
		last = newElem;
		return newElem;
	}
}

Queue* PopFront(Queue* last, int x) {
	if (last != 0) {
		x = last->data;
		last->prev->next = 0;
		Queue* f = new Queue();
		f = last->prev;
		delete last;
		return f;
	}
	else {
		Queue* f = new Queue();
		f->prev = f;
		return f;
	}
}


int main() {
	Queue* first = 0;
	Queue* last = 0;
	int n, a, x = 0, s = 0;
	bool ok = false, okey = true;

	/*cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a >> s;
		if (a == 2) {
			first = PushBack(first, s, ok);
			if (ok) {
				last = first;
				ok = false;
			}
		}
		if (a == 3)	{
			last = PopFront(last, x);
			if (last->prev == last) {
				okey = false;
			}
			else
				if (s != x)
					okey = false;
		}
	}

	if (okey)
		cout << "YES";
	else 
		cout << "NO";*/

	PushBack(first, last, 23, ok);
	cout << PopFront(last, x)->data;

	return 0;
}
