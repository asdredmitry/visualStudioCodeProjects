#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;
const int blockSize = 350;
const int inf = INT_MAX/10;
const int log2Max = int(log2(inf));
const int maxN = 200000;
vector<int> powers;
vector<int> log2Arr;
vector<int> visit;
vector<int> bfsVisit;
vector<int> weights;
vector<int> redDistance;
vector<bool> used;
vector<int> first;
void dfs(vector<int> * graph, int cur)
{
    visit.push_back(cur);
    for(int i = 0; i < graph[cur].size(); i++)
    {
        if(!used[graph[cur][i]])
        {
            used[graph[cur][i]] = true;
            weights[graph[cur][i]] = weights[cur] + 1;
            dfs(graph, graph[cur][i]);
            visit.push_back(cur);
        }
    }
}
void bfs(vector<int> * graph, int root)
{
    queue<int> q;
    q.push(root);
    used[root] = true;
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        bfsVisit.push_back(cur);
        for(int i = 0; i < graph[cur].size(); i++)
        {
            if(!used[graph[cur][i]])
            {
                used[graph[cur][i]] = true;
                q.push(graph[cur][i]);
            }
        }
    }
}
int lca(int a1, int a2, int ** sparseTable)
{
    int l = first[a1];
    int r = first[a2];
    if(l > r)
        swap(l, r);
    int vertex1 = sparseTable[l][log2Arr[ r - l + 1]];
    int vertex2 = sparseTable[r - powers[log2Arr[r - l + 1]] + 1][log2Arr[r - l + 1]];
    return (weights[vertex1] > weights[vertex1] ? vertex1 : vertex1);
}
void updateTree(vector<int> * graph, int root)
{
    for(int i = bfsVisit.size() - 1; i >= 0; i--)
    {
        int cur = bfsVisit[i];
        for(int j = 0; j < graph[cur].size(); j++)
        {
            if(weights[graph[cur][j]] < weights[cur])
                redDistance[graph[cur][j]] = min(redDistance[graph[cur][j]], redDistance[cur]);
        }
    }
    for(int i = 0; i < bfsVisit.size(); i++)
    {
        int cur = bfsVisit[i];
        for(int j = 0; j < graph[cur].size(); j++)
        {
            if(weights[graph[cur][j]] > weights[cur])
                redDistance[graph[cur][j]] = min(redDistance[graph[cur][j]], redDistance[cur]);
        }
    }
}
int main()
{
    ios :: sync_with_stdio(false);
    powers.resize(2*maxN);
    log2Arr.resize(2*maxN);
    powers[0] = 1;
    for(int i = 1; i < 2*maxN; i++)
    {
        if(i <= log2Max)
            powers[i] = powers[i - 1]*2;
        else
            powers[i] = inf;
        log2Arr[i] = int(log2(i));
    }
    int n, m;
    cin >> n >> m;
    vector<int> * graph = new vector<int> [n];
    for(int i = 0; i < n - 1; i++)
    {
        int v1, v2;
        cin >> v1 >> v2;
        v1--;
        v2--;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
    used.resize(n);
    fill(used.begin(), used.end(), false);
    weights.resize(n);
    fill(weights.begin(), weights.end(), 0);
    visit.reserve(2*n + 1);
    used[0] = true;
    
    dfs(graph, 0);
    fill(used.begin(), used.end(), false);
    used[0] = true;
    bfsVisit.reserve(n);
    bfs(graph, 0);
    first.resize(n);
    fill(first.begin(), first.end(), -1);
    cout << endl;
    for(int i = 0; i < visit.size(); i++)
    {
        cout << visit[i] << " ";
    }
    cout << endl;
    int ** sparseTable = new int *[visit.size()];
    for(int i = 0; i < visit.size(); i++)
        sparseTable[i] = new int [log2Arr[visit.size()] + 1];
    for(int i = visit.size() - 1; i >= 0; i--)
    {
        for(int j = 0; j < log2Arr[visit.size()] + 1; j++)
        {
            if(j == 0)
                sparseTable[i][j] = visit[i];
            else
            {
                int vertex1 = sparseTable[i][j - 1];
                int vertex2 = (i + powers[j - 1] < visit.size()) ? sparseTable[i + powers[j - 1]][j - 1]: sparseTable[i][j - 1] ;
                if(weights[vertex1] < weights[vertex2])
                    sparseTable[i][j] = vertex1;
                else 
                    sparseTable[i][j] = vertex2;
            }
        }
    }
    redDistance.resize(n);
    for(int i = 0; i < n; i++)
        redDistance[i] = weights[i];
    int blockCounter = 0;
    vector<int> redVertex;
    redVertex.reserve(blockSize);
    for(int i = 0; i < m; i++)
    {
        if(blockCounter < blockSize)
        {
            int type, vertex;
            cin >> type >> vertex;
            type--;
            vertex--;
            if(type == 1)
            {
                redVertex.push_back(vertex);
                redDistance[vertex] = 0;
            }
            else
            {
                int globalMin = inf;
                for(int j = 0; j < redVertex.size(); j++)
                {
                    int curLca = lca(vertex, redVertex[i], sparseTable);
                    int curMin = weights[vertex] + weights[redVertex[i]] - 2*weights[curLca];
                    globalMin = min(curMin, globalMin);
                }
                globalMin = min(globalMin, redDistance[vertex]);
                cout << globalMin << " ";
                cout << " Hello world";
            }
        }
        else
        {
            redVertex.clear();
            updateTree(graph, 0);
            blockCounter = 0;
        }
        blockCounter++;

    }
    return 0;
}