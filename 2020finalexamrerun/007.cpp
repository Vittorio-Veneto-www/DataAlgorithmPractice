#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

const int MAXN = 200010;
int wa[MAXN], wb[MAXN], wv[MAXN], Ws[MAXN]; //辅助数组
//注意，wv和Ws的元素个数应该同时超过字符串的字符种类数和字符串的长度
int sa[MAXN]; //sa[i]是名次为i的后缀的位置
void BuildSA(const char *s, int sa[], int n, int m)
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

int main(void)
{
	char s[MAXN], s1[MAXN];
	scanf("%s", s);
	int n = strlen(s);
	for (int i = 0; i < n; i++)
		s[i + n] = s[i];
	s[n * 2] = 0;
	BuildSA(s, sa, n * 2 + 1, 256);
	int cnt = 0;
	for (int i = 1; i <= n * 2; i++)
		if (sa[i] < n)
			s1[cnt++] = s[sa[i] + n - 1];
	s1[n] = 0;
	printf("%s", s1);
}