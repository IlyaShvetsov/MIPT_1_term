// 3.1. ������� ��������
// ���� N �������. ��������� ����������, ����� ����������� �������� ����� ��������� �� ���� ������� ��������.
// ������ ����������� ���� �������� ������ ���� �� ������ ������������.

// �����, �������� �����������!!! !!!!!!!! !!!!!!!!!

#include <iostream>
using namespace std;



long long Pyramid(int n)
{
	long long **arr = new long long*[n + 1];
	for (int i = 1; i <= n; ++i)
		arr[i] = new long long[n + 1];
	for (int i = 1; i <= n; ++i)
		for (int j = 2; j <= n; ++j)
			arr[i][j] = 0;
	for (int i = 1; i <= n; ++i)
	{
		arr[i][1] = 1;
		arr[i][i] = 1;
	}
	for (int i = 3; i <= n; ++i)
		for (int j = 2; j < i; ++j)		
			for (int k = 1; k <= j; ++k)
				arr[i][j] += arr[i - j][k];

	long long s = 0;
	for (int i = 1; i <= n; ++i)
		s += arr[n][i];

	for (int i = 1; i <= n; ++i)        ///  ����� �� �����
	{
		for (int j = 1; j <= n; ++j)
			cout << arr[i][j] << " ";
		cout << endl;
	}									///

	for (int i = 1; i <= n; ++i)
		delete[]arr[i];
	return s;
}





int main()
{
	int n;
	cin >> n;
	cout << Pyramid(n) << endl;;
	return 0;
}