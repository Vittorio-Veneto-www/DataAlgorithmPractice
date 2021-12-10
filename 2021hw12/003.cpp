#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

int equal(double x, double y)
{
    if (fabs(x - y) < 1e-6)
        return 1;
    else
        return 0;
}

class Point
{
public:
    double x, y;
    Point(){}
    Point(double x, double y):x(x), y(y){}
    int operator<=(Point const &p)
    {
        if (equal(x, p.x))
            if (!equal(y, p.y))
                return y < p.y;
            else
                return 1;
        else
            return x < p.x;
    }
};

std::pair<int, Point> intersect(Point p11, Point p12, Point p21, Point p22, double delta)
{
    double a1 = p12.y - p11.y, b1 = p11.x - p12.x, a2 = p22.y - p21.y, b2 = p21.x - p22.x;
    double c1 = a1 * p11.x + b1 * p11.y, c2 = a2 * p21.x + b2 * p21.y;
    if (equal(a1 * b2, a2 * b1))
        return std::make_pair(0, Point());
    c2 -= delta * sqrt(a2 * a2 + b2 * b2);
    Point p((c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1), (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1));
    return std::make_pair((p11 <= p) == (p <= p12), p);
}

int cross(Point p, Point p1, Point p2, double delta)
{
    double a = p2.y - p1.y, b = p1.x - p2.x;
    double c = a * p1.x + b * p1.y - delta * sqrt(a * a + b * b), c1 = c - (a * p.x + b * p.y);
    if (equal(c1, 0))
        return 0;
    else if (c1 > 0)
        return 1;
    else
        return -1;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    while (n)
    {
        Point a[100];
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &a[i].x, &a[i].y);
        double l = 0, r = 20000, mid;
        while (r - l > 1e-6)
        {
            mid = (l + r) / 2;
            std::vector<Point> b, c;
            for (int i = 0; i < n; i++)
                b.push_back(a[i]);
            for (int i = 0; i < n; i++)
            {
                int i1 = (i + 1) % n;
                c.clear();
                for (int j = 0; j < b.size(); j++)
                {
                    if (cross(b[j], a[i], a[i1], mid) == 1)
                        c.push_back(b[j]);
                    auto x = intersect(b[j], b[(j + 1) % b.size()], a[i], a[i1], mid);
                    if (x.first == 1)
                        c.push_back(x.second);
                }
                std::swap(b, c);
            }
            if (b.size())
                l = mid;
            else
                r = mid;
        }
        printf("%.6lf\n", l);
        scanf("%d", &n);
    }
}