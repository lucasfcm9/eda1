### Projeto 5 de Estruturas de Dados 1

*Alunos:* *Lucas Fellipe Carvalho Moreira && Pedro Henrique Queiroz Miranda && Gabriel Davi Silva Pereira*

*Matrículas:* *16/0133394 && 15/0144474 && 17/0010341*

*Disciplina: Estruturas de Dados 1*

*Professor: Mateus Mendelson*

O projeto consiste na implementação de uma árvore binária utilizando a linguagem de programação C.

O projeto possui as seguintes funções implementadas no arquivo tree.c e declaradas no arquivo tree.h:

* Data *newNode();

* Tree *newTree();

* void createTree(Tree **, int *, int);

* void *loadTreeFromFile(char *, Tree **);

* void searchValue(Data *, int);

* void getElement(Data *, int *, int *);

* void showTree(Data *);

* void whiteSpace(char, int);

* void isFull(Tree *);

* void removeValue(Data *, int);

* void printInOrder(Data *);

* void printPreOrder(Data *);

* void printPostOrder(Data *);

* void getHeigth(Tree *);

* Tree *balanceTree(Tree *);

* void printTree(Data *, int);

* Data *leftRotation(Data *, Data *, Data *, Data *);

* Data *rightRotation(Data *, Data *, Data *);

* Tree *linearizarElementos(Tree *);

* Tree *balanceTree(Tree *);

* int isBalanced(Data *);

* int getHeight2(Data *);

* int max(int, int);

Para você testar, coloque a pasta BSTs dentro da pasta dos arquivos '.c' e execute o seguinte comando no terminal:

```
gcc -o main tree.c main.c
```

E aí siga os comandos pelo terminal.

