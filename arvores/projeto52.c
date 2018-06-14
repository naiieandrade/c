#include<stdio.h>
#include<stdlib.h>
#include "lib.h"

int menu();
int * loadFile(void);
Tree* loadTreeFromFile(Tree *root, int *vetor);
void balanceTree(Tree *root);
void printinOrder(Tree *root);
void getHeightPrint(Tree* root);

int main(){

  Tree * root;
  int i;
  root = NULL;
  int * vetor;

  make_empty(root);

  int opt;
  do{
    opt=menu();

    switch (opt) {
      case 0:
        printf("Libera\n");
        break;
      case 1:
      //  showTree();
        vetor = loadFile();
        root=loadTreeFromFile(root,vetor);
        break;
      case 2:
        balanceTree(root);
      //  printInOrder();
        break;
      case 3:
        printinOrder(root);
        break;
      case 4:
        preOrder(root);
        break;
      case 5:
        postOrder(root);
        break;
      case 6:
        getHeightPrint(root);
      default:
        printf("Digite uma opcao valida (: \n\n");
    }
  } while(opt);
  return 0;
//  printf("\nAfter inserting element 10..\n");
//  root = insert(10, root);
//  print_ascii_tree(root);

}


int menu(){
  int opt;

  printf("'-----------------------------'\n");
  printf("'        bem vindo            '\n");
  printf("'-----------------------------'\n");
  printf("Escolha alguma das opcoes:\n");
  //printf("1. Carregar arquivo\n");
  printf("1. Mostrar arvore\n");
  printf("2. Balancear arvore\n");
  printf("3. Imprimir em em ordem\n");
  printf("4. Imprimir em pre ordem\n");
  printf("5. Imprimir em pos ordem\n");
  printf("6. Altura da arvore\n");
//  printf("4. Visualizar todos os registros\n");
  printf("0. Sair\n");
  printf("\n\nOpção: ");
  scanf("%d", &opt);

  return opt;


}

int * loadFile(void){
  char arquivo[]="t1.txt";
  int valor = 0;
  int cols=0;
  char ch;
  int *vetor;

  FILE *file;
  file = fopen(arquivo, "r");

  if(file==NULL){
    printf("Falha!\n");
  } else {
    while((ch=fgetc(file))!=EOF){
      if(ch==' '){
        cols++;
      }
    }
  }
  cols+=1;
  vetor = calloc(cols,sizeof(int));
  rewind(file);
  if(file==NULL){
    printf("Falha!\n");
  } else {
    for(int aux=0; aux < cols; aux++){
      fscanf(file, "%d%*c", &vetor[aux]);//&valor);
      //vetor[aux];
      //root = insert(valor, root);
    }
  }

  return vetor;

  //print_ascii_tree(root);
  // for(int i=0; i<cols;i++){
  //   root=insert(vetor[i],root);
  //   printf("%d ", vetor[i]);
  // }
  //
  //
  // printf("\n Show tree: \n\n");
  //
  //
  // print_ascii_tree(root);
  //
  // return root;
}

Tree* loadTreeFromFile(Tree *root, int *vetor){
  for(int i=0; i<sizeof(vetor);i++){
    root=insert(vetor[i],root);
    printf("%d ", vetor[i]);
  }


  printf("\n Show tree: \n\n");


  print_ascii_tree(root);
  return root;

}


void balanceTree(Tree *root){
  char arquivo[]="t1.txt";
  FILE *file;
  file = fopen(arquivo, "r");
  int valor = 0;

  if(file==NULL){
    printf("Falha!\n");
  } else {
    for(int aux=0; aux < 10; aux++){
      fscanf(file, "%d ", &valor);
      root = insertBalanced(root, valor);
    }
  }

  preOrder(root);
  printf("\n\n");
  print_ascii_tree(root);
  printf("\n");
  postOrder(root);
  printf("\n\n");
  int h = getHeight(root);
  printf("ALTURA: %d\n",h);

}

void printinOrder(Tree* root){
  preOrder(root);
  printf("\n");
}

void getHeightPrint(Tree* root){
  int h = getHeight(root);
  printf("Altura: %d\n",h);
  printf("\n");
}
