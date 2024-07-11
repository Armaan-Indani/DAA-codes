#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node {
    int data;
    char label;
    char alph;
    char hc[10];
    struct Node* left;
    struct Node* right;
};

struct Queue
{
    int front;
    int back;
    struct Node* node[30];
};

struct Node* createNode(int data, char label, char alph)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    node->label = label;
    node->alph = alph;
    node->hc[0] = '\0';
    return node;
}

void sortQ(struct Queue* Q)
{
    for(int i = Q->back; i<=Q->front; i++)
    {
        for(int j=Q->back; j<=Q->front-1; j++)
        {
            if(Q->node[j]->data > Q->node[j+1]->data)
            {
                struct Node* temp = Q->node[j];
                Q->node[j] = Q->node[j+1];
                Q->node[j+1] = temp;
            }
            else if(Q->node[j]->data == Q->node[j+1]->data)
            {
                // printf("    %c - %c\n",Q->node[j]->alph, Q->node[j+1]->alph);
                if(Q->node[j]->alph > Q->node[j+1]->alph)
                {
                    struct Node* temp = Q->node[j];
                    Q->node[j] = Q->node[j+1];
                    Q->node[j+1] = temp;
                }
            }
        }
    }
}

void sortQwithoutLabel(struct Queue* Q)
{
    for(int i = Q->back; i<=Q->front; i++)
    {
        for(int j=Q->back; j<Q->front; j++)
        if(Q->node[j]->data < Q->node[j+1]->data)
        {
            struct Node* temp = Q->node[j];
            Q->node[j] = Q->node[j+1];
            Q->node[j+1] = temp;
        }
    }
}

void inorderHuffman(struct Node* root, char str[10], int len)
{
    if(root == NULL)
    {
        return;
    }
    
    str[len] = '0';
    inorderHuffman(root->left, str, len+1);
    
    for(int i = 0; i<len; i++)
    {
        root->hc[i] = str[i];
    }
    root->hc[len+1] = '\0'; 
    // if(root->label != '~')
    // {
    //     printf("%c-",root->label);
    //     puts(root->hc);
    // }
    str[len] = '1';
    inorderHuffman(root->right, str, len+1);
}

void inorderPrint(struct Node* root, int len)
{
    if(root == NULL)
    {
        return;
    }
    inorderPrint(root->left, len);
    if(root->label != '~' && strlen(root->hc) == len)
    {
        printf("%c-",root->label);
        puts(root->hc);
    }
    inorderPrint(root->right, len);
}

int main()
{
    char str[30];
    fgets(str, 30 ,stdin);
    
    struct Queue* Q = (struct Queue*)malloc(sizeof(struct Queue));
    
    Q->back = 0;
    Q->front = -1;
    
    
    for(int i=0; i<30; i++)
    {
        if(str[i] == '\n' || str[i] == '\0')
        {
            break;
        }
        if(str[i] == ' ')
        {
            continue;
        }
        int found = 0;
        
        for(int j = 0; j<=Q->front; j++)
        {
            if(Q->node[j]->label == str[i])
            {
                found = 1;
                Q->node[j]->data += 1;
                break;
            }
        }
        if(found==0)
        {
            Q->front+=1;
            Q->node[Q->front] = createNode(1,str[i],str[i]);
        }
    }
    
    sortQwithoutLabel(Q);
    
    printf("FREQUENCY OF ALPHABETS\n");
    for(int j = Q->back; j<=Q->front; j++)
    {
        printf("%c-%d\n",Q->node[j]->label,Q->node[j]->data);
    }
    
    while(Q->front - Q->back > 0)
    {
        sortQ(Q);
        struct Node* left = Q->node[Q->back];
        struct Node* right = Q->node[Q->back+1];
        int nd = left->data + right->data;
        
        Q->node[Q->front+1] = createNode(nd, '~', left->alph);
        Q->node[Q->front+1]->left = left;
        Q->node[Q->front+1]->right = right;
        
        Q->back+=2;
        Q->front+=1;
    }
    
    printf("HUFFMAN CODE IS\n");
    
    char temp[10];
    inorderHuffman(Q->node[Q->front], temp, 0);
    
    for(int x = 5; x>0; x--)
    {
        inorderPrint(Q->node[Q->front], x);
    }
}