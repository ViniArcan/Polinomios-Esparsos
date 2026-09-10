#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <teste.h>

typedef struct POL_ POL;

struct POL_{

    unsigned long long grau;
    int coef;
    POL *prox;

}

POL Pol_criar(){

    POL *P;

    P = (POL*) malloc(sizeof(POL));

    P.grau = 0;
    P.coef = 0;
    P.prox = NULL;

    return P;

} // Complexidade Const 🥴

void LIBERA(POL *P){
    if(P == NULL){
        return;
    }
    LIBERA(P->prox);
    free(P);
    return;
}

void COPIA(POL **Q, POL **P){

    if( Q == NULL ){

        Q = Pol_criar();

    }

    Q->coef = P->coef; Q->grau = P->grau;

    if (P->prox != NULL){

        COPIA(Q->prox, P->prox);
        return;

    }

    if(Q->prox != NULL){
        LIBERA(Q->prox);
    }
    Q->prox = NULL;
    return;

} // Complexidade O(N)

void ADD(POL *P, int c, unsigned long long g){

    POL *Pos = P;

    while( ((Pos->prox) != NULL) && (g > (Pos->prox)->grau) ){
        Pos = P->prox;
    }

    if( ((Pos->prox) != NULL) && (g == (Pos->prox)->grau) ){

        if(c == -((Pos->prox)->coef)){

            POL *Aux = Pos->prox;
            Pos->prox = (Pos->prox)->prox;
            free(Aux);
            return;

        }

        (Pos->prox)->coef += c;
        return;

    }

    POL *T; T = (POL*) malloc(sizeof(POL)); T.grau = g; T.coef = c; T.prox = Pos->prox;
    Pos->prox = T;

    return;
} // Complexidade O(N)

/*
void ADD(POL **P, int c, unsigned long long g){
    
    if(*P != NULL){
        if( g > (P->prox)->grau ){
            ADD(P->prox, c, g)
            return;
        }
        if( g == (P->prox)->grau ){
            if(c == -((P->prox)->coef)){
                P->prox = (P->prox)->prox;
                free(P->prox);
                return;
            }
            (P->prox)->coef += c;
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
POL SOMA(POL *P, POL *Q){

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
            return T;

        }

        T->prox = SOMA(*((*Q)->prox), P);
        return T;
    }

    T->coef = P->coef + Q->coef; T->grau = P->grau;

    if(T->coef == 0){
        free(T);
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


// R = PROD(&P, &Q); R = (p0 + Pp) * (q0 + Qp) = p0*q0 + q0*Pp + p0*Qp + Pp*Qp
POL PROD(*P, *Q){

    POL T0 = Pol_criar();

    if(P->prox == NULL){
        COPIA(&T0, Q);
        MonProd(T0, P->coef, P->grau);
        return T0;
    }
    if(Q->prox == NULL){
        COPIA(&T0, P);
        MonProd(T0, Q->coef, Q->grau);
        return T0;
    }

    POL T1 = Pol_criar(), T2 = Pol_criar();

    T0->coef = P->coef * Q->coef; T0->grau = P->grau + Q->grau;

    COPIA(&T1, P->prox); COPIA(&T2, Q->prox);

    MonProd(T1, Q->coef, Q->grau); MonProd(T2, P->coef, P->grau);

    POL T01 = SOMA( &(&T1), &(&T2) ); T02 = PROD(P->prox, Q->prox);

    LIBERA(&T1); LIBERA(&T2);

    T0.prox = SOMA( &(&T01), &(&T02) );

    LIBERA(&T01); LIBERA(&T02);

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