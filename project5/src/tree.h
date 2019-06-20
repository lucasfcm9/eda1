/*
 - Alunos: Lucas Fellipe Carvalho Moreira && Pedro Henrique Queiroz Miranda && Gabriel Davi Silva Pereira
 - Matrículas: 16/0133394 && 15/0144474 && 17/0010341
 - Disciplina: Estruturas de Dados 1
 - Professor: Mateus Mendelson
 */
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
void createTree(Tree **, int *, int);
void *loadTreeFromFile(char *, Tree **);

void searchValue(Data *, int);
void getElement(Data *, int *, int *);
void showTree(Data *);
void whiteSpace(char, int);
void isFull(Tree *);
void removeValue(Data *, int);
void printInOrder(Data *);
void printPreOrder(Data *);
void printPostOrder(Data *);
void getHeigth(Tree *);
Tree *balanceTree(Tree *);
void printTree(Data *, int);
Data *leftRotation(Data *, Data *, Data *, Data *);
Data *rightRotation(Data *, Data *, Data *);
Tree *linearizarElementos(Tree *);
Tree *balanceTree(Tree *);
int isBalanced(Data *);
int getHeight2(Data *);
int max(int, int);

#endif
