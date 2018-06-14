#include<stdio.h>
#include<stdlib.h>

typedef struct node{
  int key;
  struct node* esq;
  struct node* dir;
  int height;
} Node;

int max(int a, int b){
  return (a>b)? a:b;
}

int height(Node* n){
  if(n==NULL)
    return 0;
  return n->height;
}

/* NULL esq e dir*/
Node* newNode(int key){
  Node* node = (Node*)malloc(sizeof(Node));
  node->key = key;
  node->esq = NULL;
  node->dir = NULL;
  node->height = 1; // é inicializado add na folha?
  return (node);
}

Node* rightRotate(Node * y){
  Node* x = y->esq;
  Node* T2 = x->dir;

  x->dir = y;
  y->esq = T2;

  y->height = max(height(y->esq), height(y->dir))+1;
  x->height = max(height(x->esq), height(y->dir))+1;

  return x;
}

Node* leftRotate(Node* x){
  Node* y = x->dir;
  Node* T2 = y->esq;

  y->esq = x;
  x->dir = T2;

  x->height = max(height(x->esq), height(x->dir))+1;
  y->height = max(height(y->esq), height(x->dir))+1;

  return y;
}

int getBalance(Node * n){
  if(n == NULL)
    return 0;
  return height(n->esq) - height(n->dir);
}

Node* insert(Node* node, int key){
  /* 1. Inserção BST */
  if(node == NULL)
    return(newNode(key));

  if(key < node->key)
    node->esq = insert(node->esq, key);
  else if(key > node->key)
    node->dir = insert(node->dir, key);
  else // chaves iguais não no BST
    return node;

  /* 2. Atualiza a altura do nó ancestral */
  node->height = 1 + max(height(node->esq), height(node->dir));

  /* 3. Ver o fator de balanceamento desde nó para ver
        se o nó desbalanceou */
  int balance = getBalance(node);

  /* Se o nó ficou desbalanceado, existem 4 casos */

  // Left Left Case
  if (balance > 1 && key < node->esq->key)
    return rightRotate(node);

  // Right Right Case
  if (balance < -1 && key > node->dir->key)
    return leftRotate(node);

  // Left Right Case
  if (balance > 1 && key > node->esq->key){
    node->esq = leftRotate(node->esq);
    return rightRotate(node);
  }

  // Right Left Case
  if (balance < -1 && key < node->dir->key){
    node->dir = rightRotate(node->dir);
    return leftRotate(node);
  }

  /* retortna o node (não modificado) */
  return node;
}

/* Print pre-order */
void preOrder(Node* root){
  if(root != NULL){
    printf("%d ", root->key);
    preOrder(root->esq);
    preOrder(root->dir);
  }
}

/* Print in-order */
void inOrder(Node* root){
  if(root != NULL){
    inOrder(root->esq);
    printf("%d ", root->key);
    inOrder(root->dir);
  }
}

/* Print post-order */
void postOrder(Node* root){
  if(root != NULL){
    postOrder(root->esq);
    postOrder(root->dir);
    printf("%d ", root->key);
  }
}

int main(){
  Node* node = NULL;

  node = insert(node, 1);
  node = insert(node, 2);
  node = insert(node, 3);
  node = insert(node, 4);
  node = insert(node, 5);
  node = insert(node, 6);

  printf("Print pre order: \n");
  preOrder(node);


  printf("\n\nPrint in order: \n");
  inOrder(node);

  printf("\n\nPrint post order: \n");
  postOrder(node);

  return 0;
}
