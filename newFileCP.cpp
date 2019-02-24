#include <iostream>
#include <cmath> 
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>
using namespace std;
void addValue(vector<long long int> & treeSum, vector<long long int> & newTree, int l, int r, int nL, int nR, long long int value, int curIndex)
{
    if(l == nL && r == nR)
    {
        if(l != r)
        {
            newTree[2*curIndex] = value;
            newTree[2*curIndex + 1] = value;
            newTree[curIndex] = 0;
        }
        treeSum[curIndex] = (r - l + 1)*value;
        return ;
    }
    if(newTree[curIndex])
    {
        if(l != r)
        {
            newTree[2*curIndex] = newTree[curIndex];
            newTree[2*curIndex + 1] = newTree[curIndex];
            newTree[curIndex] = 0;
        }
    }
    int t = (l + r)/2;
    if(nL > t)
    {
        addValue(treeSum, newTree, t + 1, r, nL, nR, value, 2*curIndex + 1);
        treeSum[2*curIndex] = (t - l + 1)*newTree[2*curIndex];
         //treeSum[2*curIndex + 1] = (r - t)*newTree[2*curIndex + 1];
    }
    else if(nR <= t)
    {
        addValue(treeSum, newTree, l, t, nL, nR, value, 2*curIndex);
        treeSum[2*curIndex + 1] = (r - t)*newTree[2*curIndex + 1];
        //treeSum[2*curIndex] = (t - l + 1)*newTree[2*curIndex];
    }
    else
    {
        addValue(treeSum, newTree, l, t, nL, t, value, 2*curIndex);
        addValue(treeSum, newTree, t+ 1, r, t + 1, nR, value, 2*curIndex + 1);
    }
    treeSum[curIndex] = treeSum[2*curIndex] + treeSum[2*curIndex + 1];

}
long long int getSum(vector<long long int> & treeSum, vector<long long int> & newTree, int l, int r, int nL, int nR, int curIndex)
{
    if(l == nL && r == nR)
    {
        //cout << l << " " << r << " " << newTree[curIndex] << " treeSum " << treeSum[curIndex] << endl;
       if(newTree[curIndex])
            treeSum[curIndex] = (r - l + 1)*newTree[curIndex];
        return treeSum[curIndex];
    }
    int t = (l + r)/2;
    long long int res = 0;
    if(newTree[curIndex])
    {
        newTree[2*curIndex] = newTree[curIndex];
        newTree[2*curIndex + 1] = newTree[curIndex];
        treeSum[curIndex] = (r - l + 1)*newTree[curIndex];
        newTree[curIndex] = 0;
    }
    if(nL > t)
    {
        res += getSum(treeSum, newTree, t + 1, r, nL, nR, 2*curIndex + 1);
    }
    else if(nR <= t)
    {
        res += getSum(treeSum, newTree, l, t, nL, nR, 2*curIndex);
    }
    else
    {
        res += getSum(treeSum, newTree, l, t, nL, t, 2*curIndex);
        res += getSum(treeSum, newTree, t + 1, r, t + 1, nR, 2*curIndex + 1);
    }
    return res;    
}
int main()
{
    ifstream input("sum.in");
    ofstream output("sum.out");
    streambuf * cinbuf = cin.rdbuf();
    streambuf * coutbuf = cout.rdbuf();
    cin.rdbuf(input.rdbuf());
    cout.rdbuf(output.rdbuf());
    int N, K;
    cin >> N >> K;
    vector<long long int> treeSum;
    treeSum.resize(4*N + 1);
    fill(treeSum.begin(), treeSum.end(), 0);
    vector<long long int> newTree;
    newTree.resize(4*N + 1);
    fill(newTree.begin(), newTree.end(), 0);
    //addValue(treeSum, newTree,0, N - 1,  0, N - 1, 0, 1);
    for(int i = 0; i < K; i++)
    {
        char l;
        cin >> l;
        if(l == 'A')
        {
            int l, r, x;
            cin >> l >> r >> x;
            cout << " next addValue" << endl;
            addValue(treeSum, newTree, 0, N - 1, l - 1, r - 1, x, 1);
            //for(long long int t : treeSum)
            //    cout << t << " ";
            //cout << endl;
            //for(long long int t : newTree)
            //    cout << t << " ";
            //cout << endl;
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << getSum(treeSum, newTree, 0, N - 1, l - 1, r - 1, 1) << endl;
        }
        
    }
    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);
}