#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define maxn 1000
#define maxN maxn + 2
#define maxM 40000 + 4

int n, cnt, node[maxN], next[maxM], to[maxM], val[maxM], cap[maxM], dis[maxN];
int vis[maxN], pre[maxN], cost;

void addedge(int x, int y, int z, int c)
{
    next[cnt] = node[x];
    node[x] = cnt;
    to[cnt] = y;
    val[cnt] = z;
    cap[cnt] = c;
    cnt++;
    next[cnt] = node[y];
    node[y] = cnt;
    to[cnt] = x;
    val[cnt] = -z;
    cap[cnt] = 0;
    cnt++;
}

int spfa(int s, int t1)
{
    for (int i = 0; i < n + 2; i++)
        dis[i] = 0x7fffffff;
    dis[s] = 0;
    int h = -1, t = 0, q[maxN];
    memset(vis, 0, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    q[0] = s;
    while (h != t)
    {
        h = (h + 1) % (maxN);
        int x = q[h];
        vis[x] = 0;
        for (int cur = node[x]; cur != -1; cur = next[cur])
            if (cap[cur])
            {
                int w = dis[x] + val[cur], v = to[cur];
                if (dis[v] > w)
                {
                    dis[v] = w;
                    pre[v] = cur;
                    if (!vis[v])
                    {
                        vis[v] = 1;
                        t = (t + 1) % (maxN);
                        q[t] = v;
                    }
                }
            }
    }
    return dis[t1] != 0x7fffffff;
}

int dfs(int u, int t, int flow)
{
    if (u == t)
        return flow;
    vis[u] = 1;
    int maxflow = 0;
    for (int cur = node[u]; cur != -1 && maxflow < flow; cur = next[cur])
    {
        int v = to[cur];
        if (!vis[v] && cap[cur] && dis[v] == dis[u] + val[cur])
        {
            int x = dfs(v, t, std::min(cap[cur], flow - maxflow));
            if (x)
            {
                cost += x * val[cur];
                cap[cur] -= x;
                cap[cur ^ 1] += x;
                maxflow += x;
            }
        }
    }
    vis[u] = 0;
    return maxflow;
}

int _mcmf(int s, int t)
{
    int maxflow = 0;
    while (spfa(s, t))
    {
        int x;
        while ((x = dfs(s, t, 0x7fffffff)))
            maxflow += x;
    }
    return maxflow;
}

int mcmf(int s, int t)
{
    int maxflow = 0;
    while (spfa(s, t))
    {
        int x;
        while ((x = dfs(s, t, 0x7fffffff)))
            maxflow += x;
        int min = 0x7fffffff;
        for (int cur = pre[t]; cur != -1; cur = pre[to[cur ^ 1]])
            min = std::min(min, cap[cur]);
        for (int cur = pre[t]; cur != -1; cur = pre[to[cur ^ 1]])
        {
            cost += min * val[cur];
            cap[cur] -= min;
            cap[cur ^ 1] += min;
            maxflow += min;
        }
    }
    return maxflow;
}

int main(void)
{
    int m;
    scanf("%d%d", &n, &m);
    memset(node, -1, sizeof(node));
    cnt = 0;
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addedge(x, y, z, 1);
        addedge(y, x, z, 1);
    }
    addedge(0, 1, 0, 2);
    addedge(n, n + 1, 0, 2);
    cost = 0;
    int ans = mcmf(0, n + 1);
    printf("%d\n", cost);
}