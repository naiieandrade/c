#include<stdio.h>
#include<stdlib.h>
#include "lib.h"

int menu();
int * loadFile(int cols, int *vetor);
Tree* loadTreeFromFile(Tree *root, int *vetor, int cols);
//void balanceTree(Tree *root);
Tree * balanceTree(Tree *root, int *vetor, int cols);
void printinOrder(Tree *root);
void getHeightPrint(Tree* root);
FILE *openFile(void);
int countDataFromFile(void);

int main(){

  int cols = 0;
  int * vetor;
  Tree * root;
  Tree * rootB;
  int i;
  root = NULL;



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
      //  showTree();
        cols = countDataFromFile();
        vetor = calloc(cols,sizeof(int));
        vetor = loadFile(cols, vetor);
        root = loadTreeFromFile(root,vetor, cols);
        break;
      case 2:
        //balanceTree(root);
        rootB = balanceTree(rootB, vetor, cols);
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

//char *choseFile(int opt){
  // char arquivo[]="t1.txt";
  //
  // FILE *file;
  // return file;
//}

int countDataFromFile(void){
  char arquivo[]="t1.txt";
  FILE* file;
  file = fopen(arquivo, "r");
  char ch;
  int cols=0;

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
  return cols;
}

int * loadFile(int cols, int *vetor){
  char arquivo[]="t1.txt";
  int valor = 0;
  char ch;

  FILE *file;
  file = fopen(arquivo, "r");

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

Tree* loadTreeFromFile(Tree *root, int *vetor, int cols){
  for(int i=0; i<cols;i++){
    root=insert(vetor[i],root);
    printf("%d ", vetor[i]);
  }

  printf("SIZEOF: %ld\n",sizeof(vetor) );
  printf("\n Show tree: \n\n");


  print_ascii_tree(root);
  return root;

}


Tree * balanceTree(Tree *rootB, int *vetor, int cols){

//  int valor = 0;

  for(int aux=0; aux < cols; aux++){
    rootB = insertBalanced(rootB, vetor[aux]);
  }


/*  preOrder(root);
  printf("\n\n");
  print_ascii_tree(root);
  printf("\n");
  postOrder(root);
  printf("\n\n");
  int h = getHeight(root);
  printf("ALTURA: %d\n",h);
*/
  print_ascii_tree(rootB);
  return rootB;
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
