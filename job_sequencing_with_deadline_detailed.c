#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

struct node
{
    char jobs[5];
    int index;
};

struct node *createNode(int index, char jobs[4])
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->index = index;
    strncpy(newNode->jobs, jobs, 4);

    return newNode;
}

struct queue
{
    int front;
    int back;
    struct node *n[20];
};

int main()
{
    int P[4] = {5, 10, 6, 3};
    int D[4] = {1, 3, 2, 1};
    int T[4] = {1, 2, 1, 1};

    char solution[4];
    strncpy(solution, "0000", 4);

    struct queue *Q = (struct queue *)malloc(sizeof(struct queue));
    Q->front = -1;
    Q->back = 0;
    int globalUB = INT_MAX;

    struct node *root = createNode(0, "0000");

    printf("Root: ");
    printf("%c%c%c%c\n", root->jobs[0], root->jobs[1], root->jobs[2], root->jobs[3]);

    Q->front++;
    Q->n[Q->front] = root;

    while (Q->back <= Q->front)
    {

        struct node *currentNode = Q->n[Q->back];
        printf("CURRENT NODE IS: ");
        printf("%c%c%c%c\n", currentNode->jobs[0], currentNode->jobs[1], currentNode->jobs[2], currentNode->jobs[3]);
        int curr_ub = 0;
        int cost = 0;
        for (int i = 0; i < 4; i++)
        {
            if (currentNode->jobs[i] == '0')
            {
                curr_ub += P[i];
            }
            if (i < currentNode->index && currentNode->jobs[i] == '0')
            {
                cost += P[i];
            }
        }

        // Check if node is valid
        // int is_valid = 1;
        int total_time = 0;
        int max_deadline = 0;
        for (int i = 0; i < 4; i++)
        {
            if (currentNode->jobs[i] == '1')
            {
                total_time += T[i];
                max_deadline = max(max_deadline, D[i]);
            }
        }

        printf("Total time for currentNode is %d\n", total_time);

        if (total_time <= max_deadline && cost <= globalUB)
        {
            printf("\nFor %c%c%c%c total time(%d) <= max_deadline(%d)\n", currentNode->jobs[0], currentNode->jobs[1], currentNode->jobs[2], currentNode->jobs[3], total_time, max_deadline);
            for (int i = currentNode->index + 1; i <= 4; i++)
            {
                char jb[4];
                strncpy(jb, currentNode->jobs, 4);
                jb[i - 1] = '1';

                struct node *newNode = createNode(i, jb);

                Q->front++;
                Q->n[Q->front] = newNode;
                printf("Enqueuing: ");
                printf("%c%c%c%c\n", Q->n[Q->front]->jobs[0], Q->n[Q->front]->jobs[1], Q->n[Q->front]->jobs[2], Q->n[Q->front]->jobs[3]);
            }

            if (globalUB > curr_ub)
            {
                printf("Global UB updated from %d to %d\n", globalUB, curr_ub);
                globalUB = curr_ub;
                strncpy(solution, currentNode->jobs, 4);
            }
        }
        else
        {
            printf("\n%c%c%c%c is invalid", currentNode->jobs[0], currentNode->jobs[1], currentNode->jobs[2], currentNode->jobs[3]);
            if (cost > globalUB)
            {
                printf(" due to cost exceeded, cost = %d, globalUB = %d\n", cost, globalUB);
            }
            else
            {
                printf(" as not within deadline\n");
            }
        }

        Q->back++;
    }

    printf("Solution is: ");
    printf("{%c, %c, %c, %c}", solution[0], solution[1], solution[2], solution[3]);
    return 0;
}