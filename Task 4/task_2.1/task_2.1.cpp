// «адача 2. ∆адность(3 балла)
// 2_1.јтлеты.
// ¬ город N приехал цирк с командой атлетов. ќни хот€т удивить горожан города N Ч выстроить из своих тел башню максимальной высоты.
// Ѕашн€ Ч это цепочка атлетов, первый стоит на земле, второй стоит у него на плечах, третий стоит на плечах у второго и т.д.
//  аждый атлет характеризуетс€ силой s(kg) и массой m(kg).—ила Ч это максимальна€ масса, которую атлет способен держать у себ€ на плечах.
//   сожалению ни один из атлетов не умеет программировать, так как всю жизнь они занимались физической подготовкой,и у них не было времени 
// на изучение €зыков программировани€. ѕомогите им, напишите программу, котора€ определит максимальную высоту башни, которую они могут составить.
// »звестно, что если атлет т€желее, то он и сильнее :
// если mi>mj, то si > sj.
// јтлеты равной массы могут иметь различную силу.


#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

#define SIZE 128



class Athletes
{
private:
	struct athlete
	{
		int weight;
		int power;

		athlete(int weight, int power) : weight(weight), power(power) {}
	};

	athlete** data;
	int realSize;
	int maxSize;

	void grow();
	void MergeSort(athlete**a, int aLen);
	void Merge(athlete** a, int aLen, athlete** b, int bLen, athlete** c);

public:
	Athletes() : realSize(0), maxSize(SIZE)
	{
		data = new athlete*[maxSize];
	}
	~Athletes()
	{
		delete[]data;
	}
	void sort();
	void add(int weight, int power);
	int getSize()
	{
		return realSize;
	}
	athlete* getAthlete(int i)
	{
		return data[i];
	}
};

void Athletes::grow()
{
	maxSize *= 2;
	athlete** newData = new athlete*[maxSize];
	for (int i = 0; i < maxSize / 2; ++i)
		newData[i] = data[i];
	delete[] data;
	data = newData;
}

void Athletes::add(int weight, int power)
{
	if (realSize == maxSize)
		grow();
	athlete* one = new athlete(weight, power);
	data[realSize] = one;
	realSize++;
}

void Athletes::sort()
{
	MergeSort(data, realSize);
	
	for (int i = 0; i < realSize - 1; ++i)
	{
		int j = i, s = 1;
		for (; (i < realSize - 1) && (data[i]->weight == data[i + 1]->weight); ++i)
			s++;

		for (int x = j; x < j + s; ++x)
			for (int y = j; y < j + s - 1; ++y)
				if (data[y]->power > data[y + 1]->power)
					swap(data[y], data[y + 1]);
	}
}

void Athletes::Merge(athlete** a, int aLen, athlete** b, int bLen, athlete** c)
{
	int i = 0, j = 0;
	while (i < aLen && j < bLen)
	{
		if (a[i]->weight < b[j]->weight)
		{
			c[i + j] = a[i];
			++i;
		}
		else
		{
			c[i + j] = b[j];
			++j;
		}
	}

	if (i == aLen)
		for (; j < bLen; ++j)
			c[i + j] = b[j];
	else
		for (; i < aLen; ++i)
			c[i + j] = a[i];
}

void Athletes::MergeSort(athlete**a, int aLen)
{
	if (aLen <= 1)
		return;
	int Len1 = aLen / 2;
	int Len2 = aLen - Len1;
	MergeSort(a, Len1);
	MergeSort(a + Len1, Len2);
	athlete* *c = new athlete*[aLen];
	Merge(a, Len1, a + Len1, Len2, c);
	memcpy(a, c, sizeof(athlete*)*aLen);
	delete[]c;
}



int main()
{
	Athletes athletes;
	int weight, power;
	ifstream inp("input.txt");
	while (!inp.eof())
	{
		inp >> weight >> power;
		athletes.add(weight, power);
	}
	athletes.sort();

	int count = 0, sum = 0;
	for (int i = 0; i < athletes.getSize(); ++i)
	{
		if (athletes.getAthlete(i)->power >= sum)
		{
			count++;
			sum += athletes.getAthlete(i)->weight;
		}

	}

	cout << count << endl;

	return 0;
}