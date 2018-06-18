#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lib.h"
#define cols 10
#define max_file 9

struct lista{
  int valor;
  struct lista *prox;
};
typedef struct lista Lista;

Lista *head;


int menu(){
  int opt;

  printf("'-----------------------------'\n");
  printf("'        bem vindo            '\n");
  printf("'-----------------------------'\n");
  printf("Escolha alguma das opcoes:\n");
  printf("1. Carregar arquivo.\n");
  printf("2. Mostrar arvore.\n");
  printf("3. Verifica se a árvore é cheia.\n");
  printf("4. Verifica altura da arvore.\n");
  printf("5. Imprimir arvore em ordem.\n");
  printf("6. Imprimir arvore em pre ordem.\n");
  printf("7. Imprimir arvore em pos ordem.\n");
  printf("8. Mostrar arvore balanceada.\n");
  printf("9. Remover valor.\n");
  printf("0. Sair\n");
  printf("\n\nOpção: ");
  scanf("%d", &opt);

  return opt;
}

void libera(Lista *l){
  Lista *p=l;
  while (p!=NULL) {
    Lista *t = p->prox; /*guarda referencia para o proximo elemento */
    free(p); //libera a memória apontada por p
    p=t; //faz p apontar para o proximo
  }
}

char *choseFile(){
  int opt;
  char * arquivo;
  arquivo = malloc(sizeof(char)*9);
    printf("Escolha um arquivo válido [1-6]: \n");
    scanf("%d",&opt);

    switch (opt) {
      case 1:
        strcpy(arquivo,"BSTs/bst1.txt");
        //printf("%s\n", arquivo);
        break;
      case 2:
        strcpy(arquivo,"BSTs/bst2.txt");
        break;
      case 3:
        strcpy(arquivo,"BSTs/bst3.txt");
        break;
      case 4:
        strcpy(arquivo,"BSTs/bst4.txt");
        break;
      case 5:
        strcpy(arquivo,"BSTs/bst5.txt");
        break;
      case 6:
        strcpy(arquivo,"BSTs/bst6.txt");
        break;
      default:
      printf("Digite uma opcao valida (: \n\n");
    }
  return arquivo;
}

Lista *insereInicio(Lista *l, int i, Lista **head)
{
  Lista *novo = (Lista*)malloc(sizeof(Lista));
  novo->valor = i;
  novo->prox = l;
  if(*head == NULL){
    *head = novo;
  }
  return novo;
}

Lista *insereFim(Lista *l, int i){
  Lista *novo = (Lista *)malloc(sizeof(Lista));
  novo->valor=i;
  novo->prox=NULL;

  if(l==NULL){
    l=novo;
  } else {
    Lista *aux = l;
    while(aux->prox != NULL){
      aux=aux->prox;
    }
    aux->prox=novo;
  }
}

Lista *retira (Lista *l, int v)//, Lista **head)
{
  Lista *ant = NULL; /* ponteiro para elemento anterior */
  Lista *p = l; /* ponteiro para percorrer a lista */

  //procura elemento na lista, guardando anterior
  while(p!=NULL && p->valor!=v){
    ant = p;
    p = p->prox;
  }
  //Verifica se achou o elemento
  if(p==NULL){
    return l;
  }
  // Retira elemento
  if(ant==NULL){
    /* retira do início */
    l = p->prox;
  } else {
    /* retira do meio*/
    ant->prox = p->prox;
  }
  free(p);
  return l;

}


void imprime(Lista *l)
{
  Lista *p;
  for(p=l;p!=NULL;p=p->prox){
    printf("%d ",p->valor);
  }
}

// Cria lista vazia
Lista *inicializa(void)
{
  return NULL;
}

