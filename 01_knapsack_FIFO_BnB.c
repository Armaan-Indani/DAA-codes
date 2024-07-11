#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

float UB = 0;

struct node
{
    float cost;
    char items[4];
    int item_no;
};

struct node *newNode(char it[4], int it_no)
{
    struct node *node1 = (struct node *)malloc(sizeof(struct node));
    node1->cost = INT_MIN;
    strncpy(node1->items, it, sizeof(node1->items));
    node1->item_no = it_no;
    return node1;
}

struct node *ans;

struct Queue
{
    struct node *n[100];
    int front;
    int back;
};

void enqueue(struct Queue *Q, struct node *node1)
{
    Q->front += 1;
    Q->n[Q->front] = node1;
}

void dequeue(struct Queue *Q)
{
    Q->back += 1;
}

float ub_cost_calc(int n, int m, int p[n], int w[n], struct node *node1)
{
    char s[n];
    strncpy(s, node1->items, sizeof(s));
    int wt = 0;
    float pf = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        if (s[i] == '1')
        {
            if (wt + w[i] <= m)
            {
                wt += w[i];
                pf -= p[i];
            }
            else
            {
                break;
            }
        }
    }

    if (UB > pf)
    {
        UB = pf;
    }
    if (wt < m && i < n)
    {
        float extp = (float)p[i] / w[i];
        pf -= (m - wt) * extp;
    }
    return pf;
}

void addToQueue(int n, int m, struct node *root, struct Queue *Q, int p[n], int w[n])
{
    if (!root)
    {
        return;
    }
    int it_no = root->item_no;
    if (it_no >= n)
    {
        return;
    }
    char it[4];
    strncpy(it, root->items, sizeof(it));

    it[it_no] = '0';

    // Check if cost > UB

    root->cost = ub_cost_calc(n, m, p, w, root);

    if (root->cost > UB)
    {
        return;
    }

    ans = root;

    for (int i = it_no + 1; i < n; i++)
    {
        char it1[4];
        strncpy(it1, root->items, sizeof(it1));
        it1[i] = '0';
        struct node *newN = newNode(it1, i);
        enqueue(Q, newN);
    }
}

int main()
{
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    int p[n], w[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &w[i]);
    }

    struct node *root = newNode("1111", 0);

    struct Queue *Q = (struct Queue *)malloc(sizeof(struct Queue));

    Q->front = -1;
    Q->back = 0;

    enqueue(Q, root);

    while (Q->front >= Q->back)
    {
        addToQueue(n, m, Q->n[Q->back], Q, p, w);
        dequeue(Q);
    }
    int total_profit = 0;
    for (int i = 0; i < n; i++)
    {
        if (ans->items[i] == '1')
        {
            total_profit += p[i];
        }
    }
    printf("Profit =%d\n", total_profit);
    printf("solution = {%c,%c,%c,%c}", ans->items[0], ans->items[1], ans->items[2], ans->items[3]);
}