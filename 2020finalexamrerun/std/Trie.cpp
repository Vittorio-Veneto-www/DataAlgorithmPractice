#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#define MogeKo qwq
#include<queue>
using namespace std;

const int maxn = 1e6+10;
int n,num;
char s[maxn];

struct node {
    int son[26];
    int fin,fail;
    bool vis;
} trie[maxn];

void insert(char *s) {
    int len = strlen(s);
    int u = 0;
    for(int i = 0; i < len; i++) {
        int v = s[i]-'a';
        if(!trie[u].son[v]) trie[u].son[v] = ++num;
        u = trie[u].son[v];
    }
    trie[u].fin++;
}

void getf() {
    queue <int> q;
    for(int i = 0; i < 26; i++) {
        if(trie[0].son[i]) {
            trie[trie[0].son[i]].fail = 0;
            q.push(trie[0].son[i]);
        }
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i = 0; i < 26; i++) {
            if(trie[u].son[i]) {
                trie[trie[u].son[i]].fail = trie[trie[u].fail].son[i];
                q.push(trie[u].son[i]);
            } else
                trie[u].son[i] = trie[trie[u].fail].son[i];
        }
    }
}

int query(char *s) {
    int len = strlen(s);
    int u = 0;
    int ans = 0;
    for(int i = 0; i < len; i++) {
        int v = s[i]-'a';
        u = trie[u].son[v];
        for(int j = u; j && !trie[j].vis; j = trie[j].fail) {
            ans += trie[j].fin;
            trie[j].vis = true;
        }
    }
    return ans;
}

int main() {
    scanf("%d",&n);
    for(int i = 1; i <= n; i++) {
        scanf("%s",s);
        insert(s);
    }
    getf();
    scanf("%s",s);
    printf("%d",query(s));
    return 0;
}