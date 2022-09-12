/*
ID: LinKArftc
PROG: 3180.cpp
LANG: C++
*/

#include <map>
#include <set>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
#include <cstdio>
#include <string>
#include <utility>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define eps 1e-8
#define randin srand((unsigned int)time(NULL))
#define input freopen("input.txt","r",stdin)
#define debug(s) cout << "s = " << s << endl;
#define outstars cout << "*************" << endl;
const double PI = acos(-1.0);
const double e = exp(1.0);
const int inf = 0x3f3f3f3f;
const int INF = 0x7fffffff;
typedef long long ll;

const int maxn = 500010;
const int maxm = 500010;

struct Edge {
    int v, next;
} edge[maxm];

int head[maxn], tot;

void init() {
    tot = 0;
    memset(head, -1, sizeof(head));
}

void addedge(int u, int v) {
    edge[tot].v = v;
    edge[tot].next = head[u];
    head[u] = tot ++;
}

int n, m;
int dfn[maxn], low[maxn];
bool ins[maxn];
int scc, Time;
stack <int> st;
vector <int> vec[maxn];

void tarjan(int u) {
    int v;
    dfn[u] = low[u] = ++ Time;
    st.push(u);
    ins[u] = true;
    for (int i = head[u]; i + 1; i = edge[i].next) {
        v = edge[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[v], low[u]);
        } else if (ins[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {//刚开始写成dfn[u] == low[v]了
        scc ++;
        do {
            v = st.top();
            st.pop();
            ins[v] = false;
            vec[scc].push_back(v);
        } while (u != v);
    }
}

int main() {

    //input;
    int u, v;
    while (~scanf("%d %d", &n, &m)) {
        init();
        for (int i = 1; i <= m; i ++) {//刚开始写成i<=n了
            scanf("%d %d", &u, &v);
            addedge(u, v);
        }
        memset(dfn, 0, sizeof(dfn));
        memset(ins, 0, sizeof(ins));
        while (!st.empty()) st.pop();
        for (int i = 1; i <= n; i ++) vec[i].clear();
        scc = 0;
        Time = 0;
        for (int i = 1; i <= n; i ++) {
            if (!dfn[i]) tarjan(i);
        }
        int ans = 0;
        for (int i = 1; i <= scc; i ++) {
            ans=max((int)vec[i].size(),ans);
        }
        printf("%d\n%d\n", ans,scc);
    }

    return 0;
}
