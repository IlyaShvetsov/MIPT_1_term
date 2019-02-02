// 4_1.Первые k элементов длинной последовательности.
// Дана очень длинная последовательность целых чисел длины n.
// Требуется вывести в отсортированном виде её первые k элементов.
// Последовательность может не помещаться в память.
// Время работы O(n * log(k)).Доп.память O(k).
// Использовать слияние.

#include <iostream>
#include <fstream>
#include <time.h>
#include <string.h>
using namespace std;

void Merge(int *a, int aLen, int *b, int bLen, int *c)
{
	int i = 0, j = 0;
	while (i < aLen && j < bLen)
	{
		if (a[i] < b[j])
		{
			c[i + j] = a[i];
			++i;
		}
		else
		{
			c[i + j] = b[j];
			++j;
		}
	}

	if (i == aLen)
		for (; j < bLen; ++j)
			c[i + j] = b[j];
	else
		for (; i < aLen; ++i)
			c[i + j] = a[i];
}

void KMerge(int *a, int aLen, int *b, int bLen, int *c)
{
	int i = 0, j = 0;
	while (i < aLen && j < bLen && i + j < aLen)
	{
		if (a[i] < b[j])
		{
			c[i + j] = a[i];
			++i;
		}
		else
		{
			c[i + j] = b[j];
			++j;
		}
	}

	if (i == aLen)
		for (; j < bLen&&i + j < aLen; ++j)
			c[i + j] = b[j];
	else
		for (; i < aLen&&i + j < aLen; ++i)
			c[i + j] = a[i];
}

void MergeSort(int *a, int aLen)
{
	if (aLen <= 1)
		return;
	int Len1 = aLen / 2;
	int Len2 = aLen - Len1;
	MergeSort(a, Len1);
	MergeSort(a + Len1, Len2);
	int *c = new int[aLen];
	Merge(a, Len1, a + Len1, Len2, c);
	memcpy(a, c, sizeof(int)*aLen);
	delete[]c;
}



int main()
{
	time_t begin = clock();  ///


	int n, k;
	ios_base::sync_with_stdio(false);
	ifstream inp("C:\\Users\\Илья\\Documents\\Visual Studio 2015\\Projects\\Task 2\\files\\input.txt");
	ofstream out("C:\\Users\\Илья\\Documents\\Visual Studio 2015\\Projects\\Task 2\\files\\output.txt");
	inp >> n >> k;
	int *a = new int[k];
	for (int i = 0; i < k; ++i)   // считываем первые k элементов
		inp >> a[i];
	MergeSort(a, k);			  // сортируем их
	int i, elem, j;
	int *b = new int[k];
	int *c = new int[k];
	for (i = k; i < n; )
	{
		j = 0;
		for (; (i < n) && (j < k); ++i)
		{
			inp >> elem;          // считываем остальные элементы последовательности
			if (elem < a[k - 1])  // проверяем, может ли этот элемент входить в первые k
			{
				b[j] = elem;      // если да, записываем его в новый массив
				j++;
			}
		}
		MergeSort(b, j);		  // сортируем новый массив
		KMerge(a, k, b, j, c);    // сливаем старый массив с новым (записываем только первые k элементов
		memcpy(a, c, sizeof(int)*k);
	}

	for (int i = 0; i < k; ++i)
		out << a[i] << " ";

	delete[]a;
	delete[]b;
	delete[]c;


	time_t end = clock();
	cout << double(end - begin) / CLOCKS_PER_SEC << endl; ///

	return 0;
}