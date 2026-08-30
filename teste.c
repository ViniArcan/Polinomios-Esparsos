#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <teste.h>


POL Pol_criar(){
    POL P;
    P.grau = 0;
    P.coef = 0;
    P.prox = NULL;

    return P;
}

void COPIA(POL *Q, POL *P){
    Q->coef = P->coef; Q->grau = P->grau;
    if (P->prox != NULL){
        if( Q->prox == NULL ){
            Q->prox = Pol_criar();
        }
        COPIA(Q->prox, P->prox);
        return;
    }
    Q->prox = NULL;
    return;
}

void ADD(POL *P, int c, unsigned long long g){
    POL *Rem, *Pos = P;
    while( (g > Pos->grau) && (Pos != NULL) ){
        Rem = Pos;
        Pos = P->prox;
    }
    if( g == Pos->grau ){
        Pos->coef += c;
        return;
    }
    POL T = Pol_criar(); T.grau = g; T.coef = c; T.prox = Pos;
    Rem->prox = *T;
    return;
}

/*
POL SOMA(POL *P, POL *Q, POL *R){
    int N = P->num + Q-> num;
    POL R = Pol_criar(N);

    for(int i = 0; i<N)
}*/

bool SOMA(POL **P, POL **Q, POL *R){
    if ((*Q)->grau > (*P)->grau){
        R->grau = (*P)->grau; R->coef = (*P)->coef;
        if((*P)->prox == NULL){
            COPIA(R->prox, *Q);
            return TRUE;
        }
        return SOMA(*((*P)->prox), Q, R->prox);
    }
    if ((*P)->grau > (*Q)->grau){
        R->grau = (*Q)->grau; R->coef = (*Q)->coef;
        if((*Q)->prox == NULL){
            COPIA(R->prox, *P);
            return TRUE;
        }
        return SOMA(P, *((*Q)->prox), R->prox);
    }
    R->coef = P->coef + Q->coef; R->grau = P->grau;
    return TRUE;
}

bool PROD(POL **P, POL **Q, POL *R){
    if (Q.Seq == NULL){
        if(P.Seq == NULL){
            R.coef = Q.coef*P.coef; R.grau = Q.grau + P.grau;
            R.Seq = NULL;
            return TRUE;
        }
        R.coef = Q.coef*P.coef; R.grau = Q.grau + P.grau;
        return PROD(P.Seq, Q, R.Seq);
    }
    if (P.Seq == NULL){
        if(P.Seq == NULL){
            R.coef = Q.coef*P.coef; R.grau = Q.grau + P.grau;
            R.Seq = NULL;
            return TRUE;
        }
        R.coef = Q.coef*P.coef; R.grau = Q.grau + P.grau;
        return PROD(P, Q.Seq, R.Seq);
    }
    R.grau = P.grau; R.coef = P.coef + Q.coef;
    return TRUE;
}
*/