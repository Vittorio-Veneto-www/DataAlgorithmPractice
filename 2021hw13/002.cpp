#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

const int MAXN = 4000 * 250;
int wa[MAXN], wb[MAXN], wv[MAXN], Ws[MAXN]; //辅助数组
//注意，wv和Ws的元素个数应该同时超过字符串的字符种类数和字符串的长度
int sa[MAXN]; //sa[i]是名次为i的后缀的位置
void BuildSA(const int *s, int sa[], int n, int m)
{
    int i, j, p, *pm = wa, *k2sa = wb, *t;
    for (i = 0; i < m; i++)
        Ws[i] = 0;
    for (i = 0; i < n; i++)
        Ws[pm[i] = s[i]]++;
    for (i = 1; i < m; i++)
        Ws[i] += Ws[i - 1];
    for (i = n - 1; i >= 0; i--)
        sa[--Ws[pm[i]]] = i;
    for (j = p = 1; p < n; j <<= 1, m = p)
    {
        for (p = 0, i = n - j; i < n; i++)
            k2sa[p++] = i;
        for (i = 0; i < n; i++)
            if (sa[i] >= j)
                k2sa[p++] = sa[i] - j;
        for (i = 0; i < m; i++)
            Ws[i] = 0;
        for (i = 0; i < n; i++)
            Ws[wv[i] = pm[k2sa[i]]]++;
        for (i = 1; i < m; i++)
            Ws[i] += Ws[i - 1];
        for (i = n - 1; i >= 0; i--)
            sa[--Ws[wv[i]]] = k2sa[i];
        for (t = pm, pm = k2sa, k2sa = t, pm[sa[0]] = 0, p = i = 1; i < n; i++)
        {
            int a = sa[i - 1], b = sa[i];
            if (k2sa[a] == k2sa[b] && a + j < n && b + j < n && k2sa[a + j] == k2sa[b + j])
                pm[sa[i]] = p - 1;
            else
                pm[sa[i]] = p++;
        }
    }
    return;
}

int height[MAXN], Rank[MAXN];

void BuildHeight(int *str, int n, int *sa, int *Rank)
{
    int i, j, k;
    for (int i = 0; i < n; ++i) //i 是名次,n是字符串长度
        Rank[sa[i]] = i;
    height[0] = 0;
    for (i = k = 0; i < n - 1; height[Rank[i++]] = k) //i是位置
        for (k ? k-- : 0, j = sa[Rank[i] - 1];        //Rank[0]>0才不越界
             str[i + k] == str[j + k]; k++)
            ;
    //k相当于是 H[i]; height[Rank[i]] =  H[i] ;
}

int a[2][MAXN];

int main(void)
{
    char s[100001];
    int cur = 0;
    scanf("%s", s);
    for (int j = 0; s[j]; j++)
        a[0][cur] = s[j], a[1][cur] = 0, cur++;
    a[0][cur] = 256, cur++;
    scanf("%s", s);
    for (int j = 0; s[j]; j++)
        a[0][cur] = s[j], a[1][cur] = 1, cur++;
    a[0][cur] = 0;
    BuildSA(a[0], sa, cur + 1, 257);
    BuildHeight(a[0], cur + 1, sa, Rank);
    int max = 0;
    for (int i = 0; i < cur + 1; i++)
        if (height[i] > max && a[1][sa[i]] != a[1][sa[i - 1]])
            max = height[i];
    printf("%d\n", max);
}