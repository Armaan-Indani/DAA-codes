#include <stdio.h>

struct point
{
    int x;
    int y;
};

float slope(struct point a, struct point b)
{
    return ((float)(a.y - b.y)) / (a.x - b.x);
}

void swap(struct point *p1, struct point *p2)
{
    int x = p1->x;
    int y = p1->y;
    p1->x = p2->x;
    p1->y = p2->y;
    p2->x = x;
    p2->y = y;
}

int dist(struct point p1, struct point p2)
{
    return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
}

int crossprod(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return (x1-x3)*(y2-y3) - (x2-x3)*(y1-y3);
}

int main()
{
    int n = 8;
    struct point p[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &p[i].x, &p[i].y);
    }

    // printf("%f\n", slope(p[0], p[1]));

    struct point border[n];

    for (int i = 1; i < n; i++)
    {
        if (p[0].x > p[i].x)
        {
            swap(&p[0], &p[i]);
        }
        else if (p[0].x == p[i].x && p[0].y > p[1].y)
        {
            swap(&p[0], &p[i]);
        }
    }

    int n2 = n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < n - i - 1; j++)
        {
            if (slope(p[j], p[0]) > slope(p[j + 1], p[0]))
            {
                swap(&p[j], &p[j + 1]);
            }
            if(slope(p[j], p[0]) == slope(p[j+1], p[0]))
            {
                if(dist(p[j+1], p[0]) > dist(p[j], p[0]))
                {
                    swap(&p[j], &p[j+1]);
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("(%d, %d)\n", p[i].x, p[i].y);
    }



    return 0;
}