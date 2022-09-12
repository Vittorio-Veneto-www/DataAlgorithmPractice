#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

#define maxN 200000
#define maxM 200000

int node[maxN], edge[maxM], next[maxN];

int dfn[maxN], low[maxN], vis[maxN], mark[maxN], stack[maxN], top = -1, index1 = 0, cnt = 0, max = 0;

void tarjan(int x)
{
    dfn[x] = low[x] = index1++;
    stack[++top] = x;
    vis[x] = mark[x] = 1;
    int cur = node[x];
    while (cur != -1)
    {
        int v = edge[cur];
        if (!vis[v])
        {
            tarjan(v);
            low[x] = std::min(low[x], low[v]);
        }
        else if (mark[v])
            low[x] = std::min(low[x], low[v]);
        cur = next[cur];
    }
    if (dfn[x] == low[x])
    {
        cnt++;
        int num = 0;
        while (1)
        {
            int t = stack[top--];
            mark[t] = 0;
            num++;
            if (t == x)
                break;
        }
        max = std::max(max, num);
    }
}

int main(void)
{
    int n, m;
    scanf("%d%d", &n, &m);
    memset(node, -1, sizeof(node));
    for (int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        x--, y--;
        edge[i] = y;
        next[i] = node[x];
        node[x] = i;
    }
    memset(vis, 0, sizeof(vis));
    memset(mark, 0, sizeof(mark));
    for (int i = 0; i < n; i++)
        if (!vis[i])
            tarjan(i);
    printf("%d\n%d\n", max, cnt);
}