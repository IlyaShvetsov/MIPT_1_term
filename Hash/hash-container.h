#pragma once

class HashContainer {

private:
	struct Pair {
		int key;
		int value;

		Pair(int key, int value) : 
			key(key), 
			value(value) {}
	};

	struct ListNode {
		Pair data;
		ListNode* next;

		ListNode(int key, int value) : 
			data(key, value), 
			next(nullptr) {}
	};
	ListNode** table;
	size_t table_size;

	size_t hash(int key);
	bool has(size_t h, int key);

public:
	HashContainer();
	~HashContainer();

	bool add(int key, int value);
	bool remove(int key);
	bool has(int key);
};
