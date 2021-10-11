#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

char s[81];
int f1[80], f2[80];

int less(int l1, int r1, int l2, int r2)
{
    char s1[81], s2[81];
    memset(s1, '0', sizeof(s1));
    memset(s2, '0', sizeof(s2));
    s1[80] = 0, s2[80] = 0;
    for (int i = l1; i <= r1; i++)
        s1[79 + i - r1] = s[i];
    for (int i = l2; i <= r2; i++)
        s2[79 + i - r2] = s[i];
    return strcmp(s1, s2) < 0;
}

int main(void)
{
    scanf("%s", s);
    while (strcmp(s, "0"))
    {
        int n = strlen(s);
        for (int i = 0; i < n; i++)
        {
            f1[i] = 0;
            for (int j = i - 1; j >= 0; j--)
                if (less(f1[j], j, j + 1, i))
                {
                    f1[i] = j + 1;
                    break;
                }
        }
        int index = f1[n - 1];
        f2[index] = n - 1;
        while (index && s[index - 1] == '0')
        {
            index--;
            f2[index] = n - 1;
        }
        for (int i = index - 1; i >= 0; i--)
            for (int j = i; j < f1[n - 1]; j++)
                if (less(i, j, j + 1, f2[j + 1]))
                    f2[i] = j;
        int now = 0;
        do
        {
            for (int i = now; i <= f2[now]; i++)
                printf("%c", s[i]);
            now = f2[now] + 1;
            if (now < n)
                printf(",");
        } while (now < n);
        printf("\n");
        scanf("%s", s);
    }
}