#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"

#define Dt Data
#define T Tree

Dt *newNode()
{
    Dt *newNode = (Dt *)calloc(1, sizeof(Dt));
    if(newNode == NULL)
        return NULL;
    else
        return newNode;
}

T *newTree()
{
    T *newTree = (T *)calloc(1, sizeof(T));
    if(newTree == NULL)
        return NULL;
    else
        return newTree;
}

T *createTree(T *tree, int *n)
{
    T *element = newTree();
    if(element == NULL) //Se a árvore não foi alocada
        return NULL;

    //Raíz nula
    if(tree->root == NULL)
    {
        tree->root = newNode();
    if(tree->root == NULL)
        return NULL'

    tree->root->info = *n;
    return tree;
    }
    else //Caso a raíz não seja nula;
    {
        if(*n > tree->root->info)
        {
            element->root = tree->root->right;
            element = createTree(element, n);
            tree->root->right = element->root;
            return tree;
        } //Se n(Valor) for maior que a raiz(O valor vai para a direita)
        else
        {
            element->root = tree->root->left;
            element = createTree(element, n);
            tree->root->left = element->root;
            return tree; //Caso ao contrário, o valor vai para a esquerda
        }
    }
}

T *loadTreeFromFile(char *fp)
{
    T *tree;
    tree = newTree();

    if(tree == NULL)
        return NULL;

    FILE *fp = fopen(fp, "r");

    if(fp == NULL)
        return NULL;
}
