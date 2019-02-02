// 3_1.Реализуйте стратегию выбора опорного элемента “медиана трёх”.
// Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;

int Partition(int *array, int beg, int size)
{
	int pivot;
	int x1 = beg + rand() % (size-beg);
	int x2 = beg + rand() % (size-beg);
	int x3 = beg + rand() % (size-beg);

	if (((array[x3] <= array[x1]) && (array[x1] <= array[x2]))
		|| ((array[x3] >= array[x1]) && (array[x1] >= array[x2])))
	{
		pivot = array[x1];
		swap(array[x1], array[size - 1]);
	}
	if (((array[x1] <= array[x2]) && (array[x2] <= array[x3]))
		|| ((array[x1] >= array[x2]) && (array[x2] >= array[x3])))
	{
		pivot = array[x2];
		swap(array[x2], array[size - 1]);
	}
	else
	{
		pivot = array[x3];
		swap(array[x3], array[size - 1]);
	}

	int i = beg;
	int j = i;
	while (j < size - 1) {
		for (; array[j] > pivot; ++j);
		if (j != size - 1)
			swap(array[i++], array[j++]);
	}
	swap(array[i], array[size - 1]);
	
	return i;
}



int main()
{
	time_t begin = clock();  ///


	srand(time(NULL));
	ios_base::sync_with_stdio(false);
	ifstream inp("input.txt");
	int n, k;
	inp >> n >> k;
	int *array = new int[n];
	for (int i = 0; i < n; ++i) {
		inp >> array[i];
	}

	int beg = 0;
	int size = n;
	int pivot = Partition(array, beg, size);
	while (pivot != k) {
		if (pivot < k) {
			beg = pivot + 1;
		}
		else {
			size = pivot;
		}
		pivot = Partition(array, beg, size);
	}
	cout << array[pivot];

	delete[]array;


	time_t end = clock();
	cout << endl << double(end - begin) / CLOCKS_PER_SEC << endl; ///

	return 0;
}