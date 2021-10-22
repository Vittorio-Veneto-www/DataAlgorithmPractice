#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int next[120001][26], prev[120001], mark[120001];

int main()
{
    int n, cnt;
    scanf("%d", &n);
    memset(next, 0, sizeof(next));
    memset(prev, 0, sizeof(prev));
    memset(mark, 0, sizeof(mark));
    cnt = 2;
    for (int i = 0; i < n; i++)
    {
        char s[121];
        scanf("%s", s);
        int cur = 1;
        for (int i = 0; s[i]; i++)
        {
            int& x = next[cur][s[i] - 'a'];
            if (!x)
            {
                x = cnt;
                cnt++;
            }
            cur = x;
        }
        mark[cur] = 1;
    }
    int q[120000], h = -1, t = 0;
    q[0] = 1;
    for (int i = 0; i < 26; i++)
        next[0][i] = 1;
    prev[0] = 0;
    prev[1] = 0;
    while (h < t)
    {
        h++;
        int x = q[h];
        for (int i = 0; i < 26; i++)
        {
            int child = next[x][i];
            if (child)
            {
                int pre = prev[x];
                while (!next[pre][i])
                    pre = prev[pre];
                prev[child] = next[pre][i];
                if (mark[prev[child]])
                    mark[child] = 1;
                t++;
                q[t] = child;
            }
        }
    }
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        char s[1001];
        scanf("%s", s);
        int cur = 1;
        for (int i = 0; s[i]; i++)
        {
            while (!next[cur][s[i] - 'a'])
                cur = prev[cur];
            cur = next[cur][s[i] - 'a'];
            if (mark[cur])
                break;
        }
        printf(mark[cur] ? "YES\n" : "NO\n");
    }
}