#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define maxN 400

int n, f[maxN][maxN], G[maxN + 2][maxN + 2], num, layer[maxN + 2], vis[maxN + 2];

int countlayer()
{
    int q[maxN + 2], h = -1, t = 0;
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
    int maxflow = 0, stack[maxN + 2], top;
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
    int k, c;
    while (scanf("%d%d", &k, &c) != EOF)
    {
        n = k + c;
        memset(G, 0, sizeof(G));
        for (int i = 0; i < k; i++)
        {
            int x;
            scanf("%d", &x);
            for (int j = 0; j < x; j++)
            {
                int y;
                scanf("%d", &y);
                G[i][y + k - 1] = 1;
            }
            G[n][i] = 1;
        }
        for (int i = 0; i < c; i++)
            G[i + k][n + 1] = 1;
        printf("%d\n", dinic());
    }
}