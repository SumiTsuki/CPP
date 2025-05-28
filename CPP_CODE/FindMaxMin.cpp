#include<iostream>
#include<vector>
using namespace std;
size_t FindMax(vector<int> v, size_t left, size_t right);
size_t FindMax_Compare(vector<int> v, size_t left, size_t right);
size_t FindMin(vector<int> v, size_t left, size_t right);
size_t FindMin_Compare(vector<int> v, size_t left, size_t right);

size_t FindMax(vector<int> v, size_t left, size_t right)//FindMax(v,0,v.size()-1);
{
	if ((left == (right - 1)) || (left == right))
		return FindMax_Compare(v, left, right);
	else
	{
		size_t mid = (left + right) / 2;
		return v[FindMax(v, left, mid)] > v[FindMax(v, mid + 1, right)] ? FindMax(v, left, mid) : FindMax(v, mid + 1, right);
	}

}

size_t FindMax_Compare(vector<int> v, size_t left, size_t right)
{
	if (v[left] >= v[right])
		return left;
	else
		return right;
}

size_t FindMin(vector<int> v, size_t left, size_t right)
{
	if ((left == (right - 1)) || (left == right))
		return FindMin_Compare(v, left, right);
	else
	{
		size_t mid = (left + right) / 2;
		return v[FindMin(v, left, mid)] < v[FindMin(v, mid + 1, right)] ? FindMin(v, left, mid) : FindMin(v, mid + 1, right);
	}
}

size_t FindMin_Compare(vector<int> v, size_t left, size_t right)
{
	if (v[left] <= v[right])
		return left;
	else
		return right;
}

int main()
{
	vector<int> v = {3,4,1,4,5,7,8,10,9,1,2,3};
	cout << FindMax(v, 0, v.size() - 1) << endl;
	cout << FindMin(v, 0, v.size() - 1) << endl;
}