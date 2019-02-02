// 6. Быстрейшая сортировка.
// Дан массив целых чисел в диапазоне[0..10 ^ 9].Размер массива кратен 10 и ограничен сверху значением 2.5 * 10^6 элементов.
// Все значения массива являются элементами псевдо-рандомной последовательности. Необходимо отсортировать элементы массива 
// за минимальное время и вывести каждый десятый элемент отсортированной последовательности.
// Реализуйте сортировку, основанную на QuickSort.
// Минимальный набор оптимизаций, который необходимо реализовать :
// 1. Оптимизация ввода / вывода
// 2. Оптимизация выбора опорного элемента
// 3. Оптимизация Partition
// 4. Написать без рекурсии
// 5. Оптимизация концевой рекурсии

#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

class stack
{
public:
	int* content;
	int size, bufferSize;

	stack();
	~stack();
	void push(const int c);
	int pop();
	bool isEmpty();
};

stack::stack()
{
	size = 0;
	bufferSize = 10000;
	content = new int[bufferSize];
}

stack::~stack()
{
	delete[]content;
}

void stack::push(const int c)
{
	content[size++] = c;
}

int stack::pop()
{
	if (size > 0)
	{
		size--;
		return content[size];
	}
	return 0;
}

bool stack::isEmpty() {
	if (size == 0)
		return true;
	else
		return false;
}



int Partition(int *arr, int first, int last)
{
	int pivot;
	int x1 = first + rand() % (last - first);
	int x2 = first + rand() % (last - first);
	int x3 = first + rand() % (last - first);

	if (((arr[x3] <= arr[x1]) && (arr[x1] <= arr[x2]))
		|| ((arr[x3] >= arr[x1]) && (arr[x1] >= arr[x2])))
	{
		pivot = arr[x1];
		swap(arr[x1], arr[last]);
	}
	if (((arr[x1] <= arr[x2]) && (arr[x2] <= arr[x3]))
		|| ((arr[x1] >= arr[x2]) && (arr[x2] >= arr[x3])))
	{
		pivot = arr[x2];
		swap(arr[x2], arr[last]);
	}
	else
	{
		pivot = arr[x3];
		swap(arr[x3], arr[last]);
	}

	int i = first;
	int j = i;
	while (j < last) {
		for (; arr[j] > pivot; ++j);
		if (j != last)
			swap(arr[i++], arr[j++]);
	}
	swap(arr[i], arr[last]);

	return i;
}

void QuickSort(int *arr, int n)
{
	int first = 0, last = n - 1;
	stack s;
	s.push(first);
	s.push(last);
	while (!s.isEmpty())
	{
		last = s.pop();
		first = s.pop();
		if (last <= first)
			continue;
		int part = Partition(arr, first, last);
		if (part > 0)
		{
			s.push(first);
			s.push(part - 1);
		}
		if (part - 1 > last - part)
		{
			s.push(first);
			s.push(part - 1);
			s.push(part + 1);
			s.push(last);
		}
		else 
		{
			

			s.push(part + 1);
			s.push(last);
			s.push(first);
			s.push(part - 1);
		}
	}
}


int main()
{


	srand(time(NULL));
	ios_base::sync_with_stdio(false);
	ifstream inp("C:\\Users\\Илья\\Documents\\Visual Studio 2015\\Projects\\Task 2\\files\\input.txt");
	ofstream out("C:\\Users\\Илья\\Documents\\Visual Studio 2015\\Projects\\Task 2\\files\\output.txt");
	int n;
	inp >> n;
	int *arr = new int[n];
	for (int i = 0; i < n;++i)
		inp >> arr[i];


	time_t begin = clock();  ///

	QuickSort(arr, n);


	time_t end = clock();
	cout << double(end - begin) / CLOCKS_PER_SEC << endl; ///

	for (int i = 0; i < n; ++i)
		out << arr[i] << " ";

	delete[]arr;




	return 0;
}