#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, m, s, node[100], next[200], to[200];
double v, edge[200][2], dis[100];

int spfa()
{
    for (int i = 0; i < n; i++)
        dis[i] = 0;
    dis[s] = v;
    int h = -1, t = 0, q[100], vis[100];
    memset(vis, 0, sizeof(vis));
    q[0] = s;
    while (h != t)
    {
        h = (h + 1) % n;
        int x = q[h];
        vis[x] = 0;
        for (int cur = node[x]; cur != -1; cur = next[cur])
        {
            double w = (dis[x] - edge[cur][1]) * edge[cur][0];
            if (dis[to[cur]] < w)
            {
                if (to[cur] == s)
                    return 1;
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
    return 0;
}

int main(void)
{
    scanf("%d%d%d%lf", &n, &m, &s, &v);
    s--;
    memset(node, -1, sizeof(node));
    for (int i = 0; i < m; i++)
    {
        int x, y;
        double a, b, c, d;
        scanf("%d%d%lf%lf%lf%lf", &x, &y, &a, &b, &c, &d);
        x--, y--;
        next[i * 2] = node[x];
        node[x] = i * 2;
        to[i * 2] = y;
        edge[i * 2][0] = a;
        edge[i * 2][1] = b;
        next[i * 2 + 1] = node[y];
        node[y] = i * 2 + 1;
        to[i * 2 + 1] = x;
        edge[i * 2 + 1][0] = c;
        edge[i * 2 + 1][1] = d;
    }
    printf(spfa() ? "YES" : "NO");
}