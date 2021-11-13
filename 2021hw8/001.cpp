#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, G[102][102], G1[102][102], nodes[50][10][2], capacity[50], num, layer[102], vis[102];

void addedge(int x, int y, int z)
{
    G[x][y] = z;
}

int countlayer()
{
    int q[102], h = -1, t = 0;
    memset(layer, -1, sizeof(layer));
    layer[n * 2] = 0;
    q[0] = n * 2;
    while (h < t)
    {
        h++;
        int x = q[h];
        for (int i = 0; i < n * 2 + 2; i++)
            if (G[x][i] && layer[i] == -1)
            {
                layer[i] = layer[x] + 1;
                if (i == n * 2 + 1)
                    return 1;
                t++;
                q[t] = i;
            }
    }
    return 0;
}

int dinic()
{
    int maxflow = 0, stack[102], top;
    while (countlayer())
    {
        top = 0;
        memset(vis, 0, sizeof(vis));
        stack[0] = n * 2;
        vis[n * 2] = 1;
        while (top != -1)
        {
            int x = stack[top];
            if (x == n * 2 + 1)
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
                for (i = 0; i < n * 2 + 2; i++)
                    if (G[x][i] && layer[i] == layer[x] + 1 && !vis[i])
                    {
                        vis[i] = 1;
                        stack[++top] = i;
                        break;
                    }
                if (i == n * 2 + 2)
                    top--;
            }
        }
    }
    return maxflow;
}

int main(void)
{
    int p;
    scanf("%d%d", &p, &n);
    memset(G, 0, sizeof(G));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &capacity[i]);
        for (int j = 0; j < p; j++)
            scanf("%d", &nodes[i][j][0]);
        for (int j = 0; j < p; j++)
            scanf("%d", &nodes[i][j][1]);
        addedge(i, i + n, capacity[i]);
    }
    for (int i = 0; i < n; i++)
    {
        int mark = 1;
        for (int j = 0; j < p; j++)
            if (nodes[i][j][0] == 1)
                mark = 0;
        if (mark)
            addedge(n * 2, i, 1e9);
        mark = 1;
        for (int j = 0; j < p; j++)
            if (nodes[i][j][1] != 1)
                mark = 0;
        if (mark)
            addedge(i + n, n * 2 + 1, 1e9);
        for (int j = 0; j < n; j++)
        {
            mark = 1;
            for (int k = 0; k < p; k++)
                if (nodes[i][k][0] == 0 && nodes[j][k][1] != 0)
                    mark = 0;
                else if (nodes[i][k][0] == 1 && nodes[j][k][1] != 1)
                    mark = 0;
            if (mark)
                addedge(j + n, i, 1e9);
        }
    }
    memcpy(G1, G, sizeof(G));
    printf("%d", dinic());
    int cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && G1[i + n][j] > G[i + n][j])
                cnt++;
    printf(" %d\n", cnt);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && G1[i + n][j] > G[i + n][j])
                printf("%d %d %d\n", i + 1, j + 1, G1[i + n][j] - G[i + n][j]);
}