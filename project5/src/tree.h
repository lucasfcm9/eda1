#ifndef TREE_H
#define TREE_H

typedef struct _TREE
{
    int dt;
    struct _TREE *left;
    struct _TREE *right;
} Tree;

Tree *loadTreeFromFile(const char *);
void showTree(Tree *);
bool isFull(Tree *);
int searchValue(Tree *, int);
int getHeigth(Tree *);
void removeValue(Tree *, int);
void printInOrder(Tree *);
void printPreOrder(Tree *);
void printPostOrder(Tree *);
void balanceTree(Tree *);

#endif