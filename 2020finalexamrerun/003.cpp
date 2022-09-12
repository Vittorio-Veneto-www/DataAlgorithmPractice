#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

#define maxN 1000
#define maxM 10000

int to[maxM], from[maxM], val[maxM], dis[maxN];

int main(void)
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        to[i] = y - 1;
        from[i] = x - 1;
        val[i] = z;
    }
    for (int i = 0; i < n; i++)
        dis[i] = 1e9;
    dis[0] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (dis[from[j]] + val[j] < dis[to[j]])
                dis[to[j]] = dis[from[j]] + val[j];
    int mark = 0;
    for (int j = 0; j < m; j++)
        if (dis[from[j]] + val[j] < dis[to[j]])
            mark = 1;
    if (mark)
        printf("GG\n");
    else
        printf("%d", dis[n - 1]);
}