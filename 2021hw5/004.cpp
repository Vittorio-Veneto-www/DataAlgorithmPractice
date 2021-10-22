#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int next[1001][4], prev[1001], mark[1001], f[1001][1001];

int main()
{
    int n, T = 0;
    scanf("%d", &n);
    while (n)
    {
        T++;
        memset(next, 0, sizeof(next));
        memset(prev, 0, sizeof(prev));
        memset(mark, 0, sizeof(mark));
        int cnt = 2;
        for (int i = 0; i < n; i++)
        {
            char s[21];
            scanf("%s", s);
            int cur = 1;
            for (int i = 0; s[i]; i++)
            {
                if (s[i] == 'A')
                    s[i] = 0;
                else if (s[i] == 'T')
                    s[i] = 1;
                else if (s[i] == 'G')
                    s[i] = 2;
                else if (s[i] == 'C')
                    s[i] = 3;
                int& x = next[cur][s[i]];
                if (!x)
                {
                    x = cnt;
                    cnt++;
                }
                cur = x;
            }
            mark[cur] = 1;
        }
        int q[1000], h = -1, t = 0;
        q[0] = 1;
        for (int i = 0; i < 4; i++)
            next[0][i] = 1;
        prev[0] = 0;
        prev[1] = 0;
        while (h < t)
        {
            h++;
            int x = q[h];
            for (int i = 0; i < 4; i++)
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
        memset(f, 0x7f, sizeof(f));
        char s[1001];
        scanf("%s", s);
        f[0][1] = 0;
        int len = strlen(s);
        for (int i = 0; i < len; i++)
        {
            if (s[i] == 'A')
                s[i] = 0;
            else if (s[i] == 'T')
                s[i] = 1;
            else if (s[i] == 'G')
                s[i] = 2;
            else if (s[i] == 'C')
                s[i] = 3;
            for (int j = 1; j < cnt; j++)
                if (!mark[j])
                    for (int k = 0; k < 4; k++)
                        {
                            int cur = j;
                            while (!next[cur][k])
                                cur = prev[cur];
                            cur = next[cur][k];
                            if (!mark[cur])
                                f[i + 1][cur] = std::min(f[i + 1][cur], f[i][j] + (k != s[i]));
                        }
        }
        int ans = 0x7fffffff;
        for (int i = 1; i < cnt; i++)
            ans = std::min(ans, f[len][i]);
        if (ans != 0x7f7f7f7f)
            printf("Case %d: %d\n", T, ans);
        else
            printf("Case %d: -1\n", T);
        scanf("%d", &n);
    }
}