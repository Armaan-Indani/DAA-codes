#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

struct point
{
    int x;
    int y;
};

int crossProd(struct point l1_p1, struct point l1_p2, struct point l2_p1, struct point l2_p2)
{
    int cp = (l1_p2.x - l1_p1.x) * (l2_p2.y - l2_p1.y) - (l1_p2.y - l1_p1.y) * (l2_p2.x - l2_p1.x);
    return cp;
}

int main()
{
    struct point p1, p2, p3, p4;

    scanf("%d%d", &p1.x, &p1.y);
    scanf("%d%d", &p2.x, &p2.y);
    scanf("%d%d", &p3.x, &p3.y);
    scanf("%d%d", &p4.x, &p4.y);

    // Line like 'X'
    if ((crossProd(p3, p1, p3, p4) * crossProd(p3, p2, p3, p4) < 0) && (crossProd(p1, p4, p1, p2) * crossProd(p1, p3, p1, p2) < 0))
    {
        printf("The line segments intersect\n");
    }

    // P1 or P2 are collinear with P3 and P4
    else if ((crossProd(p3, p1, p3, p4) * crossProd(p3, p2, p3, p4) == 0) && (crossProd(p1, p4, p1, p2) * crossProd(p1, p3, p1, p2) != 0))
    {
        // p1 is collinear with p3, p4
        if (crossProd(p3, p1, p3, p4) == 0)
        {
            // p1 lies between p3, p4
            if (max(p3.x, p4.x) > p1.x && p1.x > min(p3.x, p4.x))
            {
                printf("The line segments intersect\n");
            }
            else
            {
                printf("The line segments does not intersect");
            }
        }

        // p2 is collinear with p3, p4
        else if (crossProd(p3, p2, p3, p4) == 0)
        {
            // p2 lies between p3, p4
            if (max(p3.x, p4.x) > p2.x && p2.x > min(p3.x, p4.x))
            {
                printf("The line segments intersect\n");
            }
            else
            {
                printf("The line segments does not intersect");
            }
        }
    }

    // P3 or P4 are collinear with P1 and P2
    else if ((crossProd(p3, p1, p3, p4) * crossProd(p3, p2, p3, p4) != 0) && (crossProd(p1, p4, p1, p2) * crossProd(p1, p3, p1, p2) == 0))
    {
        // p4 is collinear with p1, p2
        if (crossProd(p1, p4, p1, p2) == 0)
        {
            // p4 lies between p1, p2
            if (max(p1.x, p2.x) > p4.x && p4.x > min(p1.x, p2.x))
            {
                printf("The line segments intersect\n");
            }
            else
            {
                printf("The line segments does not intersect");
            }
        }

        // p3 is collinear with p1, p2
        else if (crossProd(p1, p3, p1, p2) == 0)
        {
            // p3 lies between p1, p2
            if (max(p1.x, p2.x) > p3.x && p3.x > min(p1.x, p2.x))
            {
                printf("The line segments intersect\n");
            }
            else
            {
                printf("The line segments does not intersect");
            }
        }
    }

    // Lines are collinear (can be intersectiong or non-intersecting)
    else if ((crossProd(p3, p1, p3, p4) * crossProd(p3, p2, p3, p4) == 0) && (crossProd(p1, p4, p1, p2) * crossProd(p1, p3, p1, p2) == 0))
    {
        if ((max(p1.x, p2.x) > p3.x && p3.x > min(p1.x, p2.x)) || (max(p1.x, p2.x) > p4.x && p4.x > min(p1.x, p2.x)))
        {
            printf("The line segments intersect\n");
        }
        else if ((max(p3.x, p4.x) > p1.x && p1.x > min(p3.x, p4.x)))
        {
            printf("The line segments intersect\n");
        }
    }
    else
    {
        printf("The line segments does not intersect");
    }

    return 0;
}