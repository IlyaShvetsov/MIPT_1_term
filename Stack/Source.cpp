#include <iostream>
using namespace std;

class stack {
private:
	struct CNode {
		int content;
		CNode* prev;

		CNode(int value) : content(value), prev(NULL) {}
	};

	CNode* top;
	int size;
	int min;

public:
	stack() : top(NULL), size(0), min(NULL) {}
	~stack() { clear(); }

	void pop();
	void push(int value);
	void getMin();
	void getSize();
	void clear();
	void back();
};

void stack::back() {
	if (size == 0)
		cout << "error" << endl;
	else
		cout << top->content << endl;
}

void stack::push(int value) {
	cout << "ok" << endl;
	if (size == 0) {
		min = value;
		top = new CNode(value);
		size++;
		return;
	}
	if (value < min)
		min = value;
	CNode* tmp = new CNode(value);
	top->prev = top;
	top = tmp;
	size++;
}

void stack::pop() {
	if (size == 0)
		cout << "error" << endl;
	else {
		size--;
		CNode* tmp = new CNode(top->content);
		tmp->prev = top->prev;
		delete top;
		top = tmp->prev;
		cout << tmp->content << endl;
	}
}

void stack::getMin() {
	cout << min << endl;
}

void stack::getSize() {
	cout << size << endl;
}

void stack::clear() {
	if (size == 0)
		return;
	while (top->prev != NULL) {
		CNode* tmp = top;
		delete top;
		top = tmp->prev;
	}
	top = NULL;
	size = 0;
}


int main() {
	stack s;
	int n;
	cin >> n;
	char str[8];
	for (int i = 0; i < n; ++i) {
		cin >> str;
		if (str[3] == 'h') {
			int f;
			cin >> f;
			s.push(f);
		}
		else if (str[2] == 'p') {
			s.pop();
		}
		else if (str[3] == 'k') {
			s.back();
		}
		else if (str[2] == 'n') {
			s.getMin();
		}
		else if (str[3] == 'e') {
			s.getSize();
		}
		else if (str[4] == 'r') {
			s.clear();
		}
	}
	return 0;
}
