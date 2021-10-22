#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define maxN 250
#define maxLen 1000
#define maxLenDest 5100000

int next[maxN * maxLen * 2 + 1][26], prev[maxN * maxLen * 2 + 1], id[maxN * maxLen * 2 + 1], num[maxN];
bool mark[maxN * maxLen * 2 + 1], vis[maxN * maxLen * 2 + 1];
char s[maxLenDest + 1], temp[maxLenDest + 1], s1[maxN][maxLen + 1];

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, cnt;
        scanf("%d", &n);
        memset(next, 0, sizeof(next));
        memset(prev, 0, sizeof(prev));
        memset(mark, 0, sizeof(mark));
        memset(vis, 0, sizeof(vis));
        memset(id, 0, sizeof(id));
        memset(num, 0, sizeof(num));
        cnt = 2;
        for (int i = 0; i < n; i++)
            scanf("%s", s1[i]);
        for (int i = 0; i < n; i++)
        {
            char* s = s1[i];
            int cur = 1;
            for (int i = 0; s[i]; i++)
            {
                int& x = next[cur][s[i] - 'A'];
                if (!x)
                {
                    x = cnt;
                    cnt++;
                }
                cur = x;
            }
            mark[cur] = 1;
            id[cur] = i + 1;
        }
        for (int i = 0; i < n; i++)
        {
            char* s = s1[i];
            int cur = 1;
            for (int i = strlen(s) - 1; i != -1; i--)
            {
                int& x = next[cur][s[i] - 'A'];
                if (!x)
                {
                    x = cnt;
                    cnt++;
                }
                cur = x;
            }
            mark[cur] = 1;
            id[cur] = i + 1;
        }
        int q[maxN * maxLen * 2], h = -1, t = 0;
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
        scanf("%s", temp);
        int len = 0;
        for (int i = 0; temp[i]; i++)
            if (temp[i] != '[')
                s[len++] = temp[i];
            else
            {
                i++;
                int x = 0;
                while ('0' <= temp[i] && temp[i] <= '9')
                    x = x * 10 + temp[i] - '0', i++;
                memset(s + len, temp[i], x);
                len += x;
                i++;
            }
        s[len] = 0;
        int cur = 1;
        for (int i = 0; s[i]; i++)
        {
            while (!next[cur][s[i] - 'A'])
                cur = prev[cur];
            cur = next[cur][s[i] - 'A'];
            if (mark[cur])
            {
                int tmp = cur;
                while (prev[tmp] && !vis[tmp])
                {
                    vis[tmp] = 1;
                    if (id[tmp])
                        num[id[tmp] - 1] = 1;
                    tmp = prev[tmp];
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++)
            ans += num[i];
        printf("%d\n", ans);
    }
}