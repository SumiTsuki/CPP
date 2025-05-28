#include<iostream>
#include<vector>
using namespace std;
template <class T>
void MERGE(vector<T>& v, size_t left, size_t mid, size_t right)
{
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;
    vector<T> L(n1);
    vector<T> R(n2);
    for (size_t i = 0; i < n1; ++i)
        L[i] = v[left + i];
    for (size_t j = 0; j < n2; ++j)
        R[j] = v[mid + 1 + j];
    size_t i = 0;
    size_t j = 0;
    size_t k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            v[k] = L[i];
            ++i;
        }
        else {
            v[k] = R[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        v[k] = L[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        v[k] = R[j];
        ++j;
        ++k;
    }
}
template<class T>
void MERGE_SORT(vector<T>& v, size_t left, size_t right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		MERGE_SORT(v, left, mid);
		MERGE_SORT(v, mid + 1, right);
		MERGE(v, left, mid, right);
	}
}
int main()
{
	vector<int> v = { 5,4,6,3,9,8,10,2,1,7 };
	MERGE_SORT(v, 0, v.size()-1);
	for (auto e : v)
		cout << e << " ";
	return 0;
}