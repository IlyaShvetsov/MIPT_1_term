#include "hash-container.h"
#include <iostream>

#define INITIAL_TABLE_SIZE 128
using namespace std;



HashContainer::HashContainer() {
	table = new ListNode*[INITIAL_TABLE_SIZE];
	table_size = INITIAL_TABLE_SIZE;
	for (int i = 0; i < table_size; ++i) {
		table[i] = nullptr;
	}
}

HashContainer::~HashContainer() {
	for (int i = 0; i < table_size; ++i) {
		ListNode* current = table[i];
		while (current != nullptr) {
			ListNode* to_del = current;
			current = current->next;
			delete to_del;
		}
	}
	delete[] table;
}

bool HashContainer::add(int key, int value) {
	int h = hash(key);
	if (has(h, key)) {
		return false;
	}
	if (table[h] != nullptr) {
		cout << "h: " << h << " collision " << endl;
	}
	ListNode* new_node_ptr = new ListNode(key, value);
	new_node_ptr->next = table[h];
	table[h] = new_node_ptr;
	return true;
}

bool HashContainer::remove(int key) {
	int h = hash(key);
	ListNode* parent = table[h];
	if (parent != nullptr) {
		if (parent->data.key == key) {
			table[h] = parent->next;
			delete parent;
			return true;
		}
		ListNode* current = table[h];
		while (current != nullptr) {
			if (current->data.key == key) {
				parent->next = current->next;
				delete current;
				return true;
			}
			parent = current;
			current = parent->next;
		}
	}
	return false;
}

bool HashContainer::has(size_t h, int key) {
	ListNode* current = table[h];
	while (current != nullptr) {
		if (current->data.key == key) {
			return true;
		}
		current = current->next;
	}
	return false;
}

bool HashContainer::has(int key) {
	return has(hash(key), key);
}

size_t HashContainer::hash(int key) {
	const double alpha = 2.718281828459045;
	double t = (key*alpha);
	int result = static_cast<int>(t) % table_size;
	return result;
}
