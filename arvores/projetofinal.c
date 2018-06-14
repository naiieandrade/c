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
  printf("1. Mostrar arvore\n");
  printf("0. Sair\n");
  printf("\n\nOpção: ");
  scanf("%d", &opt);

  return opt;
}

char *choseFile(){
  int opt;
  char * arquivo;
  arquivo = malloc(sizeof(char)*8);
    printf("Escolha um arquivo válido: \n");
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

  for(int i=0;i<cols;i++)
    printf("%d ",vetor[i]);

  return vetor;
}


int main(){

  int * vetor;
  Tree * root;
  Tree * rootB;
  char *arquivo;

//  make_empty(root);
//  make_empty(rootB);

  int opt;
  do{
    opt=menu();

    switch (opt) {
      case 0:
        printf("Libera\n");
        break;
      case 1:
      //  showTree();
        arquivo = choseFile();
        vetor = calloc(cols,sizeof(int));
        vetor = loadFile(arquivo, vetor);
      //  root = loadTreeFromFile(root,arquivo);
        break;
      default:
        printf("Digite uma opcao valida (: \n\n");
    }
  } while(opt);
  return 0;

}
