#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int valor;
    int altura;
    struct node *esq;
    struct node *dir;
} Node;

typedef Node* NODEPTR;

int altura(NODEPTR n) {
    return n == NULL ? -1 : n->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void atualiza_altura(NODEPTR n) {
    if (n != NULL)
        n->altura = 1 + max(altura(n->esq), altura(n->dir));
}

NODEPTR rot_dir(NODEPTR p) {
    NODEPTR q = p->esq;
    NODEPTR temp = q->dir;
    q->dir = p;
    p->esq = temp;
    atualiza_altura(p);
    atualiza_altura(q);
    return q;
}

NODEPTR rot_esq(NODEPTR p) {
    NODEPTR q = p->dir;
    NODEPTR temp = q->esq;
    q->esq = p;
    p->dir = temp;
    atualiza_altura(p);
    atualiza_altura(q);
    return q;
}

NODEPTR rot_esq_dir(NODEPTR p) {
    p->esq = rot_esq(p->esq);
    return rot_dir(p);
}

NODEPTR rot_dir_esq(NODEPTR p) {
    p->dir = rot_dir(p->dir);
    return rot_esq(p);
}

int fator(NODEPTR n) {
    return altura(n->esq) - altura(n->dir);
}

NODEPTR balancea(NODEPTR p) {
    atualiza_altura(p);
    int balance = fator(p);

    if (balance > 1) {
        if (fator(p->esq) >= 0) {
            printf("Rotacao simples direita (esquerda-esquerda)\n");
            return rot_dir(p);
        } else {
            printf("Rotacao dupla esquerda-direita (sinais trocados)\n");
            return rot_esq_dir(p);
        }
    } else if (balance < -1) {
        if (fator(p->dir) <= 0) {
            printf("Rotacao simples esquerda (direita-direita)\n");
            return rot_esq(p);
        } else {
            printf("Rotacao dupla direita-esquerda (sinais trocados)\n");
            return rot_dir_esq(p);
        }
    }
    return p;
}

NODEPTR inserir(NODEPTR raiz, int valor) {
    if (raiz == NULL) {
        NODEPTR novo = (NODEPTR)malloc(sizeof(Node));
        novo->valor = valor;
        novo->esq = novo->dir = NULL;
        novo->altura = 0;
        return novo;
    }

    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);

    return balancea(raiz);
}

void imprime_in_order(NODEPTR raiz) {
    if (raiz != NULL) {
        imprime_in_order(raiz->esq);
        printf("%d ", raiz->valor);
        imprime_in_order(raiz->dir);
    }
}

void executar_teste(const char* nome, int* vetor, int tamanho) {
    printf("\n--- %s ---\n", nome);
    NODEPTR raiz = NULL;
    int i; // <- Declara fora do for
    for (i = 0; i < tamanho; i++) {
        raiz = inserir(raiz, vetor[i]);
    }
    printf("Em ordem: ");
    imprime_in_order(raiz);
    printf("\n");
}

int main() {
    int caso1_simples_esq[] = {5, 15, 35}; 
    int caso1_simples_dir[] = {30, 20, 10}; 
    int caso2_dupla_esq_dir[] = {35, 5, 15}; 
    int caso2_dupla_dir_esq[] = {10, 30, 20}; 

    executar_teste("Caso 1 - Rotacao simples esquerda", caso1_simples_esq, 3);
    executar_teste("Caso 1 - Rotacao simples direita", caso1_simples_dir, 3);
    executar_teste("Caso 2 - Rotacao dupla esquerda-direita", caso2_dupla_esq_dir, 3);
    executar_teste("Caso 2 - Rotacao dupla direita-esquerda", caso2_dupla_dir_esq, 3);

    return 0;
}
//Alunos: 
//João Guilherme Camarota 202201638
//Yuri Cassiano Matsuoka 202302595