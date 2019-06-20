#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "tree.h"

#define Dt Data
#define T Tree

int COUNT = 10;

Dt *newNode()
{
    Dt *newNode = (Dt *)malloc(sizeof(Dt));
    if (newNode == NULL)
    {
        printf("Error\n");
        return NULL;
        exit(-1);
    }
    else
        return newNode;
}

T *newTree()
{
    T *newTree = (T *)malloc(sizeof(T));
    if (newTree == NULL)
        return NULL;
    else
        return newTree;
}

void createTree(T **tree, int *n, int size)
{
    int isfull = 0;
    for (int i = 0; i < size; i++)
    {
        Dt *elem = newNode();
        elem->info = *(n + i);
        if ((*tree)->root == NULL)
        {
            elem->right = NULL;
            elem->left = NULL;
            (*tree)->root = elem;
        }
        else if (*(n + i) < (*tree)->root->info)
        {
            if ((*tree)->root->left == NULL)
            {
                (*tree)->root->left = elem;
                elem->right = NULL;
                elem->left = NULL;
            }
            else
            {
                Dt *aux = (*tree)->root->left;
                int j = 3;
                while (1)
                {
                    if (*(n + i) < aux->info)
                    {
                        if (aux->left == NULL)
                        {
                            aux->left = elem;
                            elem->right = NULL;
                            elem->left = NULL;
                            break;
                        }
                        else
                        {
                            aux = aux->left;
                            j++;
                        }
                    }
                    else
                    {
                        if (aux->right == NULL)
                        {
                            aux->right = elem;
                            elem->right = NULL;
                            elem->left = NULL;
                            break;
                        }
                        else
                        {
                            aux = aux->right;
                            j++;
                        }
                    }

                    if (j > (*tree)->height)
                    {
                        (*tree)->height = j;
                        isfull = 0;
                    }
                    if (j == (*tree)->height)
                        isfull++;
                }
            }
        }
        else
        {
            if ((*tree)->root->right == NULL)
            {
                (*tree)->root->right = elem;
                elem->right = NULL;
                elem->left = NULL;
            }
            else
            {
                Dt *aux = (*tree)->root->right;
                int j = 3;
                while (1)
                {
                    if (*(n + i) < aux->info)
                    {
                        if (aux->left == NULL)
                        {
                            aux->left = elem;
                            elem->right = NULL;
                            elem->left = NULL;
                            break;
                        }
                        else
                        {
                            aux = aux->left;
                            j++;
                        }
                    }
                    else
                    {
                        if (aux->right == NULL)
                        {
                            aux->right = elem;
                            elem->right = NULL;
                            elem->left = NULL;
                            break;
                        }
                        else
                        {
                            aux = aux->right;
                            j++;
                        }
                    }
                }

                if (j > (*tree)->height)
                {
                    (*tree)->height = j;
                    isfull = 0;
                }
                if (j == (*tree)->height)
                    isfull++;
            }
        }
    }

    if (pow(2, (*tree)->height - 1) == isfull)
        (*tree)->isFull = true;
    else
        (*tree)->isFull = false;
}

void *loadTreeFromFile(char *fp, T **tree)
{
    int *vector;

    vector = (int *)malloc(1000 * sizeof(int));

    if (tree == NULL)
        return NULL;

    FILE *archive = fopen(fp, "r");

    if (archive == NULL)
        return NULL;

    int number;
    int count = 0;
    do
    {
        fscanf(archive, "%d ", &number);
        vector[count++] = number;

    } while (!feof(archive));
    createTree(tree, vector, count);
    fclose(archive);
    return 0;
}

void printTree(Dt *root, int space)
{
    if (root == NULL)
    {
        return;
    }
    space += COUNT;

    printTree(root->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->info);

    printTree(root->left, space);
}

void isFull(T *tree)
{
    if (tree->isFull)
    {
        printf("Árvore é cheia\n\n");
    }
    else
    {
        printf("Árvore não é cheia\n");
    }
}

void searchValue(Dt *root, int value)
{
    Data *aux = root;
    Data *aux2 = root;
    int knot_level = 1;
    while (aux != NULL)
    {
        if (value == aux->info)
        {
            if (knot_level == 1)
            {
                printf("Nível do nó encontrado: %d\n", knot_level);
                return;
            }
            printf("Nível do nó encontrado: %d\n", knot_level);
            printf("Valor do pai: %d\n", aux2->info);
            if (aux2->info < aux->info)
            {
                if (aux2->left != NULL)
                    printf("Valor do irmão: %d\n", aux2->left->info);
            }
            else if (aux2->info > aux->info)
            {
                if (aux2->right != NULL)
                    printf("Valor do irmão: %d\n", aux2->right->info);
            }
            return;
        }
        else if (value > aux->info)
        {
            aux2 = aux;
            aux = aux->right;
            knot_level++;
        }
        else
        {
            aux2 = aux;
            aux = aux->left;
            knot_level++;
        }
    }
    printf("Valor não encontrado\n\n");
}

void printInOrder(Dt *root)
{
    if (root == NULL)
        return;
    else
    {
        printInOrder(root->left);
        printf("%d ", root->info);
        printInOrder(root->right);
    }
}

void printPostOrder(Dt *root)
{
    if (root == NULL)
        return;
    else
    {
        printPostOrder(root->left);
        printPostOrder(root->right);
        printf("%d ", root->info);
    }
}

