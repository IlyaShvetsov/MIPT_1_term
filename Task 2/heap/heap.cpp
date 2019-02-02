#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

void SiftDown(long long *arr, int i, int n) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int largest = i;
	if (left < n)
		if (arr[left] > arr[largest])
			largest = left;
	if (right < n)
		if (arr[right] > arr[largest])
			largest = right;
	if (largest != i) {
		swap(arr[largest], arr[i]);
		SiftDown(arr, largest, n);
	}
}

void BuildHeap(long long *arr, int n) {
	for (int i = n / 2 - 1; i >= 0; i--)
		SiftDown(arr, i, n);
}

void HeapSort(long long *arr, int n) {
	BuildHeap(arr, n);
	int size = n;
	while (size > 1) {
		swap(arr[0], arr[size - 1]);
		size--;
		SiftDown(arr, 0, size);
	}

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

	for (int i = 0; i < n;++i)
		inp >> arr[i];

	HeapSort(arr, n);

	for (int i = 0; i < n; ++i)
		out << arr[i] << " ";

	delete[]arr;


	time_t end = clock();
	cout << double(end - begin) / CLOCKS_PER_SEC << endl; ///

	return 0;
}