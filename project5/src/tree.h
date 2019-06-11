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
    bool isFull;

} Tree;

Data *newNode();
Tree *newTree();
void createTree(Tree **, int *);
Tree *loadTreeFromFile(char *);

//Funções que o professor pediu

 void searchValue(Data *, int);
void getElement(Data *, int *, int *);
void showTree(Data *);

void isFull(Tree *);
void removeValue(Data *, int);
void printInOrder(Data *);
void printPreOrder(Data *);
void printPostOrder(Data *);
void getHeigth(Tree *);
Tree *balanceTree(Tree *);
void printTree(Data* ,int);

#endif
