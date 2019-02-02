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
		}

		delete[] a;
		delete[] b;
	}
}

int TangensSort(int *x, int *y, double *tan, int j, int n)
{
	int rez = j;
	for (int i = j; i < n; ++i)
		if (tan[i] >= 0)
		{
			int k = 0;
			int A = x[i];
			int B = y[i];
			double T = tan[i];
			for (; (k < i) && (T > tan[k]); ++k);
			for (int g = i - 1; g >= k; --g)
			{
				x[g + 1] = x[g];
				y[g + 1] = y[g];
				tan[g + 1] = tan[g];
			}
			x[k] = A;
			y[k] = B;
			tan[k] = T;
			rez++;
		}
	return rez;
}

void TangensSortMIN(int *x, int *y, double *tan, int j, int n)
{
	int rez = j;
	for (int i = j; i < n; ++i)
		if (tan[i] < 0)
		{
			int k = 0;
			int A = x[i];
			int B = y[i];
			double T = tan[i];
			for (; (k < i) && (abs(T) > abs(tan[k])); ++k);
			for (int g = i - 1; g >= k; --g)
			{
				x[g + 1] = x[g];
				y[g + 1] = y[g];
				tan[g + 1] = tan[g];
			}
			x[k] = A;
			y[k] = B;
			tan[k] = T;
			rez++;
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

	int j;
	for (j = 0; x[j] == x[0]; ++j)
		cout << x[j] << " " << y[j] << endl;

	double *tan = new double[n];
	for (int i = j; i < n; ++i)
		tan[i] = (double)(x[i] - x[0]) / (y[i] - y[0]);


	int rez = TangensSort(x, y, tan, j, n);
	TangensSortMIN(x, y, tan, rez, n);

	for (int i = j; i < n; ++i)
		cout << x[i] << " " << y[i] << " " << tan[i] << endl;

	delete[] x;
	delete[] y;

	return 0;
}