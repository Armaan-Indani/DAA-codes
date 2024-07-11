#include <stdio.h>
#include <stdlib.h>

int random_no(int a, int b)
{
    int x = b - a > 0 ? b - a : 1;
    return rand() % x + a;
}

struct edge
{
    int v1;
    int v2;
};

void swap(struct edge *e1, struct edge *e2)
{
    struct edge e;
    e.v1 = e1->v1;
    e.v2 = e1->v2;

    e1->v1 = e2->v1;
    e1->v2 = e2->v2;

    e2->v1 = e.v1;
    e2->v2 = e.v2;
}

struct edge *newEdge(int v1, int v2)
{
    struct edge *e = (struct edge *)malloc(sizeof(struct edge));
    e->v1 = v1;
    e->v2 = v2;
    return e;
}

int removeSelfLoop(int n_e, struct edge *E[n_e])
{
    int n_pe = 0;
    for (int i = 0; i < n_e - n_pe; i++)
    {
        if (E[i]->v1 == E[i]->v2)
        {
            swap(E[i], E[n_e - 1 - n_pe]);
            n_pe++;
            i--;
        }
    }
    return n_e - n_pe;
}

int no_of_vert_is_2(int n_e, struct edge *E[n_e])
{
    int arr[2] = {-1, -1};
    for (int i = 0; i < n_e; i++)
    {
        if (E[i]->v1 == arr[0] || E[i]->v2 == arr[1])
        {
            continue;
        }
        else if (arr[0] == -1)
        {
            arr[0] = E[i]->v1;
        }
        else if (arr[1] == -1)
        {
            arr[1] = E[i]->v1;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int n_e = 5;
    struct edge *E[5];
    E[0] = newEdge(0, 1);
    E[1] = newEdge(0, 2);
    E[2] = newEdge(0, 3);
    E[3] = newEdge(1, 3);
    E[4] = newEdge(2, 3);

    struct edge *ce = E[0];
    printf("Contracting edge %d-%d\n", ce->v1, ce->v2);
    int a = ce->v1, b = ce->v2;
    for (int i = 0; i < n_e; i++)
    {
        if (E[i]->v1 == a)
        {
            E[i]->v1 = b;
        }
        else if (E[i]->v2 == a)
        {
            E[i]->v2 = b;
        }
    }
    n_e = removeSelfLoop(n_e, E);

    ce = E[3];
    printf("Contracting edge %d-%d\n", ce->v1, ce->v2);
    for (int i = 0; i < n_e; i++)
    {
        if (E[i]->v1 == ce->v1)
        {
            E[i]->v1 = ce->v2;
        }
        else if (E[i]->v2 == ce->v1)
        {
            E[i]->v2 = ce->v2;
        }
    }
    ce->v1 = ce->v2;
    n_e = removeSelfLoop(n_e, E);

    if (no_of_vert_is_2(n_e, E) == 1)
    {
        printf("Cut found by the randomized algorithm is %d", n_e);
    }
    return 0;
}