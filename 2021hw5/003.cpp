#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int next[30001][2], prev[30001], mark[30001], vis[30001];

int dfs(int x)
{
    if (vis[x])
        return 1;
    vis[x] = 1;
    for (int i = 0; i < 2; i++)
    {
        int child = next[x][i];
        if (!child)
        {
            int pre = prev[x];
            while (!next[pre][i])
                pre = prev[pre];
            child = next[pre][i];
        }
        if (!mark[child])
            if (dfs(child))
                return 1;
    }
    vis[x] = 0;
    return 0;
}

int main()
{
    int n, cnt;
    scanf("%d", &n);
    memset(next, 0, sizeof(next));
    memset(prev, 0, sizeof(prev));
    memset(mark, 0, sizeof(mark));
    memset(vis, 0, sizeof(vis));
    cnt = 2;
    for (int i = 0; i < n; i++)
    {
        char s[30001];
        scanf("%s", s);
        int cur = 1;
        for (int i = 0; s[i]; i++)
        {
            int& x = next[cur][s[i] - '0'];
            if (!x)
            {
                x = cnt;
                cnt++;
            }
            cur = x;
        }
        mark[cur] = 1;
    }
    int q[30001], h = -1, t = 0;
    q[0] = 1;
    for (int i = 0; i < 2; i++)
        next[0][i] = 1;
    prev[0] = 0;
    prev[1] = 0;
    while (h < t)
    {
        h++;
        int x = q[h];
        for (int i = 0; i < 2; i++)
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
    printf(dfs(1) ? "TAK" : "NIE");
}