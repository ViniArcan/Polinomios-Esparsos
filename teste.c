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

    if( Q == NULL ){

        Q = Pol_criar();

    }

    Q->coef = P->coef; Q->grau = P->grau;

    if (P->prox != NULL){

        COPIA(Q->prox, P->prox);
        return;

    }

    Q->prox = NULL;
    return;

}

void ADD(POL *P, int c, unsigned long long g){

    POL *Rem, *Pos = P;

    while( (Pos != NULL) && (g > Pos->grau) ){

        Rem = Pos;
        Pos = P->prox;

    }

    if( (Pos != NULL) && (g == Pos->grau) ){

        if(c == -(Pos->coef)){

            Rem->prox = Pos->prox;
            //LIBERA(Pos);
            return;

        }

        Pos->coef += c;
        return;

    }

    POL T = Pol_criar(); T.grau = g; T.coef = c; T.prox = Pos;
    Rem->prox = *T;

    return;
}

/*
void ADD(POL *P, int c, unsigned long long g){
    if(*P != NULL){
        if( g > P->grau ){
            ADD(P->prox, c, g)
            return;
        }
        if( g == P->grau ){
            if(c == -(P->coef)){
                //preguiça de pensar como fazer isso com recursão
            }
            P->coef += c;
            return;
        }
    }
    else{
        *P = Pol_criar(); P->coef = c; P->grau = g;
        return;
    }
    POL T = Pol_criar(); T.grau = P->grau; T.coef = P->coef; T.prox = P->prox;
    P->coef = c; P->grau = g; P->prox = &T;
    return;
}
*/

/*
POL SOMA(POL *P, POL *Q, POL *R){
    int N = P->num + Q-> num;
    POL R = Pol_criar(N);

    for(int i = 0; i<N)
}*/

// R = SOMA( &&P, &&Q);
POL SOMA(POL **P, POL **Q){

    POL T = Pol_criar();

    if ((*Q)->grau > (*P)->grau){

        T->grau = (*P)->grau; T->coef = (*P)->coef;

        if((*P)->prox == NULL){

            COPIA(T->prox, *Q);
            return T;

        }

        T->prox = SOMA(*((*P)->prox), Q);
        return T;
    }

    if ((*P)->grau > (*Q)->grau){

        T->grau = (*Q)->grau; T->coef = (*Q)->coef;

        if((*Q)->prox == NULL){

            COPIA(T->prox, *P);
            return t;

        }

        T->prox = SOMA(*((*Q)->prox), P);
        return T;
    }

    T->coef = P->coef + Q->coef; T->grau = P->grau;

    if(R->coef == 0){
        return SOMA(*((*P)->prox), *((*Q)->prox));
    }

    T->prox = SOMA(*((*P)->prox), *((*Q)->prox));
    return T;
}

/*
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