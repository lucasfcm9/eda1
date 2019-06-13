#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#include "tree.h"
#define path "../BSTs/"


int main()
{
    int op;
    char fp[20];
    char full_path[25];
    int number;
    int n;
    Tree *tree = newTree();
    do
    {
        printf("1 - Carregar árvore a partir de um arquivo\n\n");
        printf("\tOpções:\n\ttbst1.txt\n\ttbst2.txt\n\ttbst3.txt\n\ttbst4.txt\n\ttbst5.txt\n\ttbst6.txt\n\n");
        printf("2 - Mostrar árvore binária\n");
        printf("3 - Imprimir na tela se a árvore está cheia ou não\n");
        printf("4 - Buscar valor na árvore binária\n");
        printf("5 - Imprimir na tela a altura da árvore\n");
        printf("6 - Remover valor da árvore binária\n");
        printf("7 - Printar árvore InOrder\n");
        printf("8 - Printar árvore PreOrder\n");
        printf("9 - Printar árvore PostOrder\n");
        printf("10 - Balancear árvore\n\n");

        printf("Digite sua opção, por favor: ");
        scanf("%d", &op);

    switch (op)
    {
        case 1:
            scanf("%s[^\n]", fp);
            strcpy(full_path, path);
            strcat(full_path, fp);
            loadTreeFromFile(full_path, &tree);
            break;
        case 2:
            printTree(tree->root, 0);
            break;
        case 3:
            isFull(tree);
            break;
        case 4:
            printf("Digite o valor a ser procurado na árvore:\n");
            scanf("%d", &number);
            searchValue(tree->root, number);
            break;
        case 5:
            getHeigth(tree);
            break;
        case 6:
            printf("Digite o valor que quer remover da árvore:\n");
            scanf("%d", &n);
            removeValue(tree->root, n);
            break;
        case 7:
            printInOrder(tree->root);
            break;
        case 8:
            printPreOrder(tree->root);
            break;
        case 9:
            printPostOrder(tree->root);
            break;
        // case 10:
        //     balanceTree();
        //     break;
        default:
            printf("Digite uma opção válida, por favor!");
            break;
    }

    } while (op);
    return 0;
}
