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
    int operator<(Point const &p)
    {
        if (equal(x, p.x))
            if (!equal(y, p.y))
                return y < p.y;
            else
                return 0;
        else
            return x < p.x;
    }
};

int cross(Point p, Point p1, Point p2)
{
    double a = (p2.x - p1.x) * (p.y - p2.y) - (p2.y - p1.y) * (p.x - p2.x);
    if (equal(a, 0))
        return 0;
    else if (a > 0)
        return 1;
    else
        return -1;
}

double length(double x, double y)
{
    return sqrt(x * x + y * y);
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        Point a[1000];
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &a[i].x, &a[i].y);
        if (n < 6)
        {
            //可能只有一两个点，此时不可能有答案，但是按下面的判断条件没有排除
            printf("NO\n");
            continue;
        }
        std::sort(a, a + n);
        std::vector<Point> stack;
        stack.push_back(a[0]);
        stack.push_back(a[1]);
        for (int i = 2; i < n; i++)
        {
            while (stack.size() > 1)
            {
                Point p2 = *(stack.end() - 1);
                Point p1 = *(stack.end() - 2);
                if (cross(a[i], p1, p2) < 0)
                    stack.pop_back();
                else
                    break;
            }
            stack.push_back(a[i]);
        }
        int size = stack.size();
        stack.push_back(a[n - 2]);
        for (int i = n - 3; i >= 0; i--)
        {
            while (stack.size() > size)
            {
                Point p2 = *(stack.end() - 1);
                Point p1 = *(stack.end() - 2);
                if (cross(a[i], p1, p2) < 0)
                    stack.pop_back();
                else
                    break;
            }
            stack.push_back(a[i]);
        }
        stack.push_back(stack[1]);
        int last = 0, mark = 1;
        for (int i = 2; i < stack.size(); i++)
            if (!equal(cross(stack[last], stack[last + 1], stack[i]), 0))
            {
                if (i == last + 2)
                    mark = 0;
                last = i - 1;
            }
        if (mark)
            printf("YES\n");
        else
            printf("NO\n");
    }
}