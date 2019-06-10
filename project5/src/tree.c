#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"

#define Dt Data
#define T Tree
int COUNT = 10;
Dt *newNode()
{
    Dt *newNode = (Dt *)malloc(sizeof(Dt));
    if(newNode == NULL){
        printf("Error\n");
        return  NULL;
        exit(-1);
    }else
        return newNode;
}

T *newTree()
{
    T *newTree = (T *)malloc(sizeof(T));
    if(newTree == NULL)
        return NULL;
    else
        return newTree;
}

void createTree(T **tree, int *n)
//{42,16,57,48,63,35,8,11,5}
{
  for(int i = 0; i < 9; i++){
    Dt *elem = newNode();
    elem->info = *(n+i);
    if((*tree)->root == NULL){
      elem->right = NULL;
      elem->left = NULL;
      (*tree)->root = elem;
    } else if(*(n+i) < (*tree)->root->info){
      if((*tree)->root->left == NULL){
        (*tree)->root->left = elem;
        elem->right = NULL;
        elem->left = NULL;
      } else {
        Dt *aux = (*tree)->root->left;
        int j = 3;
        while(1){
          if(*(n+i) < aux->info){
            if(aux->left == NULL){
              aux->left = elem;
              elem->right = NULL;
              elem->left = NULL;
              break;
            }else{
              aux = aux->left;
              j++;
            }
          }else{
              if(aux->right == NULL){
                aux->right = elem;
                elem->right = NULL;
                elem->left = NULL;
                break;
              }else{
                aux = aux->right;
                j++;
              }
          }
          (*tree)->height = j;
        }
      }
    }else{
      if((*tree)->root->right == NULL){
        (*tree)->root->right = elem;
        elem->right = NULL;
        elem->left = NULL;
      } else {
        Dt *aux = (*tree)->root->right;
        int j = 3;
        while(1){
          if(*(n+i) < aux->info){
            if(aux->left == NULL){
              aux->left = elem;
              elem->right = NULL;
              elem->left = NULL;
              break;
            }else{
              aux = aux->left;
              j++;
            }
          }else{
              if(aux->right == NULL){
                aux->right = elem;
                elem->right = NULL;
                elem->left = NULL;
                break;
              }else{
                aux = aux->right;
                j++;
              }
          }
        }
        (*tree)->height = j;
      }
    }
  }
}

T *loadTreeFromFile(char *fp)
{
    // T *tree;
    // tree = newTree();
    //
    // if(tree == NULL)
    //     return NULL;
    //
    // FILE *fp = fopen(fp, "r");
    //
    // if(fp == NULL)
    //     return NULL;
}

  void printTree(Dt* root, int space){
    if(root == NULL){
      return;
    }
    space+=COUNT;

    printTree(root->right, space);

    printf("\n");
    for(int i = COUNT; i < space; i++)
      printf(" ");
    printf("%d\n", root->info);

    printTree(root->left, space);
}

void isFull(T *tree){
  Dt *aux = tree->root;
  int j = 0;
  while(1){
    if(j == (tree->height -1)){

    }else{
      aux = aux -> left
    }
  }
}
