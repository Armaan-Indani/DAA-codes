#include <stdio.h>
#include <limits.h>
#include <float.h>

struct point
{
    int x;
    int y;
};

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
    int val = (curr.y - prev.y) * (curr.x - next.x) - (curr.x - prev.x) * (curr.y - next.y);

    if (val == 0)
    {
        return val;
    }
    return (val > 0) ? 1 : -1;
}

int main()
{
    int n = 8;
    struct point p[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    int s = 0;

    // Finding start point
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
    swap(&p[0], &p[s]);
    int border[n];
    border[0] = 0;

    int bd_index;
    for (int i = 0; i < n; i++)
    {
        if (i != 0 && border[i] == 0)
        {
            bd_index = i;
            break;
        }
        int prev = border[i];
        int next = 1;
        for (int j = 0; j < n; j++)
        {
            if (orientation(p[prev], p[next], p[j]) == -1)
            {
                next = j;
            }
        }
        border[i + 1] = next;
    }
    printf("Boundary points of convex hull are:\n");
    for (int i = bd_index - 1; i > 0; i--)
    {
        printf("%d %d\n", p[border[i]].x, p[border[i]].y);
    }
    printf("%d %d\n", p[border[0]].x, p[border[0]].y);
    return 0;
}