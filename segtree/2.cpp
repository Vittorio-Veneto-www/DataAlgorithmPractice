#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

const int maxN = 100000;
int a[maxN], num[20][maxN], val[20][maxN];

void build(int l, int r, int depth)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1, cnt = mid - l + 1;
    for (int i = l; i <= r; i++)
        cnt -= val[depth][i] < a[mid];
    int t1 = l, t2 = mid + 1;
    for (int i = l ; i <= r; i++)
    {
        if (i == l)
            num[depth][i] = 0;
        else
            num[depth][i] = num[depth][i - 1];
        if (val[depth][i] < a[mid] || ((val[depth][i] == a[mid] && cnt > 0)))
        {
            val[depth + 1][t1++] = val[depth][i];
            num[depth][i]++;
            if (val[depth][i] == a[mid])
                cnt--;
        }
        else
            val[depth + 1][t2++] = val[depth][i];
    }
    build(l, mid, depth + 1);
    build(mid + 1, r, depth + 1);
}

int query(int L, int R, int k, int l, int r, int depth)
{
    if (l == r)
        return val[depth][l];
    int mid = (l + r) >> 1;
    int before = L == l ? 0 : num[depth][L - 1];
    int total = num[depth][R] - before;
    if (total >= k)
        return query(l + before, l + num[depth][R] - 1, k, l, mid, depth + 1);
    else
    {
        int newl = mid + 1 + (L - l - before);
        return query(newl, newl + R - L + 1 - total - 1, k - total, mid + 1, r, depth + 1);
    }
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    memcpy(val[0], a, sizeof(a));
    std::sort(a, a + n);
    build(0, n - 1, 0);
    while (m--)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", query(l - 1, r - 1, k, 0, n - 1, 0));
    }
}