#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int min(int a, int b)
{
    return a > b ? b : a;
}

struct vertex
{
    char type;
    int no;
};

struct edge
{
    int capacity;
    int flow;
    int from;
    int to;
};

struct vertex *newV(char t, int no)
{
    struct vertex *v = (struct vertex *)malloc(sizeof(struct vertex));
    v->type = t;
    v->no = no;
    return v;
}

struct queue
{
    // struct vertex *v[100];
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
    int n = 9; // No of vertices

    struct vertex *V[9];
    struct edge *E[32]; // For Residual edges as well
    int ans = 0;

    // Create Vertices
    V[0] = newV('s', 0);
    // printf("Vertex %d of type '%c' created\n", V[0]->no, V[0]->type);
    for (int i = 1; i < n - 1; i++)
    {
        V[i] = newV('v', i);
        // printf("Vertex %d of type '%c' created\n", V[i]->no, V[i]->type);
    }
    V[n - 1] = newV('t', n - 1);
    // printf("Vertex %d of type '%c' created\n", V[n - 1]->no, V[n - 1]->type);

    E[0] = newE(26, 0, 0, 1);  // Normal Edge
    E[1] = newE(0, 0, 1, 0);   // Residual Edge
    E[2] = newE(17, 0, 0, 2);  // Normal Edge
    E[3] = newE(0, 0, 2, 0);   // Residual Edge
    E[4] = newE(37, 0, 0, 4);  // Normal Edge
    E[5] = newE(0, 0, 4, 0);   // Residual Edge
    E[6] = newE(20, 0, 1, 3);  // Normal Edge
    E[7] = newE(0, 0, 3, 1);   // Residual Edge
    E[8] = newE(10, 0, 1, 4);  // Normal Edge
    E[9] = newE(0, 0, 4, 1);   // Residual Edge
    E[10] = newE(20, 0, 2, 4); // Normal Edge
    E[11] = newE(0, 0, 4, 2);  // Residual Edge
    E[12] = newE(15, 0, 2, 5); // Normal Edge
    E[13] = newE(0, 0, 5, 2);  // Residual Edge
    E[14] = newE(10, 0, 3, 5); // Normal Edge
    E[15] = newE(0, 0, 5, 3);  // Residual Edge
    E[16] = newE(22, 0, 3, 6); // Normal Edge
    E[17] = newE(0, 0, 6, 3);  // Residual Edge
    E[18] = newE(18, 0, 3, 7); // Normal Edge
    E[19] = newE(0, 0, 7, 3);  // Residual Edge
    E[20] = newE(35, 0, 4, 3); // Normal Edge
    E[21] = newE(0, 0, 3, 4);  // Residual Edge
    E[22] = newE(15, 0, 4, 5); // Normal Edge
    E[23] = newE(0, 0, 5, 4);  // Residual Edge
    E[24] = newE(34, 0, 5, 7); // Normal Edge
    E[25] = newE(0, 0, 7, 5);  // Residual Edge
    E[26] = newE(48, 0, 6, 8); // Normal Edge
    E[27] = newE(0, 0, 8, 6);  // Residual Edge
    E[28] = newE(20, 0, 7, 6); // Normal Edge
    E[29] = newE(0, 0, 6, 7);  // Residual Edge
    E[30] = newE(30, 0, 7, 8); // Normal Edge
    E[31] = newE(0, 0, 8, 7);  // Residual Edge

    int pathAvailable = 1;
    while (pathAvailable == 1)
    {
        int visited[9] = {0};
        int parent[9];
        for (int i = 0; i < 9; i++)
        {
            parent[i] = -1;
        }
        struct queue *Q = (struct queue *)malloc(sizeof(struct queue));
        Q->front = -1;
        Q->back = 0;

        enqueue(Q, 0);
        visited[0] = 1;

        // printf("\n");

        while (visited[8] != 1)
        {
            if (Q->front < Q->back)
            {
                pathAvailable = 0;
                break;
            }
            for (int i = 0; i < 32; i++)
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

                    visited[E[i]->to] = 1;
                    enqueue(Q, E[i]->to);
                    parent[E[i]->to] = E[i]->from;
                }
            }
            dequeue(Q);
        }

        int vert = 8;
        int min_cap = INT_MAX;
        while (vert != 0)
        {
            if (parent[vert] == -1)
            {
                pathAvailable = 0;
                break;
            }
            int vert2 = parent[vert];
            for (int i = 0; i < 16; i++)
            {
                if ((E[2 * i]->from == vert2) && (E[2 * i]->to == vert))
                {
                    min_cap = min(min_cap, E[2 * i]->capacity - E[2 * i]->flow);
                    break;
                }
            }
            vert = vert2;
        }

        if (!pathAvailable)
        {
            break;
        }

        ans += min_cap;

        vert = 8;
        while (vert != 0)
        {
            int vert2 = parent[vert];
            for (int i = 0; i < 16; i++)
            {
                if ((E[2 * i]->from == vert2) && (E[2 * i]->to == vert) && E[2 * i]->capacity - E[2 * i]->flow >= min_cap)
                {
                    E[2 * i]->flow += min_cap;     // Forward Edge
                    E[2 * i + 1]->flow -= min_cap; // Residual Edge
                }
            }
            vert = vert2;
        }
    }

    printf("max flow = %d", ans);

    return 0;
}
