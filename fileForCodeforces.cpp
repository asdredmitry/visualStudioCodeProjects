#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits.h>
using namespace std;
int inf = INT_MAX/10;
int log2Max = log2(inf);
const int maxN = 200000; 
vector<int> powers;
vector<int> logArr;
vector<int> visit;
vector<int> weights;
vector<int> first;
//int ** sparseTable; 
void dfs(vector<int> * graph, vector<bool> & used, int cur)
{
    visit.push_back(cur);
    for(int i = 0; i < graph[cur].size(); i++)
    {
        if(!used[graph[cur][i]])
        {
            used[graph[cur][i]] = true;
            weights[graph[cur][i]] = weights[cur] + 1;
            dfs(graph, used, graph[cur][i]);
            visit.push_back(cur);
        }
    }
}
int lca(int a1, int a2, int ** sparseTable)
{
    //cout << a1 << " " << a2 << endl;
    int l = first[a1];
    int r = first[a2];
    if(l > r)
        swap(l, r);
    cout  << r << " r and l " << l << endl;
    cout << "Come here" << r - powers[logArr[r - l + 1] + 1] << " " << logArr[r - l + 1] << endl;
    cout << sparseTable[0][1] << endl;
    int vertex1 = sparseTable[l][logArr[ r - l + 1]];
    cout << "Come and here" << endl;
    int vertex2 = sparseTable[r - powers[logArr[r - l + 1]] + 1][logArr[r - l + 1]];
    cout << " Finally here" << endl;
    //cout << " and here" << endl;
    return 1;
    //return (weights[vertex1] > weights[vertex1] ? vertex1 : vertex1);
}
int main()
{
    ios :: sync_with_stdio(false);
    //vector<int> powers(maxN*2);
    //vector<int> logArr(maxN*2);
    powers.resize(maxN*2);
    logArr.resize(maxN*2);
    powers[0] = 1;
    for(int i = 1; i < 2*maxN; i++)
    {
        if(i < log2Max)
            powers[i] = powers[i - 1]*2;
        else
            powers[i] = inf;
        logArr[i] = int(log2(i));
    }
    int n;
    cin >> n;
    vector<int> * graph = new vector<int>[n];
    int q;
    cin >> q;
    int tmp;
    for(int i = 0; i < n - 1; i++)
    {
        cin >> tmp;
        tmp--;
        graph[i + 1].push_back(tmp);
        graph[tmp].push_back(i + 1);
    }
    vector<bool> used(n);
    cout << " i am here" << endl;
    //vector<int> weights(n);
    weights.resize(n);
    fill(used.begin(), used.end(), false);
    fill(weights.begin(), weights.end(), 0);
    //vector<int> visit;
    visit.reserve(2*n + 1);
    used[0] = true;
    cout << " and here " << endl;
    dfs(graph, used, 0);
    cout << " visit" <<  endl;
    for(int i = 0; i < visit.size(); i++)
        cout << visit[i] << " ";
    cout << endl;
    first.resize(n);
    fill(first.begin(), first.end(), -1);
    for(int i = 0; i < visit.size(); i++)
    {
        if(first[visit[i]] == -1)
            first[visit[i]] = i; 
    }
    cout << " I come till here" << endl;
    int ** sparseTable = new int *[visit.size()];
    for(int i = 0; i < visit.size(); i++)
        sparseTable[i] = new int [logArr[visit.size()] + 1];
    cout << logArr[visit.size()] + 1 << " logArr " << endl;; 
    for(int i = visit.size() - 1; i >= 0; i--)
    {
        for(int j = 0; j < logArr[visit.size()] + 1; j++)
        {
            if(j == 0)
                sparseTable[i][j] = visit[i];
            else
            {
                int vertex1 = sparseTable[i][j - 1];
                int vertex2 = (i + powers[j - 1] < visit.size()) ? sparseTable[i + powers[j - 1]][j-1] : sparseTable[i][j - 1];
                sparseTable[i][j] = weights[vertex1] > weights[vertex2] ? vertex2 : vertex1;
            }
        }
    }
    cout << sparseTable[0][1] << " sparseTable 0 and 1" << endl;
    cout << "first" << endl;
    for(int i = 0; i < first.size(); i++)
        cout << first[i] << " ";
    cout << endl;
    int a[3];
    for(int i = 0; i < q; i++)
    {
        int globalMax = 0;
        cin >> a[0] >> a[1] >> a[2];
        a[0]--;
        a[1]--;
        a[2]--;
        for(int j = 0; j < 3; j++)
        {
            int curMax = 0;
            int f = a[j];
            int t = a[(j + 1)%3];
            int s = a[(j + 2)%3];
            cout << f << t << s << endl;
            int lcaft = lca(f, t, sparseTable);
            cout << "and here" << endl;
            int lcafs = lca(f, s, sparseTable);
            //int lcats = lca(t, s);
            curMax = min(abs(weights[lcaft] - weights[f]), abs(weights[lcafs] - weights[f]));
            globalMax = max(globalMax, curMax);
        }
        cout << globalMax << " globalMax ";
    }
    cout << endl;


    return 0;
}