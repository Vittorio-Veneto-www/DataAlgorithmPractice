#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

typedef struct{
    int x, y, index;
} data;

data d[100001];

int n = 100001, a[100002], cnt[100000];

int lowbit(int x)
{
    return x & -x;
}

int query(int x)
{
    int ans = 0;
    while (x)
    {
        ans += a[x];
        x -= lowbit(x);
    }
    return ans;
}

void update(int x, int dx)
{
    while (x <= n)
    {
        a[x] += dx;
        x += lowbit(x);
    }
}

int cmp(const data &a, const data &b)
{
    return a.x < b.x || (a.x == b.x && a.y > b.y);
}

int main(void)
{
    int m;
    scanf("%d", &m);
    while (m)
    {
        memset(a, 0, sizeof(a));
        for (int i = 0; i < m; i++)
            scanf("%d%d", &d[i].x, &d[i].y), d[i].index = i;
        std::sort(d, d + m, cmp);
        int num = 1;
        cnt[d[0].index] = 0;
        for (int i = 1; i < m; i++)
        {
            if (d[i].x == d[i - 1].x && d[i].y == d[i - 1].y)
                num++;
            else
                update(d[i - 1].y + 1, num), num = 1;
            cnt[d[i].index] = query(n) - query(d[i].y);
        }
        int mark = 0;
        for (int i = 0; i < m; i++)
        {
            if (mark)
                printf(" ");
            mark = 1;
            printf("%d", cnt[i]);
        }
        printf("\n");
        scanf("%d", &m);
    }
}