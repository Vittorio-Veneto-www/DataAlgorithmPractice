#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, f[230][230], G[232][232], num, layer[232], vis[232];

int countlayer()
{
    int q[232], h = -1, t = 0;
    memset(layer, -1, sizeof(layer));
    layer[n] = 0;
    q[0] = n;
    while (h < t)
    {
        h++;
        int x = q[h];
        for (int i = 0; i < n + 2; i++)
            if (G[x][i] && layer[i] == -1)
            {
                layer[i] = layer[x] + 1;
                if (i == n + 1)
                    return 1;
                t++;
                q[t] = i;
            }
    }
    return 0;
}

int dinic()
{
    int maxflow = 0, stack[232], top;
    while (countlayer())
    {
        top = 0;
        memset(vis, 0, sizeof(vis));
        stack[0] = n;
        vis[n] = 1;
        while (top != -1)
        {
            int x = stack[top];
            if (x == n + 1)
            {
                int min = 1e9;
                int min1;
                for (int i = 1; i <= top; i++)
                {
                    int s = stack[i - 1], v = stack[i];
                    if (min > G[s][v])
                    {
                        min = G[s][v];
                        min1 = s;
                    }
                }
                maxflow += min;
                for (int i = 1; i <= top; i++)
                {
                    int s = stack[i - 1], v = stack[i];
                    G[s][v] -= min;
                    G[v][s] += min;
                }
                while (stack[top] != min1)
                {
                    vis[stack[top]] = 0;
                    top--;
                }
            }
            else
            {
                int i;
                for (i = 0; i < n + 2; i++)
                    if (G[x][i] && layer[i] == layer[x] + 1 && !vis[i])
                    {
                        vis[i] = 1;
                        stack[++top] = i;
                        break;
                    }
                if (i == n + 2)
                    top--;
            }
        }
    }
    return maxflow;
}

int main(void)
{
    int k, c, m;
    scanf("%d%d%d", &k, &c, &m);
    n = k + c;
    memset(f, 0x3f, sizeof(f));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &f[i][j]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (f[i][j] == 0)
                f[i][j] = 1e9;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                    f[i][j] = std::min(f[i][j], f[i][k] + f[k][j]);
    int l = 0, r = 230 * 200 + 1, mid, last;
    while (l < r)
    {
        mid = (l + r) >> 1;
        memset(G, 0, sizeof(G));
        for (int i = 0; i < c; i++)
            G[n][i + k] = 1;
        for (int i = 0; i < k; i++)
            G[i][n + 1] = m;
        for (int i = 0; i < c; i++)
            for (int j = 0; j < k; j++)
                if (f[i + k][j] <= mid)
                    G[i + k][j] = 1;
        if (dinic() != c)
            l = mid + 1;
        else
            r = mid, last = mid;
    }
    printf("%d\n", last);
}