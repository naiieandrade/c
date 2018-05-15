#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct registro{
  char *nome;
  char *telefone;
  unsigned int cep;
  char *data;
  struct registro *prox;
};
typedef struct registro Agenda;

Agenda *inicializa(void);
Agenda *insere(Agenda *l);//, char *nome, char *telefone, unsigned int cep, char *data);
void imprime(Agenda *l);
Agenda *apaga_contato(Agenda *l, char *nome);
void libera(Agenda *l);
int tamanho(Agenda *l);
//Agenda *novo_registro(Agenda *l);
int menu();
void opcao(Agenda *l, int op);

int vazia(Agenda *l){
  if(l->prox==NULL)
    return 1;
  else
    return 0;
}


int main(){

  char *nome = (char *)malloc(100*sizeof(char));
  char *telefone = (char *)malloc(10*sizeof(char));
  unsigned int cep;
  char *data = (char *)malloc(10*sizeof(char));

  Agenda *l = (Agenda *)malloc(sizeof(Agenda));
  if(!l){ // verifica se tem memória
    printf("Sem memória disponível!\n");
    exit(1);
  } else {
    l=inicializa();
    int opt;

    do{
      opt=menu();

      switch (opt) {
        case 0:
          libera(l);
          break;
        case 1:
          l=insere(l);
          break;
        case 2:
          printf("opcao 2\n");
          break;
        case 3:
          printf("opcao 3\n");
          break;
        case 4:
          imprime(l);
          break;
        default:
          printf("Digite uma opcao valida (:\n\n");
      }

    } while(opt);
    free(l);
    return 0;
  }

/*
  l = insere(l,"pedro","1234",123,"hoje");
  l = insere(l,"marina","999888",1278231,"25maio");

  printf("\n__________________\n    IMPRIME   \n\n");
  imprime(l);

  int x = tamanho(l);
  printf("TAMANHO %d\n\n",x);
  l=apaga_contato(l,"pedro");
  printf("DEPOIS DE REMOVER\n  ----------------------- \n");
  imprime(l);


  libera(l);
*/
//  return 0;
}

int menu(){
  int opt;
  //system("clear");
//  printf("'-----------------------------'\n");
//  printf("'        bem vindo            '\n");
//  printf("'-----------------------------'\n");
  printf("Escolha alguma das opcoes:\n");
  printf("1. Adicionar um registro\n");
  printf("2. Remover um registro\n");
  printf("3. Buscar registro\n");
  printf("4. Visualizar todos os registros\n");
  printf("0. Sair\n");
  printf("\n\nOpção: ");
  scanf("%d", &opt);

  return opt;

}
/*
void opcao(Agenda *l, int op){

  Agenda *tmp;
  switch (op) {
    case 0:
      libera(l);
      break;
    case 1:
      insere(l);
      break;
    case 2:
      printf("opcao 2\n");
      break;
    case 3:
      printf("opcao 3\n");
      break;
    case 4:
      imprime(l);
      break;
    default:
      printf("Digite uma opcao valida (:\n\n");
  }
}*/


//inicializa
Agenda *inicializa(void){
  return NULL;
}

//insere
Agenda *insere(Agenda *l){//, char *nome, char *telefone, unsigned int cep, char *data){
  Agenda *novo = (Agenda*)malloc(sizeof(Agenda));

  char *nome = (char *)malloc(100*sizeof(char));
  char *telefone = (char *)malloc(10*sizeof(char));
  unsigned int cep;
  char *data = (char *)malloc(10*sizeof(char));

  printf(" -----------------------------\n");
  printf("|        novo registro       |\n");
  printf(" -----------------------------\n");
  printf("1 - Inserir contato\n\n");
  printf("Digite o nome:  ");
  scanf("%s", nome);
  printf("Numero de telefone:  ");
  scanf("%s", telefone);
  printf("CEP:  ");
  scanf("%d", &cep);
  printf("Data de aniversario:  ");
  scanf("%s", data);


  novo->nome=nome;
  novo->telefone=telefone;
  novo->cep=cep;
  novo->data=data;
  novo->prox = l;

  return novo;
}

void imprime(Agenda *l){
  Agenda *ag;
/*  if(vazia(l)){
    printf("Lista vazia\n");
    return ;
  }
*/
  //if(l->prox==NULL){
  //  printf("Lista vazia\n");
  //} else {
  printf("TESTE\n");
  if(l==NULL)
    printf("VAZIA\n");
    for(ag=l; ag!=NULL; ag=ag->prox){
      printf("Nome: %s\n", ag->nome);
    //  printf("Telefone: %s\n", ag->telefone);
    }
  //}
}

Agenda *apaga_contato(Agenda *l, char *nome){
  Agenda *ant = NULL;
  Agenda *aux = l;

  /* Verifica se achou o elemento */
  while(aux!=NULL && aux->nome!=nome){
    ant = aux;
    aux = aux->prox;
  }
  /* Verifica se achou o elemento */
  if(aux==NULL){
    return l;
  }
  /* Retira elemento */
  if(ant==NULL){
    /* retira do início */
    l = aux->prox;
  } else {
    /* retira do meio */
    ant->prox = aux->prox;
  }
  free(aux);
  return l;
}


void libera(Agenda *l){
  Agenda *p=l; //aux, agenda
  while(p!=NULL){
    Agenda *ag = p->prox; /* guarda referencia para o proximo elemento */
    free(p); /* libera a memória apontada por AUX */
    p=ag;  /* faz AUX apontar para o proximo */
  }
}

// Tamanho da lista
int tamanho(Agenda *l){
  if(l==NULL) return 0;
  int cont = 0;
  Agenda *no=l; //*l -> primeiro elemento da lista?
  while(no!=NULL){
    cont++;
    no=no->prox;
  }
  return cont;
}


//Agenda *novo_registro(Agenda *l){
//  system("clear");

  //Agenda *l = (Agenda *)malloc(sizeof(Agenda));

/*
  char *nome = (char *)malloc(100*sizeof(char));
  char *telefone = (char *)malloc(10*sizeof(char));
  unsigned int cep;
  char *data = (char *)malloc(10*sizeof(char));

  printf(" -----------------------------\n");
  printf("|        novo registro       |\n");
  printf(" -----------------------------\n");
  printf("1 - Inserir contato\n\n");
  printf("Digite o nome:  ");
  scanf("%s", nome);
  printf("Numero de telefone:  ");
  scanf("%s", telefone);
  printf("CEP:  ");
  scanf("%d", &cep);
  printf("Data de aniversario:  ");
  scanf("%s", data);

//  l=insere(l,nome,telefone,cep,data);
  imprime(l);
  return l;
*/
//}
