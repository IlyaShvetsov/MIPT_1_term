// 1.1. ��� - �������
// ���������� ��������� ������ ���� ���������� ����� �� ������ ������������ ��� - ������� � �������� ����������.
// �������� ������ �������� � ������� �� �������� ��������� ����. ��� - ������� ������ ������ ���� ����������� � ������� 
// ���������� �������� ���������� ������� �������. ��������� ������ ������� ������ ���� ������ 8 - ��. ���������������
// ���������� ��� ���������� ��������� � ������, ����� ����������� ���������� ������� ��������� 3 / 4. ��������� ������ 
// ������ ������������ �������� ���������� ������ � ���������, �������� ������ �� ��������� � �������� ��������������
// ������ ������ ���������. ��� ���������� �������� ����������� ������������ ������������. i - �� ����� g(k, i) = g(k, i - 1) + i(mod m).
// m - ������� ������.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define INITIAL_TABLE_SIZE 8

ofstream out("output.txt");

class HashTable
{
private:
	struct CNode
	{
		string key;
		bool deleted;     // 1 - ������ ���� �������
						  // 0 - � ��������� ������
		CNode() : key(""), deleted(0) {}
	};
	CNode* table;
	size_t table_size;
	size_t real_size;
	int alpha;

	size_t hash(string key);
	void reHash();
	short has(size_t h, string key);
	void ADD(string key);

public:
	HashTable();
	~HashTable();

	void add(string key);
	void remove(string key);
	void has(string key);
};

HashTable::HashTable()
{
	table_size = INITIAL_TABLE_SIZE;
	real_size = 0;
	alpha = 3;
	table = new CNode[table_size];
}

HashTable::~HashTable()
{
	delete[] table;
}

void HashTable::add(string key)
{
	if (real_size == table_size / 4 * 3)     // ���� ������� ����������� - ������������
		reHash();
	size_t j = hash(key);
	size_t mem = 0;
	for (int i = 0; i < table_size; ++i)
	{
		j = (j + i) % table_size;
		switch (has(j, key))
		{
		case 1:								 // ����� ������ ������
		{
			if (!mem)						 // ���� ���� ��������� ������, ����� � ���
			{
				table[j].key = key;
				table[j].deleted = false;
			}
			else							 // ����� ����� � ��������� ������
			{
				table[mem].key = key;
				table[mem].deleted = false;
			}
			real_size++;
			out << "OK" << endl;
			return;
		}
		case 2:                              // ���� ����� ����� ������ � ������� - FAIL
		{
			out << "FAIL" << endl;
			return;
		}
		case 3:							     // ����� ������ ��������� ������ � ��������� ��
		{
			if (!mem)
				mem = j;
		}
		}
	}
	if (mem)								 // ���� �� ����� ������ ������, �� ����� ���������
	{										 // �� ����� � ���
		table[mem].key = key;
		table[mem].deleted = false;
		real_size++;
		out << "OK" << endl;
	}
}

void HashTable::ADD(string key)
{
	size_t j = hash(key);
	for (int i = 0; i < table_size; ++i)
	{
		j = (j + i) % table_size;
		if (has(j, key) == 1)
		{
			table[j].key = key;
			return;
		}
	}
}

void HashTable::remove(string key)
{
	if (!real_size)							 // ���� ������� ����� - FAIL
	{
		out << "FAIL" << endl;
		return;
	}
	size_t j = hash(key);
	for (int i = 0; i < table_size; ++i)
	{
		j = (j + i) % table_size;
		switch (has(j, key))
		{
		case 1:								 // ���� ����� �� ������ ������ - FAIL
		{
			out << "FAIL" << endl;
			return;
		}
		case 2:								 // ����� ������ - �������
		{
			table[j].deleted = true;
			table[j].key = "";
			real_size--;
			out << "OK" << endl;
			return;
		}
		}
	}
	out << "FAIL" << endl;					 // ���� ������ ��� �������, �� �� ����� ������ ������
}

short HashTable::has(size_t h, string key)
{
	if (table[h].key != "" && table[h].key != key)
	{
		return 0;   // ������ ������
	}
	if (table[h].deleted == 0 && table[h].key == "")
	{
		return 1;   // ������ �����
	}
	if (table[h].key == key)
	{
		return 2;   // ������ ���������
	}
	if (table[h].deleted == 1 && table[h].key == "")
	{
		return 3;   // ������ �������
	}
}

void HashTable::has(string key)
{
	if (!real_size)
	{
		out << "FAIL" << endl;
		return;
	}
	size_t j = hash(key);
	for (int i = 0; i < table_size; ++i)
	{
		j = (j + i) % table_size;
		switch (has(j, key))
		{
		case 1:
		{
			out << "FAIL" << endl;
			return;
		}
		case 2:
		{
			out << "OK" << endl;
			return;
		}
		}
	}
	out << "FAIL" << endl;					 // ���� ������ ��� �������, �� �� ����� ������ ������
}

size_t HashTable::hash(string key)
{
	if (key.size() == 1)
		return (key[0] * alpha) % table_size;
	size_t result = (key[0] * alpha + key[1]) % table_size;
	for (int i = 2; i < key.size(); ++i)
		result = (result*alpha + key[i]) % table_size;
	return result;
}

void HashTable::reHash()
{
	table_size *= 2;
	CNode* newTable = table;
	table = new CNode[table_size];
	for (int i = 0; i < table_size / 2; ++i)
	{
		if (newTable[i].key != "")
			ADD(newTable[i].key);
	}
	delete[]newTable;
}





int main()
{
	HashTable container;
	string key;
	char operation;
	ifstream inp("input.txt");
	while (!inp.eof())
	{
		inp >> operation >> key;
		if (operation == '+')
			container.add(key);
		if (operation == '-')
			container.remove(key);
		if (operation == '?')
			container.has(key);
		operation = NULL;
	}

	return 0;
}