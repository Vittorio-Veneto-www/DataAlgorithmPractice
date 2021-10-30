#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>

int n, edge[1000][1000][2], dfn[1000], low[1000], index1, bridge[1000], bridgecnt, min;

void Tarjan(int u, int father)
{
    dfn[u] = low[u] = ++index1;
    for (int v = 0; v < n; v++)
        if (edge[u][v][0])
        {
            if (!dfn[v])
            {
                Tarjan(v, u);
                low[u] = std::min(low[u], low[v]);
                if (dfn[u] < low[v] && edge[u][v][0] == 1)
                    min = std::min(min, edge[u][v][1]);
            }
            else if (father != v)
                low[u] = std::min(low[u], low[v]);
        }
}

int main(void)
{
    int m;
    scanf("%d%d", &n, &m);
    while (n)
    {
        memset(edge, 0, sizeof(edge));
        for (int i = 0; i < m; i++)
        {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            x--, y--;
            edge[x][y][0]++;
            edge[x][y][1] = z;
            edge[y][x][0]++;
            edge[y][x][1] = z;
        }
        index1 = 0;
        bridgecnt = 0;
        min = 0x7fffffff;
        int mark1 = 0;
        memset(dfn, 0, sizeof(dfn));
        for (int i = 0; i < n; i++)
            if (!dfn[i])
                Tarjan(i, -1), mark1++;
        if (min == 0x7fffffff)
            min = -1;
        if (min == 0)
            min = 1;
        if (mark1 != 1)
            min = 0;
        printf("%d\n", min);
        scanf("%d%d", &n, &m);
    }
}