#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int parent[50000], rank[50000];

int GetRoot(int x)
{
    if (parent[x] == x)
        return x;
    int fa = parent[x];
    parent[x] = GetRoot(parent[x]);
    rank[x] = (rank[x] + rank[fa]) % 2;
    return parent[x];
}

int Merge(int x, int y)
{
    int p1 = GetRoot(x), p2 = GetRoot(y);
    if (p1 == p2)
        if (rank[x] == 0)
            return rank[y] == 1;
        else
            return rank[y] == 0;
    parent[p1] = p2;
    rank[p1] = (rank[y] - rank[x] + 2 + 1) % 2;
    return 1;
}

int main(void)
{
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        for (int i = 0; i < n; i++)
            parent[i] = i, rank[i] = 0;
        int cnt = 0;
        for (int i = 0; i < k; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x > n || y > n || x == y)
            {
                cnt++;
                continue;
            }
            x--, y--;
            cnt += !Merge(x, y);
        }
        printf("Scenario #%d:\n%s\n\n", t + 1, cnt ? "Suspicious bugs found!" : "No suspicious bugs found!");
    }
}