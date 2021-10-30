#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>

int node[10000], to[50000], next[50000], vis[10000], mark[10000], color[10000], num[10000], dfn[10000], low[10000], index1, cnt;
std::stack<int> stack;

void Tarjan(int u)
{
    dfn[u] = low[u] = index1++;
    stack.push(u);
    vis[u] = 1;
    mark[u] = 1;
    int x = node[u];
    while (x != -1)
    {
        int v = to[x];
        if (!vis[v])
        {
            Tarjan(v);
            low[u] = std::min(low[u], low[v]);
        }
        else if (mark[v])
            low[u] = std::min(low[u], low[v]);
        x = next[x];
    }
    if (dfn[u] == low[u])
    {
        while (1)
        {
            int x = stack.top();
            stack.pop();
            color[x] = cnt;
            num[cnt]++;
            mark[x] = 0;
            if (x == u)
                break;
        }
        cnt++;
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
        next[i] = node[x];
        node[x] = i;
        to[i] = y;
    }
    index1 = 0;
    cnt = 0;
    memset(vis, 0, sizeof(vis));
    memset(mark, 0, sizeof(mark));
    memset(num, 0, sizeof(num));
    for (int i = 0; i < n; i++)
        if (!vis[i])
            Tarjan(i);
    std::vector<std::set<int> > newG(cnt);
    for (int i = 0; i < n; i++)
    {
        int x = node[i];
        while (x != -1)
        {
            int v = to[x];
            if (color[i] != color[v])
                newG[color[i]].insert(color[v]);
            x = next[x];
        }
    }
    int mark1 = 0;
    for (int i = 0; i < cnt; i++)
        if (newG[i].empty())
            if (!mark1)
                mark1 = num[i];
            else
                mark1 = -1;
    printf("%d\n", mark1 != -1 ? mark1 : 0);
}