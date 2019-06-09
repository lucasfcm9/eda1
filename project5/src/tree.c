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
  for(int i = 0; i < sizeof(n)/sizeof(int); i++){
    Dt *elem = newNode();
    elem->info = *(n+i);
    if((*tree)->root == NULL){
      elem->right = NULL;
      elem->left = NULL;
      (*tree)->root = elem;
      (*tree)->height = 1;
      (*tree)->empty = false;
    } else if(*(n+i) > (*tree)->root->info){
      if((*tree)->root->right == NULL){
        printf("ENTREI NO IF DO ROOT A DIREITA\n");
        (*tree)->root->right = elem;
        elem->right = NULL;
        elem->left = NULL;
      } else {
        Dt *aux = (*tree)->root->right;
        while(1){
          if((*n+i) > aux->info){
            if(aux->right == NULL){
              aux->right = elem;
              elem->right = NULL;
              elem->left = NULL;
              break;
            }else{
              aux = aux->right;
            }
          }else{
              if(aux->left == NULL){
                aux->left = elem;
                elem->right = NULL;
                elem->left = NULL;
                break;
              }else{
                aux = aux->left;
              }
          }
        }
      }
    }else{
      if((*tree)->root->left == NULL){
        (*tree)->root->left = elem;
        elem->right = NULL;
        elem->left = NULL;
      } else {
        Dt *aux = (*tree)->root->left;
        while(1){
          if((*n+i) > aux->info){
            if(aux->right == NULL){
              aux->right = elem;
              elem->right = NULL;
              elem->left = NULL;
              break;
            }else{
              aux = aux->right;
            }
          }else{
              if(aux->left == NULL){
                aux->left = elem;
                elem->right = NULL;
                elem->left = NULL;
                break;
              }else{
                aux = aux->left;
              }
          }
        }
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
  printf("%d\n", root->info );
}
