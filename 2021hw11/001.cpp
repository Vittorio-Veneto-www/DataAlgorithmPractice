#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int equal(double x, double y)
{
    if (abs(x - y) < 1e-6)
        return 1;
    else
        return 0;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    printf("INTERSECTING LINES OUTPUT\n");
    while (n--)
    {
        double x11, y11, x12, y12, x21, y21, x22, y22;
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &x11, &y11, &x12, &y12, &x21, &y21, &x22, &y22);
        double a1 = y12 - y11, b1 = x11 - x12, a2 = y22 - y21, b2 = x21 - x22;
        double c1 = a1 * x11 + b1 * y11, c2 = a2 * x21 + b2 * y21;
        if (equal(a1 * b2, a2 * b1))
        {
            if (equal(a1 * c2 - a2 * c1, 0) && equal(b1 * c2 - b2 * c1, 0))
                printf("LINE\n");
            else
                printf("NONE\n");
            continue;
        }
        printf("POINT %.2lf %.2lf\n", (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1), (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1));
    }
    printf("END OF OUTPUT\n");
}