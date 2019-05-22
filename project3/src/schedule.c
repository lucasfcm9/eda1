#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "schedule.h"

int main()
{
    int option;

    do {
        printf("1 - Inserir novo registro\n");
        printf("2 - Remover registros que contenham certa string no nome\n");
        printf("3 - Visualizar registros que contenham certa string no nome\n");
        printf("4 - Visualizar todos os registros em ordem alfabética\n");
        printf("5 - SAIR\n");

        switch(option)
        {
            case 1:
                Inserir();
                break;
            case 2:
                Remover();
                break;
            case 3:
                Visualizar();
                break;
            case 4:
                Ordem();
                break;
            default:
                printf("Digite uma opção válida\n");
                break;
        }
    } while(option);
    
    return 0;
}
