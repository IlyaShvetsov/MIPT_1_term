//Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы.
//Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм. 
//За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно,
//откусывает от каждого половину и кладет огрызки обратно в корзину. Если фрукт весит нечетное 
//число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.
//
//Определить за сколько подходов Вовочка съест все фрукты в корзине.
//Формат входных данных. Вначале вводится n - количество фруктов и n строк с массами фруктов.
//n ≤ 50000.
//Затем K - "грузоподъемность". K ≤ 1000.


#include <iostream>
#include <math.h>

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

void SiftUp(int *arr, int i) {
	while (i > 0) {
		int	parent = (i	- 1) / 2;
		if (arr[i] <= arr[parent])
			return;
		swap(arr[i], arr[parent]);
		i = parent;
	}
}

void BuildHeap(int *arr, int n) {
	for (int i = n/2 - 1; i >= 0; i--) 
		SiftDown(arr, i, n);
}

int main() {
	int arr[50000], n, k, s = 0, c = 0, j = 0, b[1000];
	bool ok = false;
	cin >> n; 
	for (int i = 0; i < n; i++)
		cin >> arr[i]; 
	cin >> k;
	BuildHeap(arr, n);

	while (arr[0] != 0) {
		while ((!ok) && (arr[0] != 0)) {
			c += arr[0];
			if (c <= k) {
				b[j] = arr[0] / 2;
				j++;
				arr[0] = 0;
				swap(arr[0], arr[n-j]);
				SiftDown(arr, 0, n);
			}
			else 
				ok = true;
		}
		for (int i = j - 1; i >= 0; i--) {
			arr[n-i-1] = b[i];
			SiftUp(arr, n-i-1);
		}
		ok = false;
		c = 0;
		j = 0;
		s++;
	}
	cout << s;

	return 0;
}