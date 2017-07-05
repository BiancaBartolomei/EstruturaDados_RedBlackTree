#include <stdio.h>
#include <stdlib.h>
#include "redBlack.h"

//Cria a sentinela que aponta para o endereco da arvore
rb *inicializaArvore()
{
    rb *sentinela;
    sentinela = (rb*)calloc (1,sizeof(rb));
    sentinela->raiz = -1000;
    sentinela->esq = NULL;
    sentinela->dir = NULL;
    sentinela->pai = NULL;
    sentinela->cor = 'p'; //A sentinela tem que ser preta
    return sentinela;
}
//Cria um novo no para ser inserido na arvore
rb *criaNo(int valorNo){
    rb *novoNo;
    novoNo = (rb*)calloc (1,sizeof(rb));
    novoNo->raiz = valorNo;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->pai = NULL;
    novoNo->cor = 'v'; //todo novo no inserido na arvore e uma folha, portanto sua cor e vermelho
    return novoNo;
}
//Insere um novo dado na arvore
void insereNoRB(rb *A, int valorNo){
    rb *novoNo;
    novoNo = criaNo(valorNo);//cria um novo no que sera alocado na arvore
    rb *noAtual = A->dir;
    rb *noPai = A;
    //procura o local certo, onde deve ficar esse novo no
    while (noAtual != NULL)
    {
        if (valorNo > noAtual->raiz)
        {
            noPai = noAtual;
            noAtual = noAtual->dir;
        }
        else
        {
            noPai = noAtual;
            noAtual = noAtual->esq;
        }
    }
    //com relacao ao pai desse novo no, insere-o na posicao correta, ou seja a esquerda ou a direita do no que sera seu pai
    if (valorNo > noPai->raiz)
        noPai->dir = novoNo;
    else
        noPai->esq = novoNo;
    //liga o novo no ao no que sera seu pai
    novoNo->pai = noPai;
    //balancear a RedBlack
    balanceamentoRBInsercao(A, novoNo);
    return;
}
//passa imprimindo a arvore em ordem
void percorreOrdem (rb *A)
{
    if (A == NULL){
    	return;
	}
        
    percorreOrdem(A->esq);
    printf(" %d %c -- ", A->raiz, A->cor);
    percorreOrdem(A->dir);
}
//funcao para balancear a arvore caso a altura de preto esteja desbalanceada
void balanceamentoRBInsercao(rb *A, rb *z)
{
    //Na insercao, deve-se olhar o tio para se ter nocao do balanceamento
    char corTio;
    rb *pai = z->pai;
    rb *avo = pai->pai;
    rb *tio;
    //so e necessario o balanceamento se o no pai for vermelho, 
    //porque quebra a regra de que um pai vermelho nao pode ter filhos vermelhor
    if(pai->cor == 'v'){
        if(z->raiz < avo->raiz){ //checa se o no inserido esta a esquerda do avo
            tio = avo->dir;
            if(tio==NULL) //nos nulos sao sempre pretos
                corTio = 'p';
            else
                corTio = tio->cor;
            //Primeiro caso
            if(corTio == 'v'){
                pai->cor = 'p'; //colore pai de preto
                tio->cor = 'p'; //colore tio de preto
                avo->cor = 'v'; //colore avo de vermelho
                balanceamentoRBInsercao(A, avo); //nova avalicao sobre o avo
            }
            //Segundo caso
            if((corTio == 'p') && (z->raiz > pai->raiz)){
                z = pai;
                rotacaoEsq(A, z);
                pai = z->pai;
                //Leva ao caso 3
            }
            //Terceiro caso
            if((corTio == 'p') && (z->raiz < pai->raiz)){
                pai->cor = 'p'; //colore pai de preto
                avo->cor = 'v'; //colore avo de vermelho
                rotacaoDir(A, avo);
            }
        }else{ //se o no inserido esta a direita do avo
            tio = avo->esq;
            if(tio==NULL)
                corTio = 'p';
            else
                corTio = tio->cor;
            //Primeiro caso
            if(corTio == 'v'){
                pai->cor = 'p';
                tio->cor = 'p';
                avo->cor = 'v';
                balanceamentoRBInsercao(A, avo);
            }
            //Segundo caso
            if((corTio == 'p') && (z->raiz < pai->raiz)){
                z = pai;
                rotacaoDir(A, z);
                pai = z->pai;
            }
            //Terceiro caso
            if((corTio == 'p') && (z->raiz > pai->raiz)){
                pai->cor = 'p';
                avo->cor = 'v';
                rotacaoEsq(A, avo);
            }
        }
    }
    A->dir->cor = 'p'; //garante que a raiz sempre sera preta
   
    return;
}
//Rotacao a esquerda
void rotacaoEsq(rb *A, rb *noDesbalanceado)
{
  
    rb *filho = noDesbalanceado->dir;
    noDesbalanceado->dir = filho->esq;//liga o filho da esquerda do filho na direita do no desbalanceado
    
    if(filho->esq != NULL){ //checa se o filho nao e nulo
    	filho->esq->pai = noDesbalanceado; //se nao for, declara como pai do filho a esquerda de filho como o no desbalanceado
    }
	filho->esq = noDesbalanceado; //o no desbalanceado vira filho a esquerda do filho
	filho->pai = noDesbalanceado->pai; //o pai do no desbalanceado vira o pai do filho
	if(filho->pai->raiz <= filho->raiz) //localiza se o filho deve ser o da direita ou esquerda do seu pai
		filho->pai->dir = filho;
	else 
		filho->pai->esq = filho;
	noDesbalanceado->pai = filho; //o filho vira pai do no desbalanceado
    return;
}
//Rotacao a esquerda
void rotacaoDir(rb *A, rb *noDesbalanceado)
{
    rb *filho = noDesbalanceado->esq;
    noDesbalanceado->esq = filho->dir;

    //Realiza a rotaÃ§Ã£o
    if(filho->dir != NULL){
        
    	filho->dir->pai = noDesbalanceado;
	}
	filho->dir = noDesbalanceado;
	filho->pai = noDesbalanceado->pai;
	if(filho->pai->raiz >= filho->raiz)
		filho->pai->esq = filho;
	else 
		filho->pai->dir = filho;
	noDesbalanceado->pai = filho;
	
 

    return;
}
//Remocao do no da RedBlack
void removeNo(rb *A, int valor)
{
    rb *noAux = A->dir;
    char corR;
    rb *x;
    //procura pelo no a ser removido
    while (noAux != NULL && noAux->raiz != valor)
    {
        if (valor > noAux->raiz)
            noAux = noAux->dir;
        else
            noAux = noAux->esq;
    }
    //se saiu do loop porque atingiu a condicao NULOe porque o no nao existe na arvore
    if (noAux == NULL)
    {
        printf("O no nao existe na arvore\n");
        return;
    }
    
    //Testa se o no tem dois filhos
    if (noAux->esq != NULL && noAux->dir != NULL)
    {
        //caso tenha, deve-se procurar pelo seu sucessor
        //sucessor = no a direita, mais a esquerda
        rb *sucessor = noAux->dir;
        
        while (sucessor->esq != NULL)
            sucessor = sucessor->esq;
        //Copia o sucessor para o local do no a ser retirado
        //Exclusao por copia
        noAux->raiz = sucessor->raiz;
        noAux = sucessor;
        
    }
    
    //guarda o pai do no removido
    rb *noPai = noAux->pai;
    corR = noAux->cor;
    //testa se o no e uma folha
    if (noAux->esq == NULL && noAux->dir == NULL)
    {
        if (noAux == noPai->esq)
            noPai->esq = NULL;
        else
            noPai->dir = NULL;
        free(noAux);
        if(A->dir==NULL)
            return;
        x = NULL;
    }
    else{ //se nao, e porque tem um filho
        if(noPai->dir == noAux){
            if(noAux->dir != NULL){//checa se e filho da direita
                x = noAux->dir;
                noPai->dir = noAux->dir;
                
            }
            if(noAux->esq != NULL){ //checa qual dos seus filhos e nao nulo
                x = noAux->esq;
                noPai->dir = noAux->esq;
                
            }
        }
        if(noPai->esq == noAux){
           if(noAux->dir != NULL){
               x = noAux->dir; 
               noPai->esq = noAux->dir;
               noAux->dir->pai = noPai;
            }
            if(noAux->esq != NULL){
               x = noAux->esq;
                noPai->esq = noAux->esq;
                
            }
        }
        
        free(noAux);
    }
    //se a cor do no que realmente foi removido e preta
    if(corR == 'p')  //passa a sentinela, o no que ficou no lugar e o seu pai  
        atualizaCorRemocao(A, x, noPai);
    return;
}

