#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    vector<int> v;
    for(int i = 0; i < 10; i++)
        v.push_back(i);
    vector<int> newVec;
    newVec.reserve(v.size());
    copy(v.begin(), v.end(), back_inserter(newVec));
    for(int i = 0; i < v.size(); i++)
        cout << newVec[i] << " " << endl;
    return 0;
}