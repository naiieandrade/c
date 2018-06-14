#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lib.h"
#define cols 10
#define max_file 9


int menu(){
  int opt;

  printf("'-----------------------------'\n");
  printf("'        bem vindo            '\n");
  printf("'-----------------------------'\n");
  printf("Escolha alguma das opcoes:\n");
  printf("1. Carregar arquivo.\n");
  printf("2. Mostrar arvore.\n");
  printf("0. Sair\n");
  printf("\n\nOpção: ");
  scanf("%d", &opt);

  return opt;
}

char *choseFile(){
  int opt;
  char * arquivo;
  arquivo = malloc(sizeof(char)*8);
    printf("Escolha um arquivo válido [1-6]: \n");
    scanf("%d",&opt);

    switch (opt) {
      case 1:
        strcpy(arquivo,"t1.txt");
        printf("%s\n", arquivo);
        break;
      default:
      printf("Digite uma opcao valida (: \n\n");
    }
  return arquivo;
}


int * loadFile(char *arquivo, int *vetor){

  int valor = 0;
  char ch;

  FILE *file;
  file = fopen(arquivo, "r");

  rewind(file);
  if(file==NULL){
    printf("Falha!\n");
  } else {
    for(int aux=0; aux < cols; aux++){
      fscanf(file, "%d%*c", &vetor[aux]);
    }
  }

  printf("Os valores do arquivo sao: \n");
  for(int i=0;i<cols;i++)
    printf("%d ",vetor[i]);

  printf("\n\n");
  return vetor;
}

Tree* loadTreeFromFile(Tree *root, char *arquivo){

  FILE *file;
  file = fopen(arquivo, "r");
  rewind(file);
  int *valor;
  if(file==NULL){
    printf("Falha!\n");
  } else {
    for(int aux=0; aux < cols; aux++){
      fscanf(file, "%d%*c", &valor[aux]);
      root = insert(valor[aux], root);
    }
  }
  printf("O arquivo selecionado eh: %s \n\n", arquivo);
  return root;
}

void showTree(Tree * root){

  printf("Mostrar arvore:\n");
  print_ascii_tree(root);
  printf("\n\n");
}



int main(){

  int * vetor;
  Tree * root;
  Tree * rootB;
  char *arquivo;

  root = NULL;
  rootB = NULL;

  make_empty(root);
  make_empty(rootB);

  int opt;
  do{
    opt=menu();

    switch (opt) {
      case 0:
        printf("Libera\n");
        break;
      case 1:
        arquivo = choseFile();
        vetor = calloc(cols,sizeof(int));
        vetor = loadFile(arquivo, vetor);
        root = loadTreeFromFile(root,arquivo);
        break;
      case 2:
        showTree(root);
        break;
      case 3:
        {
          if(isFullTree(root))
              printf("\n\nArvore é cheia. :) \n\n");
          else
              printf("\n\nArvore não é cheia. :( \n\n");
        };
        break;
      default:
        printf("Digite uma opcao valida (: \n\n");
    }
  } while(opt);
  return 0;

}