//Balanceamento da remocao
void atualizaCorRemocao(rb *A, rb *noAux, rb *noPai){
    //se o no que ficou no lugar e nao era nulo e se sua cor e vermelha
    //noAux = y = sucessor
    if(noAux!= NULL && noAux->cor == 'v'){
        noAux->cor = 'p'; //colore de preto
        
    }
    else{
        //se for nulo ou se a cor for preta
       //a remocao toma por base o irmao
        if(noAux == noPai->esq){ //checa se o no a ser balanceado esta a esquerda do pai
            rb *irmao = noPai->dir;
            char corIrmao = irmao->cor;
            //primeiro caso
            if(corIrmao == 'v'){
                irmao->cor = 'p';//colore o irmao de preto
                noPai->cor = 'v'; //colore o pai de vermelho
                rotacaoEsq(A, noPai);//rotacao a esquerda do pai
                irmao = noPai->dir; //irmao = filho da direita do pai de noAux
                corIrmao = irmao->cor;
                //leva aos casos 1, 2 ou 3
            }
            //segundo caso = irmao preto e os dois filhos sao pretos
            if(corIrmao == 'p'&& (irmao->dir == NULL || (irmao->dir!= NULL && irmao->dir->cor=='p')) && (irmao->esq == NULL || (irmao->esq!= NULL && irmao->esq->cor=='p'))){
                if(noPai->cor == 'v'){//se o pai for vermelho
                    irmao->cor = 'v'; //colore o irmao de vermelho
                    noPai->cor= 'p'; //colore o pai de preto
                }else{ // se o pai for preto
                    irmao->cor = 'v'; //colore o irmao de vermelho
                }
            }
           //terceiro caso = irmao preto, filho da esquerda pe vermelho e o da direita e preto
            if(irmao->cor == 'p'&& (irmao->esq != NULL && irmao->esq->cor=='v') &&(irmao->dir == NULL || (irmao->dir!= NULL && irmao->dir->cor=='p'))){
                irmao->esq->cor = 'p'; //colore de preto o filho da esquerda do irmao
                irmao->cor = 'v'; //colore o irmao de vermelho
                rotacaoDir(A, noPai->dir); //irmao = filho da direita do pai de noAux
                irmao = noPai->dir; 
                corIrmao = irmao->cor;
                //leva ao caso 4 
            }
            //quarto caso = irmao preto e filho da direita vermelho
            if(irmao->cor=='p'&& irmao->dir != NULL && irmao->dir->cor=='v'){
                irmao->cor = noPai->cor; //colore o irmao com a cor do pai
                noPai->cor = 'p'; //colore o pai de preto
                irmao->dir->cor = 'p'; //colore filho direio do irmao de preto
                rotacaoEsq(A, noPai);
        
            }
        }else{
            rb *irmao = noPai->esq;
            char corIrmao = irmao->cor;
           
            if(corIrmao == 'v'){
                irmao->cor = 'p';
                noPai->cor = 'v';
                rotacaoDir(A, noPai);
                irmao = noPai->esq;
                corIrmao = irmao->cor;
            }
            if(corIrmao == 'p'&& (irmao->esq == NULL || (irmao->esq!= NULL && irmao->esq->cor=='p')) && (irmao->dir == NULL || (irmao->dir!= NULL && irmao->dir->cor=='p'))){
                if(noPai->cor == 'v'){
                    irmao->cor = 'v';
                    noPai->cor= 'p';
                }else{
                    irmao->cor = 'v';
                }
                //checado
            }
            //checado
            if(irmao->cor == 'p'&& (irmao->dir != NULL && irmao->dir->cor=='v') &&(irmao->esq == NULL || (irmao->esq!= NULL && irmao->esq->cor=='p'))){
                irmao->dir->cor = 'p';
                irmao->cor = 'v';
                rotacaoEsq(A, noPai->esq);
                irmao = noPai->esq;
                corIrmao = irmao->cor;
            }
            if(irmao->cor=='p'&& irmao->esq != NULL && irmao->esq->cor=='v'){
                irmao->cor = noPai->cor;
                noPai->cor = 'p';
                irmao->esq->cor = 'p';
                rotacaoDir(A, noPai);
                //checado
            }
        }
    }
    A->dir->cor = 'p'; //raiz e sempre preta
}
//***********************************************************************
int main(){
	rb *arv;
	arv = inicializaArvore();
	
        insereNoRB(arv, 10);
	insereNoRB(arv, 8);
	//insereNoRB(arv, 10);
	//insereNoRB(arv, 11);
	//insereNoRB(arv, 7);
	//insereNoRB(arv, 21);
	/*insereNoRB(arv, 55);
	insereNoRB(arv, 11);
        insereNoRB(arv, 7);
	insereNoRB(arv, 4);
	insereNoRB(arv, 2);
	insereNoRB(arv, 15);
	insereNoRB(arv, 21);
	insereNoRB(arv, 33);
	insereNoRB(arv, 98);
        insereNoRB(arv, 9);
	insereNoRB(arv, 13);
	insereNoRB(arv, 16);
	insereNoRB(arv, 20);
	insereNoRB(arv, 22);
	insereNoRB(arv, 26);
	insereNoRB(arv, 50);
	insereNoRB(arv, 17);
        insereNoRB(arv, 19);
	insereNoRB(arv, 31);
	insereNoRB(arv, 51);
	insereNoRB(arv, 1);
	insereNoRB(arv, 0);
	
	*/
        /*insereNoRB(arv, 5);
	insereNoRB(arv, 10);
	insereNoRB(arv, 15);
	insereNoRB(arv, 2);
	insereNoRB(arv, 20);
	insereNoRB(arv, 18);
	insereNoRB(arv, 25);
	insereNoRB(arv, 30);*/
        percorreOrdem(arv->dir);
        
	removeNo(arv, 10);
        removeNo(arv, 8);
        //removeNo(arv, 8);
       // removeNo(arv, 10);
       // removeNo(arv, 8);
       
	printf("\n------------------------------------------------\n");
	if(arv->dir == NULL)
            printf("Arvore vazia");
        else
           percorreOrdem(arv->dir);
}
