#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <cstdio>
#include <limits.h>
#include <utility>
using namespace std;
const int inf = INT_MAX;
void dfs(vector<long long int> * graph, vector<pair<int, int> > & visit,  int * weights, int cur)
{
    visit.push_back(make_pair(weights[cur], cur));
    bool hasChild = false;
    for(int i = 0; i < graph[cur].size(); i++)
    {
        hasChild = true;
        weights[graph[cur][i]] = weights[cur] + 1;
        dfs(graph, visit, weights, graph[cur][i]);
        visit.push_back(make_pair(weights[cur], cur));
    }
    if(!hasChild)
        visit.push_back(make_pair(weights[cur], cur));
}
int main()
{
    int max = 100100;
    long long int * log2Arr = new long long int[max];
    for(int i = 1; i < max; i++)
    {
        log2Arr[i] = int(log2(i));
    }
    long long int * powers = new long long int[max];
    powers[0] = 1;
    for(int i = 1; i < max; i++)
    {
        powers[i] = 2*powers[i - 1];
    }
    FILE * read = fopen("lca_rmq.in", "r");
    FILE * write = fopen("lca_rmq.out", "w");
    long long int n;
    long long int m;
    fscanf(read,"%lld",&n);
    fscanf(read,"%lld",&m);
    vector<long long int> * graph = new vector<long long int>[n];
    for(int i = 0; i < n - 1; i++)
    {
        long long int tmp;
        fscanf(read, "%lld",&tmp);
        graph[tmp].push_back(i + 1);
    }
    long long int  a1, a2;
    fscanf(read, "%lld", &a1);
    fscanf(read, "%lld", &a2);
    long long int x, y, z;
    fscanf(read,"%lld", &x);
    fscanf(read,"%lld", &y);
    fscanf(read,"%lld", &z);
    int * weights = new int[n];
    weights[0] = 0;
    vector<pair<int, int> > visit;
    dfs(graph, visit, weights, 0);
    long long int prevAns = 0;
    pair<int, int> ** sparseTable = new pair<int, int>* [visit.size()];
    for(int i = 0 ; i< visit.size(); i++)
        sparseTable[i] = new pair<int, int>[log2Arr[visit.size()]+ 1];
    for(int i = 0; i < visit.size(); i++)
    {
        for(int j = 0; j < log2Arr[visit.size()] + 1; j++)
            sparseTable[i][j].first = inf;
    }
    for(int  i = visit.size() - 1; i >= 0; i--)
    {
        for(int j = 0; j < log2Arr[visit.size()] + 1; j++)
        {
            if(j == 0)
                sparseTable[i][j] = visit[i];
            else
            {
                pair<int ,int> tmp1 = sparseTable[i][j - 1];
                pair<int ,int> tmp2 = (i + powers[j - 1] < visit.size())? sparseTable[i + powers[j - 1]][j - 1] : sparseTable[i][j - 1];
                sparseTable[i][j] = (tmp1 > tmp2) ? tmp2 : tmp1;
            }
        }
    }
    long long int answer = 0;
    int * first = new int[n];
    for(int i = 0; i < n; i++)
        first[i] = -1;
    for(int i = 0; i < visit.size(); i++)
    {
        if(first[visit[i].second] == -1)
            first[visit[i].second] = i;
    }
    for(long long int i = 0; i < m; i++)
    {
        if(i != 0)
        {
            long long tmp1 = (x*a1 + y*a2 + z)%n;
            long long tmp2 = (x*a2 + tmp1*y + z)%n;
            a1 = tmp1;
            a2 = tmp2; 
        }
        long long int r1 = (a1 + prevAns)%n;
        long long int r2 = a2;
        long long int l = first[r1];
        long long int r = first[r2];
        if(l > r)
            swap(l, r);
        pair<int, int> tpq1 = sparseTable[l][log2Arr[r - l + 1]];
        pair<int, int> tpq2 = sparseTable[r - powers[log2Arr[r - l + 1]] + 1][log2Arr[r - l + 1]];
        pair<int, int> ans = (tpq1 > tpq2) ? tpq2 : tpq1;
        prevAns = ans.second;
        answer += ans.second;        
    }
    fprintf(write, "%lld", answer);
    fclose(read);
    fclose(write);
    return 0;
}