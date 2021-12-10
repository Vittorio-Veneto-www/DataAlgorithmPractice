#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

class Point
{
public:
    double x, y;
    Point(){};
    Point(double x, double y):x(x), y(y){};
};

int equal(double x, double y)
{
    if (fabs(x - y) < 1e-6)
        return 1;
    else
        return 0;
}

int leq(double x, double y)
{
    if (fabs(x - y) < 1e-6)
        return 1;
    else
        return x < y;
}

int intersect(double x11, double y11, double x12, double y12, double x21, double y21, double x22, double y22)
{
    double a1 = y12 - y11, b1 = x11 - x12, a2 = y22 - y21, b2 = x21 - x22;
    double c1 = a1 * x11 + b1 * y11, c2 = a2 * x21 + b2 * y21;
    if (equal(a1 * b2, a2 * b1))
        return 0;
    double x = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1), y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
    if (equal(x11, x12))
        return leq(y11, y) == leq(y, y12);
    else
        return leq(x11, x) == leq(x, x12);
}

Point intersect1(double x11, double y11, double x12, double y12, double x21, double y21, double x22, double y22)
{
    double a1 = y12 - y11, b1 = x11 - x12, a2 = y22 - y21, b2 = x21 - x22;
    double c1 = a1 * x11 + b1 * y11, c2 = a2 * x21 + b2 * y21;
    return Point((c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1), (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1));
}

int main(void)
{
    int n;
    double a[20][2];
    scanf("%d", &n);
    while (n)
    {
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &a[i][0], &a[i][1]);
        double max = -1e100;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j)
                {
                    int k = 0;
                    while (k < n && intersect(a[k][0], a[k][1], a[k][0], a[k][1] + 1, a[i][0], a[i][1], a[j][0], a[j][1] + 1))
                        k++;
                    if (k == n)
                    {
                        max = 1e100;
                        continue;
                    }
                    if (!k)
                        continue;
                    auto p1 = intersect1(a[k - 1][0], a[k - 1][1], a[k][0], a[k][1], a[i][0], a[i][1], a[j][0], a[j][1] + 1),
                     p2 = intersect1(a[k - 1][0], a[k - 1][1] + 1, a[k][0], a[k][1] + 1, a[i][0], a[i][1], a[j][0], a[j][1] + 1);
                    if (leq(a[k - 1][0], p1.x) == leq(p1.x, a[k][0]))
                        max = std::max(max, p1.x);
                    if (leq(a[k - 1][0], p2.x) == leq(p2.x, a[k][0]))
                        max = std::max(max, p2.x);
                }
        if (max == 1e100)
            printf("Through all the pipe.\n");
        else
            printf("%.2lf\n", max);
        scanf("%d", &n);
    }
}