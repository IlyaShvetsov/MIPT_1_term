#include <iostream>
#include <fstream>
#include <time.h>
#include <string.h>
using namespace std;

void Merge(long long *a, int aLen, long long *b, int bLen, long long *c)
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

void MergeSort(long long *a, int aLen)
{
	if (aLen <= 1)
		return;
	int Len1 = aLen / 2;
	int Len2 = aLen - Len1;
	MergeSort(a, Len1);
	MergeSort(a + Len1, Len2);
	long long *c = new long long[aLen];
	Merge(a, Len1, a + Len1, Len2, c);
	memcpy(a, c, sizeof(long long)*aLen);
	delete[]c;
}



int main()
{
	time_t begin = clock();  ///


	int n;
	ios_base::sync_with_stdio(false);
	ifstream inp("C:\\Users\\Илья\\Documents\\Visual Studio 2015\\Projects\\Task 2\\files\\input.txt");
	ofstream out("C:\\Users\\Илья\\Documents\\Visual Studio 2015\\Projects\\Task 2\\files\\output.txt");
	inp >> n;
	long long *arr = new long long[n];
	for (int i = 0; i < n; ++i)   
		inp >> arr[i];

	MergeSort(arr, n);			  	

	for (int i = 0; i < n; ++i)
		out << arr[i] << " ";

	delete[]arr;


	time_t end = clock();
	cout << double(end - begin) / CLOCKS_PER_SEC << endl; ///

	return 0;
}