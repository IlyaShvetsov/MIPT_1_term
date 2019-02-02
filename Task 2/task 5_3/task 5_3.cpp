// 5_3.Binary MSD ��� long long.
// ��� ������ ��������������� ����� 64 - ��������� �����.���������� ����� �� ������ 10^6. 
// ������������� ������ ������� MSD �� ����� (�������� QuickSort).

#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

void Binary_QuickSort(long long *arr, int n, long long count)
{
	int i = 0, j = n - 1;
	while (i < j)
	{
		for (; (i != j) && ((arr[i] & count) == 0); ++i);
		for (; (i != j) && ((arr[j] & count) == count); --j);
		swap(arr[i], arr[j]);
	}

	int pivot;
	if ((arr[i] & count) == 0)
		pivot = i + 1;
	else
		pivot = i;
	if (count > 1)
	{
		if (pivot > 0)
			Binary_QuickSort(arr, pivot, count >> 1);
		if (n > pivot)
			Binary_QuickSort(arr + pivot, n - pivot, count >> 1);
	}
}

void B_Q_Sort(long long *arr, int n)
{
	long long max = arr[0];
	for (int i = 1; i < n; ++i)
		if (arr[i] > max)
			max = arr[i];                 // ���� ������������ �������
	long long count = 1;
	for (; max > 1; count <<= 1)	      // ������� ���������� ��� � ��
		max >>= 1;
	Binary_QuickSort(arr, n, count);	  // ��������� ���������� 
}

int main()
{
	time_t begin = clock();  ///


	int n;
	ios_base::sync_with_stdio(false);
	ifstream inp("C:\\Users\\����\\Documents\\Visual Studio 2015\\Projects\\Task 2\\files\\input.txt");
	ofstream out("C:\\Users\\����\\Documents\\Visual Studio 2015\\Projects\\Task 2\\files\\output.txt");
	inp >> n;
	long long *arr = new long long[n];

	for (int i = 0; i < n;++i)
		inp >> arr[i];

	B_Q_Sort(arr, n);

	for (int i = 0; i < n; ++i)
		out << arr[i] << " ";

	delete[]arr;


	time_t end = clock();
	cout << double(end - begin) / CLOCKS_PER_SEC << endl; ///

	return 0;
}