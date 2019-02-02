// 1_2. Ломаная 1
// Задано NN точек на плоскости. Указать (N−1)(N−1)-звенную несамопересекающуюся 
// незамкнутую ломаную, проходящую через все эти точки.
// Указание: стройте ломаную в порядке возрастания x-координаты.
// Если имеются две точки с одинаковой x-координатой, то расположите 
// ту точку, у которой y-координата меньше. 

#include <iostream>
#include <fstream>
using namespace std;

void InsertionSort(int *x, int *y, int n)
{
	for (int i = 1; i < n; ++i)
	{
		int k = 0;
		int A = x[i];
		int B = y[i];
		for (; (k < i) && (A > x[k]); ++k);
		for (int j = i - 1; j >= k; --j)
		{
			x[j + 1] = x[j];
			y[j + 1] = y[j];
		}
		x[k] = A;
		y[k] = B;
	}

}

void YSort(int *x, int *y, int n)
{
	for (int i = 0; i < n; ++i)
	{
		int j = i;
		int s = 1;
		for (; x[i] == x[i + 1]; ++i) // ищем все точки с равными X координатами
			s++;
		int *a = new int[s];
		int *b = new int[s];
		for (int k = 0; k < s; ++k) // копируем их в новые массивы
		{
			a[k] = x[j + k];
			b[k] = y[j + k];
		}

		InsertionSort(b, a, s); // сортируем эти точки по Y координате

		for (int k = 0; k < s; ++k) // возвращаем точки обратно 
		{
			x[j + k] = a[k];
			y[j + k] = b[k];
			cout << x[j + k] << " " << y[j + k] << "\n";
		}

		delete[] a;
		delete[] b;
	}
}



int main()
{
	int n;
	ifstream inp("input.txt");
	inp >> n;
	int *x = new int[n];
	int *y = new int[n];
	for (int i = 0; i < n; ++i)
		inp >> x[i] >> y[i];

	InsertionSort(x, y, n); // сортируем по X координате
	YSort(x, y, n); // сортируем по Y координате

	delete[] x;
	delete[] y;

	return 0;
}