//Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. 
//Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, 
//равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. 
//Время работы поиска k для каждого элемента B[i]: O(log(k)). n, m ≤ 10000. 


#include <iostream>

using std::cin;
using std::cout;

void nextElement(int *a, int *b, int n, int m) {
	int min, max, cur;
	for (int i = 0; i < m; i++) {
		if (b[i] > a[n-1]) 
			cout << n << " ";
		else {
			min = 0;
			max = n - 1;
			while (min < max) {
				cur = (min + max) / 2;
				if (b[i] <= a[cur])
					max = cur;
				else
					min = cur + 1;
			}
			cout << min << " ";
		}
	}
}

void proga(int *a, int *b, int &j, int n) {
	for (int i = 0; i < n; i++) 
		if (a[i] % 2 == 0) {
			b[j] = a[i];
			j++;
		}
}

int main() {
	int n, i, j = 0, m;// a[10000], b[10000];
	int *a=new int[10000];
	int *b=new int[10000];
	cin >> n;  // >> m;
	for (i = 0; i < n; i++) 
		cin >> a[i];
	/*for (i = 0; i < m; i++) 
		cin >> b[i];	

	nextElement(a, b, n, m);*/

	proga(a, b, j, n);
	for (int i = 0; i < j; i++)
		cout << b[i] << " ";

	return 0;
}