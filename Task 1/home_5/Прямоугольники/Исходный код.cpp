//Дана последовательность N прямоугольников различной ширины и высоты (wi, hi). 
//Прямоугольники расположены, начиная с точки (0, 0), на оси ОХ вплотную друг за другом (вправо).
//Требуется найти M - площадь максимального прямоугольника (параллельного осям координат),
//который можно вырезать из этой фигуры.
//
//Время работы - O(n).


#include <iostream>
#include <fstream>
using namespace std;

int main() 
{
	int n;
	ifstream inp( "input.txt" );
	inp >> n;
	int *width = new int[n];
	int *height = new int[n];
	for (int i = 0; i < n; ++i)
		inp >> width[i] >> height[i];

	int max = 0, s;
	for (int i = 0; i < n; ++i)
	{
		s = 0;
		int j = i;
		while ((j >= 0) && (height[j] >= height[i]))
		{
			s += height[i] * width[j];
			j--;
		}
		j = i + 1;
		while ((j < n) && (height[j] >= height[i])) 
		{
			s += height[i] * width[j];
			j++;
		}
		if (s > max) 
			max = s;
	}

	cout << max;
	return 0;
}