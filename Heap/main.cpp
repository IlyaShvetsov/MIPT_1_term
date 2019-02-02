#include <iostream>

using std::cout;
using std::cin;
using std::swap;


void SiftDown(int *arr, int i, int n) {
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

void BuildHeap(int *arr, int n) {
	for (int i = n/2 - 1; i >= 0; i--) 
		SiftDown(arr, i, n);
}

void HeapSort(int *arr, int n) {
	BuildHeap(arr, n);
	int size = n;
	while (size > 1) {
		swap(arr[0], arr[size-1]);
		size--;
		SiftDown(arr, 0, size);
	}

}

int main() {
	const int n = 15;
	int arr[n];
	for (int i = 0; i < n; i++)
		arr[i] = n - i;

	HeapSort(arr, n);

	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";

	return 0;
}