void printPreOrder(Dt *root)
{
    if (root == NULL)
        return;
    else
    {
        printf("%d ", root->info);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

void getHeigth(T *tree)
{
    printf("Valor da altura: %u\n", tree->height);
}

void removeValue(Dt *root, int value)
{
    Data *aux = root;
    Data *aux2 = root;

    while (aux != NULL)
    {
        if (value == aux->info)
        {
            //VALOR A SE DELETAR É FOLHA
            if (aux->left == NULL && aux->right == NULL)
            {
                if (aux2->info > aux->info)
                {
                    aux2->left = NULL;
                    free(aux);
                    return;
                }
                else if (aux2->info < aux->info)
                {
                    if (aux2->right != NULL)
                        aux2->right = NULL;
                    free(aux);
                    return;
                }
            }
            else if (aux->left == NULL || aux->right == NULL)
            {
                //VALOR A SE DELETAR TEM SÓ UM FILHO
                printf("Ele só tem um filho!");
                if (aux2->info > aux->info)
                {
                    printf("Ele está à esquerda de seu pai!");
                    if (aux->right == NULL)
                    {
                        aux2->left = aux->left;
                        free(aux);
                    }
                    else
                    {
                        aux2->left = aux->right;
                        free(aux);
                    }
                }
                else
                {
                    printf("Ele está à direita de seu pai!");
                    if (aux->right == NULL)
                    {
                        aux2->right = aux->left;
                        free(aux);
                        return;
                    }
                    else
                    {
                        aux2->right = aux->right;
                        free(aux);
                        return;
                    }
                }
            }
            else
            {
                //REMOÇÃO PARA UM VALOR COM DOIS FILHOS
                Data *aux3 = aux->right;
                aux2 = aux;
                while (aux3 != NULL)
                {
                    if (aux3->right == NULL && aux3->left == NULL)
                    {

                        aux->info = aux3->info;
                        if (aux2->info > aux3->info)
                        {
                            aux2->left = NULL;
                            free(aux3);
                        }
                        else
                        {
                            aux2->right = NULL;
                            free(aux3);
                        }
                        break;
                    }
                    else
                    {
                        aux2 = aux3;
                        aux3 = aux3->left;
                    }
                }
                return;
            }
        }
        else if (value > aux->info)
        {
            aux2 = aux;
            aux = aux->right;
        }
        else
        {
            aux2 = aux;
            aux = aux->left;
        }
    }
    printf("Valor a ser removido não encontrado!\n");
}

Dt *rightRotation(Dt *avo, Dt *pai, Dt *filho)
{

    if(avo != NULL)
        avo->right = filho; 

    pai->left = filho->right; 
    filho->right = pai; 

    return filho;
}


Dt *leftRotation(Dt *avo, Dt *pai, Dt *filho, Dt *root)
{
    filho->left = pai;
    pai->right = NULL;

    if (avo != NULL)
    {
        if(avo->left == pai)
            avo->left = filho; 
        else
            avo->right = filho;

    }
    if (pai == root)
        root = filho;

    return root;
}

T *linearizarElementos(T *tree)
{
    Dt *avo, *pai;

    while (tree->root->left != NULL)
        tree->root = rightRotation(NULL, tree->root, tree->root->left);

    avo = tree->root;
    pai = tree->root->right;

    while (pai->right != NULL)
    {
        avo = tree->root;
        pai = tree->root->right;

        while ((pai->left == NULL) && (pai->right !=NULL)) {
            avo = avo->right;
            pai = pai->right;
        }

        while(pai->left != NULL)
        {
            pai = rightRotation(avo, pai, pai->left);
        }
    }
    return tree;
}

T *balanceTree(T* tree)
{
    Dt *avo, *pai, *filho;
    if(tree == NULL)
    {
        printf("Error, cannot allocate memory!\n");
        return NULL;
    }
    else
    {

        tree = linearizarElementos(tree); 

        while(!isBalanced(tree->root))
        {
            avo = tree->root; 
            pai = tree->root; 
            filho = tree->root;
            if (pai != NULL)
                filho = pai->right; 

            if (filho != NULL)
                tree->root = leftRotation(NULL, pai, filho, tree->root);

            avo = pai; 
            pai = filho; 
            filho = pai->right; 

            while((pai != NULL) && !isBalanced(tree->root)) 
            {
                avo = pai; 
                pai = filho; 

                if (pai != NULL)
                    filho = pai->right; 

                if(filho != NULL)
                    tree->root = leftRotation(avo, pai, filho, tree->root);


                avo = pai;
                pai = filho;

                if (pai != NULL)
                    filho = pai->right;

            }
        }
    }
    return tree;
}

int isBalanced(Dt *root)
{
    if(root == NULL) return 1; 
    else
    {
        if(abs(getHeight(root->right) - getHeight(root->left)) > 1)
        {
            return 0; 
        }
        else{
            if(isBalanced(root->right)&&isBalanced(root->left))
            {
                return 1; 
            }
            else
                return 0; 
        }
    }
}

int getHeight(Dt *t)
{
    if(t == NULL)
    {
        return -1;
    }
    else
    {
        return 1 + max(getHeight(t->left), getHeight(t->right));
    }
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}


