#include <vector>
#include <algorithm>
#include <deque>
#include <cstring>
#include <cstdio>
#define INFINITE 999999999
int G[900][900];
bool Visited[900];
int Layer[900]; //Layer[i]是节点i的层号
int n, m;       //1是源点，m是汇点
bool CountLayer()
{ //分层
    int layer = 0;
    std::deque<int> q;
    memset(Layer, 0xff, sizeof(Layer)); //都初始化成-1
    Layer[1] = 0;
    q.push_back(1);
    while (!q.empty())
    {
        int v = q.front();
        q.pop_front();
        for (int j = 1; j <= m; j++)
        {
            if (G[v][j] > 0 && Layer[j] == -1)
            {
                //Layer[j] == -1 说明j还没有访问过
                Layer[j] = Layer[v] + 1;
                if (j == m)
                    return true; //分层到汇点即可
                else
                    q.push_back(j);
            }
        }
    }
    return false;
}
int Dinic()
{
    int i;
    int s;
    int nMaxFlow = 0;
    std::deque<int> q; //DFS用的栈
    while (CountLayer())
    {                   //只要能分层
        q.push_back(1); //源点入栈
        memset(Visited, 0, sizeof(Visited));
        Visited[1] = 1;
        while (!q.empty())
        {
            int nd = q.back();
            if (nd == m)
            { // nd是汇点
                //在栈中找容量最小边
                int nMinC = INFINITE;
                int nMinC_vs; //容量最小边的起点
                for (i = 1; i < q.size(); i++)
                {
                    int vs = q[i - 1];
                    int ve = q[i];
                    if (G[vs][ve] > 0)
                    {
                        if (nMinC > G[vs][ve])
                        {
                            nMinC = G[vs][ve];
                            nMinC_vs = vs;
                        }
                    }
                }
                //增广，改图
                nMaxFlow += nMinC;
                for (i = 1; i < q.size(); i++)
                {
                    int vs = q[i - 1];
                    int ve = q[i];
                    G[vs][ve] -= nMinC; //修改边容量
                    G[ve][vs] += nMinC; //添加反向边
                }
                //退栈到 nMinC_vs成为栈顶，以便继续dfs
                while (!q.empty() && q.back() != nMinC_vs)
                {
                    Visited[q.back()] = 0;
                    q.pop_back();
                }
            }
            else
            { //nd不是汇点
                for (i = 1; i <= m; i++)
                {
                    if (G[nd][i] > 0 && Layer[i] == Layer[nd] + 1 &&
                        !Visited[i])
                    {
                        //只往下一层的没有走过的节点走
                        Visited[i] = 1;
                        q.push_back(i);
                        break;
                    }
                }
                if (i > m)        //找不到下一个点
                    q.pop_back(); //回溯
            }
        }
    }
    return nMaxFlow;
}
int main()
{
    int r, c, d, n = 0;
    memset(G, 0, sizeof(G));
    scanf("%d%d%d", &r, &c, &d);
    char s[50];
    m = r * c * 2 + 2;
    for (int i = 0; i < r; i++)
    {
        scanf("%s", s);
        for (int j = 0; j < c; j++)
        {
            int ord = i * c + j;
            G[ord * 2 + 2][ord * 2 + 3] = s[j] - '0';
        }
    }
    for (int i = 0; i < r; i++)
    {
        scanf("%s", s);
        for (int j = 0; j < c; j++)
        {
            int ord = i * c + j;
            if (s[j] == 'L')
                G[1][ord * 2 + 2] = 1, n++;
        }
    }
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
        {
            int ord = i * c + j;
            for (int k = -d; k <= d; k++)
                for (int l = -d; l <= d; l++)
                    if ((k || l) && abs(k) + abs(l) <= d)
                    {
                        int x = i + k, y = j + l;
                        if (x < 0 || x >= r || y < 0 || y >= c)
                            G[ord * 2 + 3][m] = INFINITE;
                        else
                            G[ord * 2 + 3][(x * c + y) * 2 + 2] = INFINITE;
                    }
        }
    printf("%d", n - Dinic());
    return 0;
}