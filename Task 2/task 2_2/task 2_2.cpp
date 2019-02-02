// 2_2.������������.
// ������ ����� ���������� �������������� ���� ��� ����� ������, ����� ��� ����� ��������� ������.
// ��� ����� � ���� ������ ������� �� ��� ������ ����  ��� ����������� 18 ���, �� ��� �� ����������� 80 ���.
// ��� ������ ����� ������� �����. ���������� �������� ������������ ���������� �������������.
// � ���� 18����� ������� ��� ����� ��������� ������� � ���������, � � ���� 80����� � � ���� ������ ��� �� �����.
// ���������! ������� ��� �� ������ �� 18 - �����, ���� ������� � ���� 18 - �����. � ���� ������� ��������� ������� � ��������� �� �� ���.

#include <iostream>
#include <fstream>
using namespace std;
ifstream inp("input.txt");

class date
{
public:
	int content;
	bool ok;

	date() { content = 0; ok = true; }
};




void SiftDown(date *arr, int i, int n)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int largest = i;
	if (left < n)
		if (arr[left].content > arr[largest].content)
			largest = left;
	if (right < n)
		if (arr[right].content > arr[largest].content)
			largest = right;
	if (largest != i)
	{
		swap(arr[largest], arr[i]);
		SiftDown(arr, largest, n);
	}
}

void BuildHeap(date *arr, int n)
{
	for (int i = n / 2 - 1; i >= 0; --i)
		SiftDown(arr, i, n);
}

void HeapSort(date *arr, int n)
{
	BuildHeap(arr, n);
	int size = n;
	while (size > 1)
	{
		swap(arr[0], arr[size - 1]);
		size--;
		SiftDown(arr, 0, size);
	}
}





void MES(int x, int &mes)
{
	if (x > 1)
		mes += 31;
	if (x > 2)
		mes += 28;
	if (x > 3)
		mes += 31;
	if (x > 4)
		mes += 30;
	if (x > 5)
		mes += 31;
	if (x > 6)
		mes += 30;
	if (x > 7)
		mes += 31;
	if (x > 8)
		mes += 31;
	if (x > 9)
		mes += 30;
	if (x > 10)
		mes += 31;
	if (x > 11)
		mes += 30;
}

void schet(date *arr, int n)
{
	int day, month, year, day1, month1, year1, mes = 0;
	for (int i = 0; i < n; ++i)
	{
		inp >> day >> month >> year;
		inp >> day1 >> month1 >> year1;
		if ((year1 - year > 18) || (year1 - year == 18) && ((month1 > month) || (month1 == month) && (day1 > day)))
		{
			mes = 0;
			MES(month, mes);
			if (year % 4 == 0)
				mes++;
			arr[2 * i].content = (year + 18) * 365 + (year + 18) / 4 + day + mes;
			arr[2 * i].ok = true;
			if ((year1 - year > 80) || (year1 - year == 80) && ((month1 > month) || (month1 == month) && (day1 > day)))
				arr[2 * i + 1].content = (year + 80) * 365 + (year + 80) / 4 + day + mes - 1;
			else
			{
				mes = 0;
				MES(month1, mes);
				arr[2 * i + 1].content = year1 * 365 + year1 / 4 + day1 + mes - 1;
			}
			arr[2 * i + 1].ok = false;
		}
		else
		{
			arr[2 * i].content = 0;
			arr[2 * i + 1].content = 0;
		}
	}
}



int main()
{
	int n;
	date *arr;
	inp >> n;
	arr = new date[2 * n];

	schet(arr, n);
	HeapSort(arr, 2 * n);

	int s = 0, max = 0;
	for (int i = 0; i < 2 * n; ++i)
		if (arr[i].content != 0)
		{
			if (arr[i].ok)
			{
				s++;
				if (s > max)
					max = s;
			}
			else
				s--;
		}

	cout << max;

	delete[]arr;

	return 0;
}