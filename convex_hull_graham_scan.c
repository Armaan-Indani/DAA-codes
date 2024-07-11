#include <stdio.h>
#include <limits.h>
#include <float.h>
struct point
{
    int x;
    int y;
};

float slope(struct point p1, struct point p2)
{
    if (p1.x == p2.x)
    {
        if (p1.y < p2.y)
        {
            return FLT_MAX;
        }
        else
        {
            return FLT_MIN;
        }
    }
    float t = (float)(p1.y - p2.y) / (p1.x - p2.x);
    return t;
}

void swap(struct point *p1, struct point *p2)
{
    int temp_x = p1->x;
    int temp_y = p1->y;

    p1->x = p2->x;
    p1->y = p2->y;

    p2->x = temp_x;
    p2->y = temp_y;
}

int orientation(struct point prev, struct point curr, struct point next)
{
    int val = (curr.y - prev.y) * (next.x - curr.x) - (curr.x - prev.x) * (next.y - curr.y);
    return (val > 0) ? 1 : ((val < 0) ? -1 : 0);
}

int main()
{
    int n = 8;
    struct point p[n + 1];
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    int s = 0;
    for (int i = 0; i < n; i++)
    {
        if (p[i].x < p[s].x)
        {
            s = i;
        }
        else if (p[i].x == p[s].x && p[i].y < p[s].y)
        {
            s = i;
        }
    }

    // Starting point at 0 index in array
    struct point temp1 = p[0];
    p[0] = p[s];
    p[s] = temp1;

    // Arrange points in increasing order of slope
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 1; j < n - i - 1; j++)
        {
            if (slope(p[0], p[j]) > slope(p[0], p[j + 1]))
            {
                swap(&p[j], &p[j + 1]);
            }
        }
    }

    p[n] = p[0];
    int border[n];

    border[0] = 0;
    int bd_index = 1;

    int prev = 0, curr = 1, next = 2;

    while (next < n + 1)
    {
        if (orientation(p[prev], p[curr], p[next]) == -1 || orientation(p[prev], p[curr], p[next]) == 0) // i.e. c is accepted
        {
            printf("{%d %d %d} Point %d - [%d %d] accepted %d\n", prev, curr, next, curr, p[curr].x, p[curr].y, bd_index);
            border[bd_index] = curr;
            bd_index++;
            prev = curr;
            curr = next;
            next = next + 1;
            continue;
        }
        else if (orientation(p[prev], p[curr], p[next]) == 1) // i.e. c is rejected
        {
            printf("{%d %d %d} Point %d - [%d %d] rejected\n", prev, curr, next, curr, p[curr].x, p[curr].y);
            curr = prev;
            bd_index--;
            prev = border[bd_index - 1];
        }
        printf("%d %d %d <%d>\n", prev, curr, next, orientation(p[prev], p[curr], p[next]));
    }

    printf("The Boundary Coordinates are\n");
    for (int i = 1; i < bd_index; i++)
    {
        printf("%d %d\n", p[border[i]].x, p[border[i]].y);
    }
    printf("%d %d\n", p[border[0]].x, p[border[0]].y);
    return 0;
}