/*Вывести квадраты натуральных чисел от 1 до n, используя только O(n) 
операций сложения и вычитания (умножением пользоваться нельзя). n ≤ 1000.*/ 

#include <iostream>

using std::cout;
using std::cin;

void sqr(int n) {
	int s = 1;
	cout << s << " ";
	for (int i = 0; i < n - 1; i++) {
		s += 3 + i*2;
		cout << s << " ";
	}
}

int main() {
	int n = 0;
	cin >> n;

	sqr(n);
	
	return 0;
}