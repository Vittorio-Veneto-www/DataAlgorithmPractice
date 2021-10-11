#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int parent[50000];

int GetRoot(int x)
{
    if (parent[x] == x)
        return x;
    else
        return parent[x] = GetRoot(parent[x]);
}

void Merge(int x, int y)
{
    int p1 = GetRoot(x), p2 = GetRoot(y);
    if (p1 == p2)
        return;
    parent[p2] = p1;
}

int main(void)
{
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF)
    {
        for (int i = 0; i < n; i++)
            parent[i] = i;
        for (int i = 0; i < m; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            x--, y--;
            if (GetRoot(x) == GetRoot(y))
                printf("Yes\n");
            else
                Merge(x, y), printf("No\n");
        }
        int cnt = 0;
        for (int i = 0; i < n; i++)
            cnt += parent[i] == i;
        printf("%d\n", cnt);
        int mark = 0;
        for (int i = 0; i < n; i++)
            if (parent[i] == i)
            {
                if (mark)
                    printf(" ");
                mark = 1;
                printf("%d", i + 1);
            }
        printf("\n");
    }
}