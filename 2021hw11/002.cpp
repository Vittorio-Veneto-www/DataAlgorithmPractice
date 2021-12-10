#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int equal(double x, double y)
{
    if (fabs(x - y) < 1e-6)
        return 1;
    else
        return 0;
}

int cross(double x, double y, double x1, double y1, double x2, double y2)
{
    double a = (x2 - x1) * (y - y1) - (y2 - y1) * (x - x1);
    if (equal(a, 0))
        return 0;
    else if (a > 0)
        return 1;
    else
        return -1;
}

int main(void)
{
    int n;
    double a[15][2];
    scanf("%d", &n);
    while (n)
    {
        for (int i = 0; i < n; i++)
            scanf("%*[^0-9]%lf%lf", &a[i][0], &a[i][1]);
        double max = 0;
        int ix, jx, kx;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++)
                {
                    int flag = 1;
                    for (int t = 0; t < n; t++)
                        if (t != i && t != j && t != k)
                        {
                            int num[3] = {0};
                            num[cross(a[t][0], a[t][1], a[i][0], a[i][1], a[j][0], a[j][1]) + 1]++;
                            num[cross(a[t][0], a[t][1], a[j][0], a[j][1], a[k][0], a[k][1]) + 1]++;
                            num[cross(a[t][0], a[t][1], a[k][0], a[k][1], a[i][0], a[i][1]) + 1]++;
                            if (!(num[0] && num[2]))
                            {
                                flag = 0;
                                break;
                            }
                        }
                    if (flag)
                    {
                        double area = abs((a[j][0] - a[i][0]) * (a[k][1] - a[i][1]) - (a[j][1] - a[i][1]) * (a[k][0] - a[i][0]));
                        if (max < area)
                        {
                            max = area;
                            ix = i, jx = j, kx = k;
                        }
                    }
                }
        printf("%c%c%c\n", 'A' + ix, 'A' + jx, 'A' + kx);
        scanf("%d", &n);
    }
}