#include <iostream>
#include "hash-container.h"
using namespace std;

int main() {
	HashContainer container;
	container.add(22, 2);
	container.add(77, 7);
	container.add(55, 5);

	if (container.has(37)) {
		cout << "has key" << endl;
	} else {
		cout << "hasn't key" << endl;
	}

	return 0;
}
