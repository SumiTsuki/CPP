#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>> Pascal_Triangle(int numRows) {
    vector<vector<int>> vv(numRows);
    for (size_t i = 0; i < vv.size(); ++i)
    {
        vv[i].resize(i + 1, 0);
        vv[i][0] = vv[i][vv[i].size() - 1] = 1;
    }
    for (size_t i = 0; i < vv.size(); ++i)
    {
        for (size_t j = 0; j < vv[i].size(); ++j)
        {
            if (vv[i][j] == 0)
            {
                vv[i][j] = vv[i - 1][j] + vv[i - 1][j - 1];
            }
        }
    }
    return vv;
}
int main()
{
    vector <vector<int>> vv = Pascal_Triangle(5);
    for (size_t i = 0; i < vv.size(); ++i)
    {
        for (size_t j = 0; j < vv[i].size(); ++j)
        {
            cout << vv[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}