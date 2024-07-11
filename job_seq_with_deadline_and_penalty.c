#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

int UB = INT_MAX;

struct node
{
    int cost;
    char jobs[4];
    int job_no;
};

struct node *ans;

struct Queue
{
    int front;
    int back;
    struct node *n[100];
};

void enqueue(struct Queue *Q, struct node *n)
{
    Q->front += 1;
    Q->n[Q->front] = n;
}

void dequeue(struct Queue *Q)
{
    Q->back += 1;
}

struct node *newNode(char j[4], int jn)
{
    struct node *node1 = (struct node *)malloc(sizeof(struct node));
    node1->cost = 0;
    strncpy(node1->jobs, j, sizeof(node1->jobs));
    node1->job_no = jn;
    return node1;
}

void addToQueue(int n, struct node *root, struct Queue *Q, int penalty[n], int deadline[n], int time[n])
{
    if (!root)
    {
        return;
    }
    int jn = root->job_no;
    if (jn >= n)
    {
        return;
    }
    char j[4];
    int local_ub = 0;
    strncpy(j, root->jobs, sizeof(j));

    j[jn] = '1';

    int total_time = 0;
    for (int i = 0; i < n; i++)
    {
        if (j[i] == '1')
        {
            total_time += time[i];
        }
    }
    int possible = 0;
    for (int i = 0; i < n; i++)
    {
        if (j[i] == '1')
        {
            if (total_time <= deadline[i])
            {
                possible = 1;
                break;
            }
        }
    }
    if (!possible)
    {
        return;
    }

    for (int i = 0; i < jn; i++)
    {
        if (j[i] == '0')
        {
            root->cost += penalty[i];
            local_ub += penalty[i];
        }
    }
    for (int i = jn + 1; i < n; i++)
    {
        local_ub += penalty[i];
    }

    UB = local_ub > UB ? UB : local_ub;

    if (root->cost > UB)
    {
        return;
    }

    ans = root;

    for (int i = jn + 1; i < n; i++)
    {
        char j1[4];
        strncpy(j1, root->jobs, sizeof(j1));
        j1[i] = '1';
        struct node *newN = newNode(j1, i);
        enqueue(Q, newN);
    }
}

int main()
{
    int n = 4;
    int penalty[4] = {5, 10, 6, 3};
    int deadline[4] = {1, 3, 2, 1};
    int time[4] = {1, 2, 1, 1};

    struct Queue *Q = (struct Queue *)malloc(sizeof(struct Queue));
    Q->front = -1;
    Q->back = 0;
    struct node *root = newNode("0000", 0);
    enqueue(Q, root);

    while (Q->front >= Q->back)
    {
        addToQueue(n, Q->n[Q->back], Q, penalty, deadline, time);
        Q->back++;
    }

    printf("Cost = %d\n", ans->cost);
    printf("Upper Bound = %d\n", UB);
    printf("Jobs Completed within deadline are ");

    int first = 1;
    for (int i = 0; i < n; i++)
    {
        if (ans->jobs[i] == '1')
        {
            if (first)
            {
                first = 0;
                printf("J%d ", i + 1);
            }
            else
            {
                printf("and J%d ", i + 1);
            }
        }
    }
    return 0;
}