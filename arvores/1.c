#include<stdio.h>
#include<stdlib.h>

struct arv{
  char info;
  struct arv* esq;
  struct arv* dir;
};

typedef struct arv Arv;

Arv* inicializa(void){
  return NULL;
}

Arv* cria(char c, Arv* sae, Arv* sad){
  Arv* p=(Arv*)malloc(sizeof(Arv));
  p->info = c;
  p->esq = sae;
  p->dir = sad;
  return p;
}

int vazia(Arv* a){
  return a==NULL;
}

void imprime(Arv* a){
  if(!vazia(a)){
    printf("<%c", a->info);
    imprime(a->esq);
    imprime(a->dir);
    printf(">");
  //  if(a==NULL)
    //  imprime("<>");
  } else{
    printf("<>");
  }
}

Arv* libera(Arv* a){
  if(!vazia(a)){
    libera(a->esq);
    libera(a->dir);
    free(a);
  }
  return NULL;
}


int main(){
  Arv* a;
  a = inicializa();

  Arv* a1=cria('d', inicializa(), inicializa());
  Arv* a2=cria('b', inicializa(), a1);
  Arv* a3=cria('e', inicializa(), inicializa());
  Arv* a4=cria('f', inicializa(), inicializa());
  Arv* a5=cria('c', a3, a4);
  Arv* d=cria ('a', a2, a5);
  d->esq->esq=cria('x',
                    cria('y', inicializa(),inicializa()),
                    cria('f', inicializa(),inicializa())
                );

  d->dir->esq = libera(d->dir->esq); // tem que fazer assim para liberar deixar NULL as filhas

  imprime(d);

  return 0;
}