Lista * loadFile(char *arquivo, Tree **rootB, Lista **head){

  //int valor = 0;
  char ch;
  int valor[10];
  Lista *vetor=NULL;
  libera(vetor);
  *rootB = NULL;
  make_empty(*rootB);
  vetor = inicializa();

  FILE *file;
  file = fopen(arquivo, "r");
  rewind(file);

  if(file==NULL){
    printf("Falha!\n");
  } else {
    for(int aux=0; aux < cols; aux++){
      fscanf(file, "%d%*c", &valor[aux]);
      //printf("valor: %d ",valor );
    //  vetor = insereFim(vetor, valor[aux]);
    }
  }
  rewind(file);
//  fclose(file);

  printf("Os valores do arquivo sao: \n");
  for(int i=cols-1;i>=0; --i)
    vetor = insereInicio(vetor, valor[i], &(*head));
    //printf("%d ", valor[i]);
  imprime(vetor);

  Lista * p;
  //for(int aux=0; aux<cols; aux++){
  for(p=vetor; p!=NULL; p=p->prox){
    *rootB = insertBalanced(*rootB, p->valor);
  }

  printf("\n\n");

  return vetor;
  //fclose(file);
}

Tree* loadTreeFromFile(Tree *root, char *arquivo){

  root = make_empty(root);
  //printf("TESTE2\n");
  FILE *file;
  file = fopen(arquivo, "r");
  //printf("TESTE1\n");
  rewind(file);
  //printf("TESTE1\n");
  int valor[10];
  if(file==NULL){
    printf("Falha!\n");
  } else {
    for(int aux=0; aux < cols; aux++){
    //  printf("TESTE4444\n");
      fscanf(file, "%d%*c", &valor[aux]);
    //  printf("%d ",valor[aux] );
      root = insert(valor[aux], root);
    //  printf("TESTE1\n");
    }
  }

  printf("O arquivo selecionado eh: %s \n\n", arquivo);

  fclose(file);

  return root;
}

void showTree(Tree * root){

  printf("Mostrar arvore:\n");
  print_ascii_tree(root);
  printf("\n\n");
}

void getHeight(Tree* root){
  int h = checkHeight(root);
  printf("\nAltura da arvore eh: %d\n\n\n",h);
}


void printInOrder(Tree * root){
  printf("Impressao da arvore em ordem:\n");
  inOrder(root);
  printf("\n\n\n");
}

void printPreOrder(Tree * root){
  printf("Impressao da arvore em pre ordem:\n");
  preOrder(root);
  printf("\n\n\n");
}

void printPostOrder(Tree * root){
  printf("Impressao da arvore em pos ordem:\n");
  postOrder(root);
  printf("\n\n\n");
}

void balanceTree(Tree **rootB){

  // Lista * p;
  // //for(int aux=0; aux<cols; aux++){
  // for(p=vetor; p!=NULL; p=p->prox){
  //   rootB = insertBalanced(rootB, p->valor);
  // }

  printf("\nArvore balanceada: \n\n");
  print_ascii_tree(*rootB);
  printf("\n\n\n");
  //return rootB;

}

Tree* removeValue(Tree * root, Tree **rootB, Lista *vetor){
  int valor = 0;
  Lista * p;
  printf("votr prox: %d\n", vetor->valor);
  printf("Digite o valor que deseja remover?\n");
  scanf("%d",&valor);
  if(busca(root, valor)==0){
    printf("Arvore não possui esse valor.\n");
  } else {
    root = delete(valor, root);
    vetor = retira(vetor, valor);
    //for(int aux=0; aux<cols; aux++){
    *rootB = delete(valor, *rootB);
    for(p=vetor; p!=NULL; p=p->prox){
      *rootB = insertBalanced(*rootB, p->valor);
    }
    printf("\n\nRemovido com sucesso");
  }
  printf("\n\n\n");

  //*rootB = delete(valor, *rootB);
  return root;

}


int main(){

  Lista *vetor;
  Tree * root;
  Tree * rootB;
  char *arquivo;
  Lista *head = NULL;

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
        //vetor = calloc(cols,sizeof(int));
      //  vetor = inicializa();
        vetor = loadFile(arquivo, &rootB, &head);
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
      case 4:
        getHeight(root);
        break;
      case 5:
        printInOrder(root);
        break;
      case 6:
        printPreOrder(root);
        break;
      case 7:
        printPostOrder(root);
        break;
      case 8:
        root = removeValue(root, &rootB, vetor);
        break;
      case 9:
        balanceTree(&rootB);
        break;
      default:
        printf("Digite uma opcao valida (: \n\n");
    }
  } while(opt);
  return 0;

}
