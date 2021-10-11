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
    rank[x] = (rank[x] + rank[fa]) % 3;
    return parent[x];
}

int Merge(int d, int x, int y)
{
    int p1 = GetRoot(x), p2 = GetRoot(y);
    if (p1 == p2)
    {
        if (d == 1 && rank[x] != rank[y])
            return 0;
        if (d == 2)
        {
            if (rank[x] == 0)
                return rank[y] == 2;
            if (rank[x] == 1)
                return rank[y] == 0;
            if (rank[x] == 2)
                return rank[y] == 1;
        }
    }
    parent[p1] = p2;
    if (d == 2)
        rank[p1] = (rank[y] - rank[x] + 3 + 1) % 3;
    else
        rank[p1] = (rank[y] - rank[x] + 3) % 3;
    return 1;
}

int main(void)
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
        parent[i] = i, rank[i] = 0;
    int cnt = 0;
    for (int i = 0; i < k; i++)
    {
        int d, x, y;
        scanf("%d%d%d", &d, &x, &y);
        if (x > n || y > n || (d == 2 && x == y))
        {
            cnt++;
            continue;
        }
        x--, y--;
        cnt += !Merge(d, x, y);
    }
    printf("%d", cnt);
}