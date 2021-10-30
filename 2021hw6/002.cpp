#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>

int node[1000], to[6000], next[6000], vis[1000], mark[1000], color[1000], num[1000], dfn[1000], low[1000], index1, cnt;
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
            mark[x] = 0;
            if (x == u)
                break;
        }
        cnt++;
    }
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
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
        for (int i = 0; i < n; i++)
            if (!vis[i])
                Tarjan(i);
        memset(num, 0, sizeof(num));
        std::vector<std::set<int> > newG(cnt);
        for (int i = 0; i < n; i++)
        {
            int x = node[i];
            while (x != -1)
            {
                int v = to[x];
                if (color[i] != color[v])
                {
                    newG[color[i]].insert(color[v]);
                    num[color[v]]++;
                }
                x = next[x];
            }
        }
        int mark1 = 0, mark2 = 0;
        for (int i = 0; i < cnt; i++)
        {
            if (!num[i])
                mark1++;
            if (newG[i].empty())
                mark2++;
        }
        printf(mark1 == 1 && mark2 == 1 ? "Yes\n" : "No\n");
    }
}