#ifndef TREE_H
#define TREE_H

typedef struct DATA
{
    int info;
    struct DATA *left;
    struct DATA *right;
} Data;

typedef struct TREE
{
    Data *root;
    unsigned int height;
    bool empty;

} Tree;

Data *newNode();
Tree *newTree();
Tree *createTree(Tree *, int *);
Tree *loadTreeFromFile(char *);

//Funções que o professor pediu

// void searchValue(Data *, int, int, int);
void getElement(Data *, int *, int *);
void showTree(Data *);

bool isFull(Data *);
Data *removeValue(Data *, int);
void printInOrder(Data *);
void printPreOrder(Data *);
void printPostOrder(Data *);
int getHeigth(Data *);
Tree *balanceTree(Tree *);

#endif
