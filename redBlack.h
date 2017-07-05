

#ifndef REDBLACK_H
#define REDBLACK_H

typedef struct rb
{
    int raiz;
    char cor;
    struct rb *esq;
    struct rb *dir;
    struct rb *pai;
}rb;


rb *inicializaArvore();
rb *criaNo(int valorNo);

void insereNoRB(rb *A, int valorNo);


void rotacaoEsq(rb *A, rb *noDesbalanceado);

void rotacaoDir(rb *A, rb *noDesbalanceado);


void percorreOrdem(rb *A);

void balanceamentoRBInsercao(rb *A, rb *noInserido);

void atualizaCorRemocao(rb *A, rb *x, rb *noPai );
void removeNo(rb *A, int valor);

#endif /* REDBLACK_H */

