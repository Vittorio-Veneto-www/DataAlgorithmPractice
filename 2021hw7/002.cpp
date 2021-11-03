#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, m, node[1000], next[4000], to[4000], edge[4000], dis[1000];

void spfa()
{
    for (int i = 0; i < n; i++)
        dis[i] = 0x7fffffff;
    dis[n - 1] = 0;
    int h = -1, t = 0, q[1000], vis[1000];
    memset(vis, 0, sizeof(vis));
    q[0] = n - 1;
    while (h != t)
    {
        h = (h + 1) % n;
        int x = q[h];
        vis[x] = 0;
        for (int cur = node[x]; cur != -1; cur = next[cur])
        {
            int w = dis[x] + edge[cur];
            if (dis[to[cur]] > w)
            {
                dis[to[cur]] = w;
                if (!vis[to[cur]])
                {
                    vis[to[cur]] = 1;
                    t = (t + 1) % n;
                    q[t] = to[cur];
                }
            }
        }
    }
}

int main(void)
{
    scanf("%d%d", &m, &n);
    memset(node, -1, sizeof(node));
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        x--, y--;
        next[i * 2] = node[x];
        node[x] = i * 2;
        to[i * 2] = y;
        edge[i * 2] = z;
        next[i * 2 + 1] = node[y];
        node[y] = i * 2 + 1;
        to[i * 2 + 1] = x;
        edge[i * 2 + 1] = z;
    }
    spfa();
    printf("%d\n", dis[0]);
}