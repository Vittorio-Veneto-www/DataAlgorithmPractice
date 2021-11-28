#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define maxN 40000
#define maxM 80000

int n, cnt, node[maxN], next[maxM], to[maxM], val[maxM], depth[maxN], f[maxN][17][2];

void addedge(int x, int y, int z)
{
    next[cnt] = node[x];
    node[x] = cnt;
    to[cnt] = y;
    val[cnt] = z;
    cnt++;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    memset(node, -1, sizeof(node));
    cnt = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        x--, y--;
        addedge(x, y, z);
        addedge(y, x, z);
    }
    int q[maxN], h = -1, t = 0;
    memset(depth, -1, sizeof(depth));
    memset(f, 0, sizeof(f));
    depth[0] = 0;
    q[0] = 0;
    while (h < t)
    {
        h++;
        int x = q[h];
        for (int cur = node[x]; cur != -1; cur = next[cur])
        {
            int v = to[cur];
            if (depth[v] == -1)
            {
                depth[v] = depth[x] + 1;
                f[v][0][0] = x;
                f[v][0][1] = val[cur];
                t++;
                q[t] = v;
            }
        }
    }
    for (int j = 1; j < 17; j++)
        for (int i = 0; i < n; i++)
        {
            f[i][j][0] = f[f[i][j - 1][0]][j - 1][0];
            f[i][j][1] = std::max(f[i][j - 1][1], f[f[i][j - 1][0]][j - 1][1]);
        }
    int q1;
    scanf("%d", &q1);
    while (q1--)
    {
        int x, y, ans = 0;
        scanf("%d%d", &x, &y);
        x--, y--;
        if (depth[x] < depth[y])
            std::swap(x, y);
        for (int j = 16; j != -1; j--)
            if (depth[x] - (1 << j) >= depth[y])
            {
                ans = std::max(ans, f[x][j][1]);
                x = f[x][j][0];
            }
        for (int j = 16; j != -1; j--)
            if (f[x][j][0] != f[y][j][0])
            {
                ans = std::max(ans, f[x][j][1]);
                x = f[x][j][0];
                ans = std::max(ans, f[y][j][1]);
                y = f[y][j][0];
            }
        if (x != y)
        {
            ans = std::max(ans, f[x][0][1]);
            ans = std::max(ans, f[y][0][1]);
        }
        printf("%d\n", ans);
    }
}