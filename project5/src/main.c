#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

int main()
{
    int tree_elements[] = {42,16,57,48,63,35,8,11,5};
    int op;
    Tree *tree = newTree();
    int *s = loadTreeFromFile("in.txt");
    createTree(&tree, s);
    printf("altura %d\n", tree->height);
    printTree(tree->root, 0);
    isFull(tree);
    searchValue(tree->root, 10);
    printf("Print in order\n\n");
    printInOrder(tree->root);
    printf("\n\n");
    printf("Print post order\n\n");
    printPostOrder(tree->root);
    printf("\n\n");
    printf("Print pre order\n\n");
    printPreOrder(tree->root);
    printf("\n\n");
    printf("Remove element\n\n");
    removeValue(tree->root, 48);
    printTree(tree->root, 0);
    printf("\n\n");
    // do
    // {
    //     printf("1 - Carregar árvore a partir de um arquivo\n");
    //     printf("2 - Mostrar árvore binária\n");
    //     printf("3 - Imprimir na tela se a árvore está cheia ou não\n");
    //     printf("4 - Buscar valor na árvore binária\n");
    //     printf("5 - Imprimir na tela a altura da árvore\n");
    //     printf("6 - Remover valor da árvore binária\n");
    //     printf("7 - Printar árvore InOrder\n");
    //     printf("8 - Printar árvore PreOrder\n");
    //     printf("9 - Printar árvore PostOrder\n");
    //     printf("10 - Balancear árvore\n\n");
    //
    //     printf("Digite sua opção, por favor: ");
    //     scanf("%d", &op);
    //     system("clear");

    // switch (op)
    // {
    // case 1:
    //     loadTreeFromFile();
    //     break;
    // case 2:
    //     showTree();
    //     break;
    // case 3:
    //     isFull();
    //     break;
    // case 4:
    //     searchValue();
    //     break;
    // case 5:
    //     getHeigth();
    //     break;
    // case 6:
    //     removeValue();
    //     break;
    // case 7:
    //     printInOrder();
    //     break;
    // case 8:
    //     printPreOrder();
    //     break;
    // case 9:
    //     printPostOrder();
    //     break;
    // case 10:
    //     balanceTree();
    //     break;
    // default:
    //     printf("Digite uma opção válida, por favor!");
    //     break;
    // }

    // } while (op);
    return 0;
}
