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

} // Complexidade Const 🥴

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

} // Complexidade O(N)

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
} // Complexidade O(N)

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

    if(T->coef == 0){
        return SOMA(*((*P)->prox), *((*Q)->prox));
    }

    T->prox = SOMA(*((*P)->prox), *((*Q)->prox));
    return T;
} // Complexidade O(N + M) 😐

void MonProd(*P, c, g){

    if(P == NULL){ return; }

    P->coef *= c; P->grau += g;
    MonProd(P->prox, c, g);
    return;
    
} // Complexidade O(N) 


// R = PROD(&P, &Q);
POL PROD(*P, *Q){

    POL T0 = Pol_criar(), T1 = Pol_criar(), T2 = T2_criar();

    T0->coef = P->coef * Q->coef; T0->grau = P->grau + Q->grau;

    T1 = COPIA(&T1, P->prox); T2 = COPIA(&T2, Q->prox); //lixo

    MonProd(T1, Q->coef, Q->grau); MonProd(T2, P->coef, P->grau);

    T0->prox = SOMA( SOMA(T1, T2), PROD(P->prox, Q->prox) );

    return T0;

} //Complexidade é O(N^2 + M^2) 🫩


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