#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
int dfs(vector<int> * graph, vector<bool> & used, int cur, int color, vector<int> & colors, int & diametr, vector<int> * visit)
{
    visit[color].push_back(cur);
    colors[cur] = color;
    int max1 = 0;
    int max2 = 0;
    for(int i = 0; i < graph[cur].size(); i++)
    {
        if(!used[graph[cur][i]])
        {
            used[graph[cur][i]] = true;
            int tmp = dfs(graph, used, graph[cur][i], color, colors, diametr, visit);
            if(tmp > max1)
            {
                max2 = max1;
                max1 = tmp;
            }
            else if(tmp == max1)
                max2 = tmp;
            else if(tmp > max2)
                max2 = tmp;
        }
    }
    diametr = max(diametr, max1 + max2);
    return max1 + 1;
}
int main()
{
    ios :: sync_with_stdio(false);
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> * graph = new vector<int> [n];
    for(int i = 0; i < m; i++)
    {
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        tmp1--;
        tmp2--;
        graph[tmp1].push_back(tmp2);
        graph[tmp2].push_back(tmp1);
    }
    vector<bool> used;
    used.resize(n);
    fill(used.begin(), used.end(), false);
    vector<int> colors;
    colors.resize(n);
    fill(colors.begin(), colors.end(), -1);
    vector<int> colorsPointer;
    colorsPointer.reserve(n);
    vector<int> * visit = new vector<int>[n];
    int color = 0;
    for(int i = 0; i < n; i++)
    {
        if(!used[i])
        {
            int diametr = 0;
            dfs(graph, used, i, color, colors, diametr, visit);
            colorsPointer.push_back(diametr);
            color++;
        }
    }
    for(int i = 0; i < q; i++)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int vertex;
            cin >> vertex;
            vertex--;
            cout << colorsPointer[colors[vertex]] << endl;
        }
        else
        {
            int v1, v2;
            cin >> v1 >> v2;
            v1--;
            v2--;
            int colorCur1 = colors[v1];
            int colorCur2 = colors[v2];
            if(colorCur1 != colorCur2)
            { 
                if(visit[colorCur1].size() < visit[colorCur2].size())
                    swap(colorCur1, colorCur2);
                int w1 = colorsPointer[colorCur1];
                int w2 = colorsPointer[colorCur2];
                int res = w1/2 + w1%2 + w2/2 + w2%2 + 1;
                for(int j = 0; j < visit[colorCur2].size(); j++)
                {
                    visit[colorCur1].push_back(visit[colorCur2][j]);
                    colors[visit[colorCur2][j]] = colorCur1; 
                }
                visit[colorCur2].clear();
                colorsPointer[colorCur1] = max(res, colorsPointer[colorCur1]);
            }
        }
    }
}