#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;



int main()
{
	srand(time(NULL));
	ios_base::sync_with_stdio(false);
	ofstream out("C:\\Users\\Илья\\Documents\\Visual Studio 2015\\Projects\\Task 2\\files\\input.txt");
	long long a;
	const long long n = 5000;
	const long long size = 1000000;
	out << n << endl;
	for (long long i = 0; i < n; ++i) {
		a = (rand()*(size - 1)) * (rand() % 10000) % size;
		out << a << endl;
	}

	return 0;
}