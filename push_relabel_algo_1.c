#include <stdio.h>
#include <stdlib.h>

int min(int a, int b)
{
    return a > b ? b : a;
}

struct edge
{
    int src;
    int dest;
    int flow;
    int cap;
};

struct edge *newEdge(int s, int d, int f, int c)
{
    struct edge *e = (struct edge *)malloc(sizeof(struct edge));
    e->src = s;
    e->dest = d;
    e->flow = f;
    e->cap = c;

    return e;
}

int getVert(char c)
{
    switch (c)
    {
    case 'S':
        return 0;
        break;
    case 'A':
        return 1;
        break;
    case 'B':
        return 2;
        break;
    case 'C':
        return 3;
        break;
    case 'D':
        return 4;
        break;
    case 'T':
        return 5;
        break;

    default:
        return -1;
        break;
    }
    return -1;
}

int main()
{
    int n_v = 6;
    int n_e = 8;

    struct edge *E[n_e];

    E[0] = newEdge(0, 1, 0, 13);
    E[1] = newEdge(0, 2, 0, 10);
    E[2] = newEdge(1, 3, 0, 6);
    E[3] = newEdge(1, 5, 0, 7);
    E[4] = newEdge(2, 1, 0, 3);
    E[5] = newEdge(3, 4, 0, 10);
    E[6] = newEdge(4, 5, 0, 5);

    // for (int i = 0; i < n_e; i++)
    // {
    //     char src, dest;
    //     int cap;
    //     scanf("%c%c", &src, &dest);
    //     scanf("%d", &cap);
    //     getchar();
    //     int s = getVert(src);
    //     int d = getVert(dest);

    //     // printf("New Edge: %c(%d) to %c(%d) - cap = %d\n", src, s, dest, d, cap);
    //     E[i] = newEdge(s, d, 0, cap);
    // }

    int ht[6] = {0};
    int ov[6] = {0};

    ht[0] = n_v;

    for (int i = 0; i < n_e; i++)
    {
        if (E[i]->src == 0)
        {
            E[i]->flow = E[i]->cap;
            ov[E[i]->dest] = E[i]->cap;
        }
    }
    int sum_of_overflows = 1;
    while (sum_of_overflows > 0)
    {
        for (int v = 1; v < n_v - 1; v++)
        {
            if (ov[v] > 0)
            {
                // printf("{%d, %d, %d}\n", v, ov[v], ht[v]);
                
                // Only forward edges
                for (int e = 0; e < n_e; e++)
                {
                    if (E[e]->src == v && E[e]->cap > E[e]->flow && ht[E[e]->src] > ht[E[e]->dest])
                    {
                        int f1 = min(ov[v], E[e]->cap - E[e]->flow);
                        E[e]->flow += f1;
                        ov[v] -= f1;
                        ov[E[e]->dest] += f1;
                        // printf("Forward flow of %d to %d increased from %d to %d\n", E[e]->src, E[e]->dest, E[e]->flow - f1, E[e]->flow);
                    }
                }

                // Only backward edges
                for (int e = 0; e < n_e; e++)
                {
                    if (E[e]->dest == v && E[e]->flow > 0 && ht[E[e]->dest] > ht[E[e]->src])
                    {
                        int f1 = min(ov[v], E[e]->flow);
                        E[e]->flow -= f1;
                        ov[v] -= f1;
                        ov[E[e]->src] += f1;
                        // printf("Forward flow of %d to %d decreased from %d to %d\n", E[e]->src, E[e]->dest, E[e]->flow + f1, E[e]->flow);
                    }
                }
                if (ov[v] == 0)
                {
                    // printf("    Vertex %d has overflow 0\n", v);
                    continue;
                }
                else if (ov[v] > 0)
                {
                    ht[v]++;
                    v = 0;
                    continue;
                }
            }
        }
        sum_of_overflows = 0;
        for (int i = 1; i < n_v - 1; i++)
        {
            sum_of_overflows += ov[i];
        }
    }

    printf("AH= %d\n", ht[1]);
    printf("BH= %d\n", ht[2]);
    printf("CH= %d\n", ht[3]);
    printf("DH= %d\n", ht[4]);

    printf("Max Flow is = %d", ov[n_v - 1]);
    return 0;
}