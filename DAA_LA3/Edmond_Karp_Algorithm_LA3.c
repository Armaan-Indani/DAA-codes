#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int min(int a, int b)
{
    return a > b ? b : a;
}

struct edge
{
    int capacity;
    int flow;
    int from;
    int to;
};

struct queue
{
    int v[100];
    int front;
    int back;
};

void enqueue(struct queue *Q, int v_no)
{
    Q->front += 1;
    Q->v[Q->front] = v_no;
}

void dequeue(struct queue *Q)
{
    Q->back += 1;
}

struct edge *newE(int cap, int flow, int v1, int v2)
{
    struct edge *e = (struct edge *)malloc(sizeof(struct edge));
    e->capacity = cap;
    e->flow = flow;
    e->from = v1;
    e->to = v2;
    return e;
}

int main()
{
    int n = 6;    // No of vertices
    int n_e = 18; // No of edges

    struct edge *E[18]; // For Residual edges as well
    int ans = 0;

    E[0] = newE(10, 0, 0, 1);  // Normal Edge
    E[1] = newE(0, 0, 1, 0);   // Residual Edge
    E[2] = newE(10, 0, 0, 3);  // Normal Edge
    E[3] = newE(0, 0, 3, 0);   // Residual Edge
    E[4] = newE(4, 0, 1, 2);   // Normal Edge
    E[5] = newE(0, 0, 2, 1);   // Residual Edge
    E[6] = newE(2, 0, 1, 3);   // Normal Edge
    E[7] = newE(0, 0, 3, 1);   // Residual Edge
    E[8] = newE(8, 0, 1, 4);   // Normal Edge
    E[9] = newE(0, 0, 4, 1);   // Residual Edge
    E[10] = newE(10, 0, 2, 5); // Normal Edge
    E[11] = newE(0, 0, 5, 2);  // Residual Edge
    E[12] = newE(9, 0, 3, 4);  // Normal Edge
    E[13] = newE(0, 0, 4, 3);  // Residual Edge
    E[14] = newE(6, 0, 4, 2);  // Normal Edge
    E[15] = newE(0, 0, 2, 4);  // Residual Edge
    E[16] = newE(10, 0, 4, 5); // Normal Edge
    E[17] = newE(0, 0, 5, 4);  // Residual Edge

    int pathAvailable = 1;
    while (pathAvailable == 1)
    {
        int visited[6] = {0};
        int parent[n];
        for (int i = 0; i < n; i++)
        {
            parent[i] = -1;
        }
        struct queue *Q = (struct queue *)malloc(sizeof(struct queue));
        Q->front = -1;
        Q->back = 0;

        enqueue(Q, 0);
        visited[0] = 1;

        while (visited[n - 1] != 1)
        {
            if (Q->front < Q->back)
            {
                pathAvailable = 0;
                break;
            }
            for (int i = 0; i < n_e; i++)
            {
                int currentV = Q->v[Q->back];
                if (E[i]->from == currentV)
                {
                    if (visited[E[i]->to] == 1)
                    {
                        continue;
                    }
                    if (E[i]->capacity - E[i]->flow == 0)
                    {
                        continue;
                    }

                    // printf("Going from vertex %d to %d\n", E[i]->from, E[i]->to);
                    visited[E[i]->to] = 1;
                    enqueue(Q, E[i]->to);
                    parent[E[i]->to] = E[i]->from;
                }
            }
            dequeue(Q);
        }

        // printf("[");
        // for (int i = 0; i < n; i++)
        // {
        //     printf("%d ", visited[i]);
        // }
        // printf("]\n[");
        // for (int i = 0; i < n; i++)
        // {
        //     printf("%d ", parent[i]);
        // }
        // printf("]\n");

        int vert = n - 1;
        int min_cap = INT_MAX;
        // printf("  Path (reversed):\n");
        while (vert != 0)
        {
            if (parent[vert] == -1)
            {
                pathAvailable = 0;
                break;
            }
            int vert2 = parent[vert];
            // printf("    %d-%d ", vert2, vert);
            for (int i = 0; i < 2 * n_e; i++)
            {
                if ((E[i]->from == vert2) && (E[i]->to == vert))
                {
                    min_cap = min(min_cap, E[i]->capacity - E[i]->flow);
                    // printf("\n    {%d %d %d %d}\n", min_cap, E[i]->capacity - E[i]->flow, E[i]->from, E[i]->to);
                    break;
                }
            }
            vert = vert2;
        }

        if (!pathAvailable)
        {
            break;
        }

        // printf("\n  min_cap = %d\n\n", min_cap);
        ans += min_cap;

        vert = n - 1;
        while (vert != 0)
        {
            int vert2 = parent[vert];
            // printf("\n(vert2 = %d)\n", vert2);
            for (int i = 0; 2 * i < n_e - 1; i++)
            {
                // printf("[[2*i = %d]]", 2 * i);
                if ((E[2 * i]->from == vert2) && (E[2 * i]->to == vert) && E[2 * i]->capacity - E[2 * i]->flow >= min_cap)
                {
                    // printf("{%d} ", 2 * i);
                    E[2 * i]->flow += min_cap;     // Forward Edge
                    E[2 * i + 1]->flow -= min_cap; // Residual Edge
                    // printf("\nChanging flow for edge %d,%d\n", E[2 * i]->from, E[2 * i]->to);
                }
            }
            vert = vert2;
        }
    }

    printf("max flow = %d", ans);

    return 0;
}
