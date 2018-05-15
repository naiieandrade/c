#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct lista
{
  int valor;
  char *nome;
  struct lista *prox;
};

typedef struct lista Lista;

// Cria lista vazia
Lista *inicializa(void)
{
  return NULL;
}

// Inserção no  início: retorna a lista atualizada
Lista *insereInicio(Lista *l, int i, char *nome)
{
  Lista *novo = (Lista*)malloc(sizeof(Lista));
  novo->valor = i;
  novo->nome=nome;
  novo->prox = l;
  return novo;
}

// Imprime valores da lista
void imprime(Lista *l)
{
  Lista *p;
  for(p=l; p!=NULL; p=p->prox)
  {
  //  int num = (int)l->valor;
    //if(p->valor!=NULL){ //funciona +-, como resolver isso?
      printf("info = %d\n", p->valor);
      printf("nome = %s\n", p->nome );
    //}

  }

}

// Verifica se a lista está vazia
int vazia(Lista *l)
{
  if(l==NULL)
    return 1;
  else
    return 0;
  //return (l==NULL);
}

// Função de busca
void *busca(Lista *l, int v)
{
  Lista *p;
  for(p=l; p!=NULL; p=p->prox)
  {
    if(p->valor==v)
      //return p;
      printf("VALOR E %d",p->valor);
  }
  //return NULL;
}

// Função retira: retira elemento da Lista
Lista *retira (Lista *l, int v)
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

void libera(Lista *l){
  Lista *p=l;
  while (p!=NULL) {
    Lista *t = p->prox; /*guarda referencia para o proximo elemento */
    free(p); //libera a memória apontada por p
    p=t; //faz p apontar para o proximo
  }
}

// Tamanho da lista
int tamanho(Lista *l){
  if(l==NULL) return 0;
  int cont = 0;
  Lista *no=l; //*l -> primeiro elemento da lista?
  while(no!=NULL){
    cont++;
    no=no->prox;
  }
  return cont;
}
/*
// Função retira: retira elemento da lista
Lista *retira(Lista *l, int v){
  Lista *ant = NULL; //ponteiro para o elemento anterior
  Lista *p = l; //ponteiro para percorrer a lista

  //procura elemento na lista, guardando anterior
  while(p!=NULL &&p->valor != v){
    ant=p;
    p=p->prox;
  }
  //verifica se achou elemento
  if(p==NULL){
    //retira elemento do inicio
    l=p->prox;
  }
  else {
    //retira elemento do meio da lista
    ant->prox=p->prox;
  }
  free(p);
  return l;
}*/

// Insere no meio


// Insere no fim
Lista *insere_fim(Lista *l, int i, char *nome){
  //if(l==NULL) return 0;
  Lista *novo = (Lista *)malloc(sizeof(Lista));
  novo->valor=i;
  novo->nome=nome;
  novo->prox = NULL;

  if(l==NULL){//lista vazia: insere inicio
    l=novo;
  } else {
    Lista *aux = l;
    while(aux->prox !=NULL){
      aux=aux->prox;
    }
    aux->prox=novo;
  }

}


// Insere ordenada


int main ()
{

  char *nome;
  nome = (char *)malloc(30*sizeof(char));
  nome = "naiara";
  Lista *l;
  l = inicializa(); /* para atualizar nas funções a lista deve ser acessada
                    por (Lista **l) e o conteúdo por (*l) */
  l = insereInicio(l,23, nome);
  l = insereInicio(l,45,"lucas");
  l = insereInicio(l,25,"pedro");
  l = insereInicio(l,15,"amanda");
  /*l = insere_fim(l,23, "amanda naiara");
  l = insere_fim(l,14,"lucas");
  l = insere_fim(l,13,"joao lucas");
  l = insere_fim(l,15,"maria");
  */imprime(l);
  int num=0;
  /*printf("Digite o valor :\n");
  scanf("%d", &num );
  busca(l,num);
  *///retira(l,45);
  //printf("depois de tirar...\n");
  l=retira(l,15);
  imprime(l);
  int x = tamanho(l);

  printf("TAMANHO %d\n", x);
  libera(l);
  return 0;
}
