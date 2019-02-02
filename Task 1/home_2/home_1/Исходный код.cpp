//2_2. Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин.
//Вначале вводится количество вершин, затем последовательно целочисленные координаты 
//всех вершин в порядке обхода по часовой стрелке.


#include <iostream>

using std::cout;
using std::cin;

double square(int *x, int *y, int n) {
	double s = 0;
	s += (x[n-1] + x[0]) * (y[n-1] - y[0]);
    for (int i = 0; i < n-1; i++) 
			s += (x[i] + x[i+1]) * (y[i] - y[i+1]);
	return s;
}

void print(double s) {
	if (s > 0)
		cout << (s / 2);
	else
		cout << ((-1) * s / 2);
}

int main() {
	int n = 0, x[1000], y[1000];
	cin >> n;
	for (int i = 0; i < n; i++) 
		cin >> x[i] >> y[i];

	print( square(x, y, n) );

	return 0;
}