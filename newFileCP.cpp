#include <iostream>
#include <cmath>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
void createTree(vector<int> & data, vector<int> & minTree, vector<int> & maxTree,int l, int r, int curIndex)
{
    if(r == l)
    {
        maxTree[curIndex] = data[l];
        minTree[curIndex] = data[l];
        return ;
    }
    int t = (l + r)/2;
    createTree(data, minTree, maxTree, l, t, curIndex*2 + (curIndex == 0));
    createTree(data, minTree, maxTree, t + 1, r, 2*curIndex + 1 + (curIndex == 0));
    minTree[curIndex] = min(minTree[2*curIndex], minTree[2*curIndex + 1]);
    maxTree[curIndex] = max(maxTree[2*curIndex], maxTree[2*curIndex + 1]);
}
int main()
{
    cout << " I am here" << endl;
    int n;
    vector<int> data;
    cout << " hello world" << endl;
    //data.reserve(n);
    for(int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        data.push_back(tmp);
    }
    cout << " and here" << endl;
    vector<int> minTree;
    vector<int> maxTree;
    minTree.resize(4*data.size() + 1);
    maxTree.resize(4*data.size() + 1);
    createTree(data, minTree, maxTree, 0, data.size() - 1, 0);
    for(int t : data)
        cout << t << " ";
    cout << endl;
    for(int t : minTree)
        cout << t << " ";
    cout << endl;
    for(int t : maxTree)
        cout << t << " ";
    cout << endl;
    return 0;
}