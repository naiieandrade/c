#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MTELEFONE "#####-####"
#define MDATA "##/##/####"

struct registro{
  char nome[101];
  char telefone[11];
  char endereco[101];
  unsigned int cep;
  char data[11];
  struct registro *prox;
  struct registro *ant;
};
typedef struct registro Agenda;

Agenda *inicializa(void);
Agenda *insere(Agenda *l);
void imprime(Agenda *l);
Agenda *apaga_contato(Agenda *l);
void libera(Agenda *l);
int tamanho(Agenda *l);
int menu();
void opcao(Agenda *l, int op);
void *busca(Agenda *l);
char *mascaraTelefone(char telefone[], char formato[]);
Agenda *buscaRegistro(Agenda *l, char nome[]);

int vazia(Agenda *l){
  if(l->prox==NULL)
    return 1;
  else
    return 0;
}

int main(){

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
          l=apaga_contato(l);
          break;
        case 3:
          busca(l);
          break;
        case 4:
          imprime(l);
          break;
        default:
          printf("Digite uma opcao valida (:\n\n");
      }

    } while(opt);
    return 0;
  }
}

int menu(){

  int opt;
  printf("'-----------------------------'\n");
  printf("'        bem vindo            '\n");
  printf("'-----------------------------'\n");
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

//inicializa
Agenda *inicializa(void){
  return NULL;
}

//insere
Agenda *insere(Agenda *l){
  Agenda *novo = (Agenda*)malloc(sizeof(Agenda));

  char nome[101];
  char telefone[10];
  char endereco[101];
  unsigned int cep;
  char dataNascimento[10];

  printf(" -----------------------------\n");
  printf("|        novo registro       |\n");
  printf(" -----------------------------\n");
  printf("1 - Inserir contato\n\n");
  printf("Digite o nome:  ");
  getchar();
  scanf("%[^\n]", nome);
  printf("Numero de telefone:  ");
  scanf("%s", telefone);
  //printf("TELEFONE %s",telefone);
  fflush ( stdin );
  printf("Endereco:  ");
  getchar();
  scanf("%[^\n]", endereco);
  printf("CEP:  ");
  scanf("%d", &cep);
  printf("Data de nascimento:  ");
  scanf("%s", dataNascimento);
  //printf("DATA %s",dataNascimento);
  //printf("das/dsa/dsad\n");

  strcpy(novo->nome,nome);
  strcpy(novo->telefone,telefone);
  strcpy(novo->endereco,endereco);
  novo->cep=cep;
  //printf("DATA %s",dataNascimento);
  strcpy(novo->data,dataNascimento); //mascaraData(dataNascimento)
  //printf("novo data %s\n",novo->data );
  //novo->prox = l;
  //novo->ant = NULL;

  Agenda *atual=l;

  if(atual==NULL){
    novo->prox=l;
    novo->ant=NULL;
  } else {
      for(atual=l;atual!=NULL;atual=atual->prox){
        if(strcmp(novo->nome,nome)<strcmp(atual->nome,nome)&&atual->ant==NULL){
          novo->ant=atual->ant;
          novo->prox=atual;
          atual->ant=novo;
          novo->prox=atual;
        }
        if(strcmp(novo->nome,nome)>strcmp(atual->nome,nome)){
          if(atual->prox==NULL){
            novo->prox=atual->prox;
            novo->ant=atual;
            atual->prox=novo;
            printf("%s",novo->ant->nome);
            //novo->ant=atual;
            //atual=atual->prox;
          }
          if(strcmp(novo->nome,nome)<strcmp(atual->prox->nome,nome)){
            novo->prox=atual->prox;
            novo->ant=atual->prox->ant;
            atual->prox=novo;
            atual->prox->ant=novo;
          }
        }
      }

    }

  printf("\n_____Contato adicionado_____\n\n\n");

  return novo;
}

void imprime(Agenda *l){
  Agenda *ag;
/*  if(vazia(l)){
    printf("Lista vazia\n");
    return ;
  }
*/
  if(l==NULL)
    printf("\n\nNão possui nenhum registro :(\n");
  else
    printf("\n\nVisualizar registros:\n");
  for(ag=l; ag!=NULL; ag=ag->prox){
    printf("Nome: %s\n", ag->nome);
  }
  printf("\n\n\n");
}

Agenda *apaga_contato(Agenda *l){//, char *nome_remover){
  //Agenda *ant = NULL;
  //Agenda *aux = l;


  char nome[101];

  printf(" -----------------------------\n");
  printf("|       apagar registro      |\n");
  printf(" -----------------------------\n");
  printf("2 - Digite o registro que deseja apagar:  ");
  getchar();
  scanf("%[^\n]", nome);

  Agenda *aux = buscaRegistro(l, nome);

  /* Verifica se achou o elemento */
  if(aux==NULL){
    printf("\n\n!!! Não achou o registro solicitado.\n\n");
    return l;
  }
  /* Retira elemento */
  if(l==aux){
    /* retira do início */
    l = aux->prox;
  } else {
    /* retira do meio */
    aux->ant->prox = aux->prox;
  }

  if(aux->prox != NULL)
    aux->prox->ant=aux->ant;

  printf("\nRegistro removido!\n\n");

  free(aux);
  return l;
}

/* Função de busca */
void *busca(Agenda *l){

  char nome[101];

  printf(" -----------------------------\n");
  printf("|        buscar registro      |\n");
  printf(" -----------------------------\n");
  printf("3 - Digite o registro que deseja buscar:  ");
  getchar();
  scanf("%[^\n]", nome);

  Agenda *aux;
  int achou = 0;
  for(aux=l; aux!=NULL; aux=aux->prox){
    if(strcmp(aux->nome, nome)==0){
      printf("\n\nACHOUU!!<o/ \n\nNome: %s\n",aux->nome);
      printf("Telefone: %s\n", aux->telefone);
      printf("Endereco: %s\n", aux->endereco);
      printf("CEP: %d\n",aux->cep);
      printf("Data de nascimento: %s \n\n\n", aux->data);
      achou = 1;
    }
  }
  if(achou==0){
    printf("\n\n !!! Não foi encontrado\n\n");
  }

}

/* função de busca: busca um elemento na lista */
Agenda *buscaRegistro(Agenda *l, char nome[]){
  Agenda *aux;
  for(aux=l; aux!=NULL; aux=aux->prox){
    if(strcmp(aux->nome, nome)==0)
      return aux;
  }
  return NULL;
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
