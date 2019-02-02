#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

void CountingSort(long long *arr, int n)
{
	int *b = new int[1000000];
	for (int i = 0; i < 1000000; ++i)
		b[i] = 0;
	for (int i = 0; i < n; ++i)
		++b[arr[i]];
	int pos = 0;
	for (int i = 0;pos < n;++i)
		for (int j = 0; j < b[i]; ++j)
		{
			arr[pos] = i;
			++pos;
		}
	 
	delete[]b;

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

	CountingSort(arr, n);

	for (int i = 0; i < n; ++i)
		out << arr[i] << " ";

	delete[]arr;


	time_t end = clock();
	cout << double(end - begin) / CLOCKS_PER_SEC << endl; ///

	return 0;
}