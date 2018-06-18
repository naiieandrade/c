#include<iostream>
#include<vector>
using namespace std;
class No {
public:
    int info;   // chave
    No* sae;    // ponteiro para a sub-árvore da esquerda
    No* sad;    // ponteiro para a sub-árvore da direita
    No (int i){ // construtor
        info = i;
        sae = sad = 0;
    }
    bool isFolha(){
        return (this->sae==0 && this->sad==0);
    }
};
class Arvore {
public:
    No* raiz;
    Arvore(){ // construtor-padrão
        raiz = 0;
    }
    No* localiza(int valor){
        No* atual = raiz;      // começamos pela raiz
        if (!atual) return 0;  // árvore vazia!
        while (atual->info != valor) {
            if (valor < atual->info) {
            	atual = atual->sae;
            } else {
                atual = atual->sad;
            }
            if (!atual) return 0;  // não há filho, não encontrou!
        }
        return atual;              // encontrou!
    }
    void insere(int valor) {
        No* novo = new No(valor);  // cria o novo nó
        if (!raiz) {
            raiz = novo;
            return;
        }
        No* atual = raiz;  // começamos pela raiz
        No* pai = 0;       // guardamos o pai de cada um
        while (true) {
            pai = atual;   // atualiza o pai a cada iteração
            if (valor < atual->info) { // vai para esquerda?
                atual = atual->sae;
                if (!atual) {          // fim da linha?
                    pai->sae = novo;   // insere aqui
                    return;
                }
            } else {
                atual = atual->sad;    // vai para direita?
                if (!atual) {          // fim da linha?
                    pai->sad = novo;   // insere aqui
                    return;
                }
            }
        }
    }
    void emOrdem(No* atual) {
        if (!atual) return;  // no vazio?
        emOrdem(atual->sae);
        cout << atual->info << " ";
        emOrdem(atual->sad);
    }
    void preOrdem(No* atual) {
        if (!atual) return;
        cout << atual->info << " ";
        preOrdem(atual->sae);
        preOrdem(atual->sad);
    }
    void posOrdem(No* atual) {
        if (!atual) return;
        posOrdem(atual->sae);
        posOrdem(atual->sad);
        cout << atual->info << " ";
    }
    int menor(){
        No* atual = raiz;
        if (!atual) return 0;
        while(atual->sae){
            atual = atual->sae;
        }
        return atual->info;
    }
    int maior(){
        No* atual = raiz;
        if (!atual) return 0;
        while(atual->sad){
            atual = atual->sad;
        }
        return atual->info;
    }
    No* sucessor(No* atual){
        No* pai = atual;
        atual = atual->sad; // primeira à direita
        if (atual->sae != 0){
            while(atual->sae != 0){
                pai = atual;
                atual=atual->sae;
            }
            if (atual->sad != 0){
                pai->sae = atual->sad;
            } else {
                pai->sae = 0;
            }
        } else {
            pai->sad = atual->sad;
        }
        return atual;
    }
    void remove(int valor){
        No* atual = raiz; // começamos pelo início :-)
        No* pai = 0; // raiz não tem pai :-(
        while(atual->info != valor){
            pai = atual;
            if (valor < atual->info) {
                atual = atual->sae;
            } else {
                atual = atual->sad;
            }
            if (atual == 0) return; // não encontrou o valor a remover.
        }
        if (atual->sae==0 && atual->sad==0) { // remove folhas...
            if (atual == raiz) {
                raiz = 0;
                delete atual;
                return;
            }
            if (pai->sae == atual) {
                pai->sae = 0;
            } else {
                pai->sad = 0;
            }
            delete atual;
        } else if (atual->sad == 0) { // tem um filho esquerdo
            if (atual==raiz){
                raiz = atual->sae;
                delete atual;
                return;
            }
            if (pai->sae == atual){
                pai->sae = atual->sae;
            } else {
                pai->sad = atual->sae;
            }
        } else if (atual->sae == 0) { // tem um filho direito
            if (atual==raiz) {
                raiz = atual->sad;
                delete atual;
                return;
            }
            if (pai->sae == atual) {
                pai->sae = atual->sad;
            } else {
                pai->sad = atual->sad;
            }
            delete atual;
        }
        if (atual->sae!=0 && atual->sad!=0){ // remove nó com dois filhos
            No* suces = sucessor(atual);
            if (pai->sae == atual) {
                pai->sae = suces;
            } else {
                pai->sad = suces;
            }
            suces->sae = atual->sae;
            suces->sad = atual->sad;
            delete atual;
        }
    }
    int nivel(int valor){
        No* atual = raiz;      // começamos pela raiz
        if (atual==0) return 0;  // árvore vazia!
        int n = 1;
        while (atual->info != valor) {
            if (valor < atual->info) {
            	n++;
            	atual = atual->sae;
            } else {
                n++;
                atual = atual->sad;
            }
            if (atual==0) return 0;  // não há filho, não encontrou!
        }
        return n;
    }
    int altura(No* atual) {
        if (atual == 0) return 0; // a altura de uma árvore vazia é 0.
        int altEsq = altura(atual->sae);
        int altDir = altura(atual->sad);
        if (altEsq > altDir) return altEsq + 1;
        else return altDir + 1;
    }
    int qtdNos(No* atual) {
        if (atual == 0) return 0; // a altura de uma árvore vazia é 0.
        int qtdEsq = qtdNos(atual->sae);
        int qtdDir = qtdNos(atual->sad);
        return qtdEsq + qtdDir;
    }
    void insereBal(int vet[], int ini, int fim) {
        if (fim < ini) return;
        int meio = (ini + fim)/2;
        insere(vet[meio]);
        insereBal(vet,ini,meio-1);
        insereBal(vet,meio+1,fim);
    }
};
int main() {
    int tam;    // tamanho do vetor ou quantidade de elementos da árvore
    int *vet;   // vetor auxiliar na montagem da árvore balanceada
    Arvore arv; // árvore
    cout << "Informe a quantidade de nos da arvore: ";
    cin  >> tam;
    vet = new int[tam];
    // insere no vetor para depois ordenar
    for (int i = 0; i < tam; i++)	{
        cout << "Digite o proximo elemento: ";
        cin  >> vet[i];
        // vet[i] = i+1;
	}
	//ordenando o vetor
	int aux;
	for (int i = 0; i < tam-1; i++){
	    for (int j = 0; j < tam-1-i; j++){
	        if (vet[j] > vet[j+1]) { // troca
	            aux = vet[j];
	            vet[j] = vet[j+1];
	            vet[j+1] = aux;
	        }
	    }
	}
    // criando a árvore balanceada!
    arv.insereBal(vet, 0, tam-1);
    cout << "Pre-ordem...\n";
    arv.preOrdem(arv.raiz);
    cout << "\nAltura: " << arv.altura(arv.raiz) << endl;
	//system("PAUSE");
	return 0;//EXIT_SUCCESS;
}
