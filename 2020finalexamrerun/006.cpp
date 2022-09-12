//此题内存限制过紧

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int next[1000001][26], prev[1000001], mark[1000001], q[1000001];
char s[1000001];
bool vis[1000001];

int main(void)
{
    int n, cnt;
    scanf("%d", &n);
    memset(next, 0, sizeof(next));
    memset(prev, 0, sizeof(prev));
    memset(mark, 0, sizeof(mark));
    memset(vis, 0, sizeof(vis));
    cnt = 2;
    while (n--)
    {
        scanf("%s", &s);
        int x = 1;
        for (int i = 0; s[i]; i++)
            if (next[x][s[i] - 'a'])
                x = next[x][s[i] - 'a'];
            else
                x = next[x][s[i] - 'a'] = cnt++;
        mark[x]++;
    }
    for (int i = 0; i < 26; i++)
        next[0][i] = 1;
    prev[1] = 0;
    int h = -1, t = 0;
    q[0] = 1;
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
                t++;
                q[t] = child;
            }
        }
    }
    scanf("%s", s);
    int cur = 1, ans = 0;
    for (int i = 0; s[i]; i++)
    {
        while (!next[cur][s[i] - 'a'])
            cur = prev[cur];
        cur = next[cur][s[i] - 'a'];
        for (int j = cur; j && !vis[j]; j = prev[j])
        {
            vis[j] = 1;
            ans += mark[j];
        }
    }
    printf("%d\n", ans);
}