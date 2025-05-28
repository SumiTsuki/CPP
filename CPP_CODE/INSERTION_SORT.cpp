#include<iostream>
#include<vector>
using namespace std;
void INSERTION_SORT(vector<int>& v)
{
	for (int j = 1; j < v.size(); j++)
	{
		int key = v[j];
		int i = j - 1;
		while (i >= 0 && v[i] > key)
		{
			v[i + 1] = v[i];
			--i;
		}
		v[i + 1] = key;
	}
}
int main()
{
	vector<int> v = { 5,2,4,6,1,3,9,10,7,8 };
	INSERTION_SORT(v);
	for (auto e : v)
		cout << e << " ";
	return 0;
}