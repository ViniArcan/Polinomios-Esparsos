#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "teste.h"

typedef struct mon {
    long long int grau;
    long long int coef;
    struct mon *prox;
} MON;

struct pol {
    MON *inicio;
};

POL* criar_pol(void){

    POL *P = (POL*) malloc(sizeof(POL)); if (P == NULL){ return NULL; }

    P->inicio = NULL;

    return P;

}

MON* criar_mon(long long int c, long long int g) {
    MON *M = (MON*) malloc(sizeof(MON)); if (M == NULL) { return NULL; }
    
    M->coef = c; M->grau = g; M->prox = NULL;
    return M;
}

void LIBERA(POL *P){
    if(P == NULL){ return; }

    MON *Pos = P->inicio, *Aux;

    while(Pos != NULL){
        Aux = Pos->prox;
        free(Pos);
        Pos = Aux;
    }

    free(P);
    return;
}

bool LIMPA(POL *P){
    if(P == NULL){ return FALSE; }

    MON *Pos = P->inicio, *Aux;

    while(Pos != NULL){
        Aux = Pos->prox;
        free(Pos);
        Pos = Aux;
    }

    P->inicio = NULL;
    return TRUE;
}

bool COPIA(POL *Q, POL *P){

    if( (Q == NULL) || (P == NULL) ){ LIMPA(Q); return FALSE; }

    LIMPA(Q);

    MON *PosP = P->inicio; if(PosP == NULL){ return TRUE; }
    Q->inicio = criar_mon(PosP->coef, PosP->grau); if(Q->inicio == NULL){ return FALSE; }
    PosP = PosP->prox;
    MON *PosQ = Q->inicio;

    while(PosP != NULL){
        MON *Aux = criar_mon(PosP->coef, PosP->grau); if(Aux == NULL){ LIMPA(Q); return FALSE; }

        PosQ->prox = Aux;
        PosQ = Aux;

        PosP = PosP->prox;
    }

    return TRUE;
} // Complexidade O(N)

bool ADD(POL *P, long long int c, long long int g){
    
    if( P == NULL ){ return FALSE; }
    if( c == 0 ){ return TRUE; }

    if(P->inicio == NULL){
        P->inicio = criar_mon(c, g);
        return TRUE;
    }

    MON *Pos = P->inicio;

    if(g < Pos->grau){
        MON *M = criar_mon(c, g); if(M == NULL){ return FALSE; }
        M->prox = Pos; P->inicio = M;
        return TRUE;
    }
    if(g == Pos->grau){
        Pos->coef += c;
        if(Pos->coef == 0){
            P->inicio = Pos->prox;
            free(Pos);
        }
        return TRUE;
    }

    while( (Pos->prox != NULL) && (g > (Pos->prox)->grau) ){
        Pos = Pos->prox;
    }

    if( (Pos->prox != NULL) && (g == (Pos->prox)->grau) ){

        (Pos->prox)->coef += c;

        if((Pos->prox)->coef == 0){
            MON *Aux = Pos->prox;
            Pos->prox = (Pos->prox)->prox;
            free(Aux);
        }
        return TRUE;
    }

    MON *M = criar_mon(c, g); if(M == NULL){ return FALSE; }
    M->prox = Pos->prox;
    Pos->prox = M;
    return TRUE;
} // Complexidade O(N)

long long int COEF(POL *P, long long int g){

    if(P == NULL){ return 0; }

    MON *Pos = P->inicio; if(Pos == NULL){ return 0; }

    while( (Pos != NULL) && (g > Pos->grau) ){
        Pos = Pos->prox;
    }
    if((Pos != NULL) && (g == Pos->grau) ){
        return Pos->coef;
    }

    return 0;
}

bool REMOVE(POL *P, long long int g){
    if(P == NULL){ return FALSE; }
    
    MON *Pos = P->inicio; if(Pos == NULL){ return FALSE; }

    if(g == Pos->grau){
        P->inicio = Pos->prox;
        free(Pos);
        return TRUE;
    }
    while( (Pos->prox != NULL) && (g > (Pos->prox)->grau) ){
        Pos = Pos->prox;
    }
    if((Pos->prox != NULL) && (g == (Pos->prox)->grau) ){
        MON *Aux = (Pos->prox)->prox;
        free(Pos->prox);
        Pos->prox = Aux;
        return TRUE;
    }

    return FALSE;
}

bool REMOVEMENOR(POL *P){
    if(P == NULL){ return FALSE; }
    if(P->inicio == NULL){ return FALSE; }
    
    MON *Aux = (P->inicio)->prox;
    free(P->inicio);
    P->inicio = Aux;
    return TRUE;
}

long long int GRAU(POL *P){
    if(P == NULL){ return -1; }
    
    MON *Pos = P->inicio; if(Pos == NULL){ return -1; }

    while(Pos->prox != NULL){
        Pos = Pos->prox;
    }

    return Pos->grau;
}

POL* SOMA(POL*P, POL *Q){
    if( (P == NULL) || (Q == NULL) ){ return NULL; }

    MON *PosP = P->inicio, *PosQ = Q->inicio;

    POL *T = criar_pol(); if(T == NULL){ return NULL; }

    if(PosP == NULL){
        if(COPIA(T, Q)){
            return T;
        }
        LIBERA(T);
        return NULL;
    }
    if(PosQ == NULL){
        if(COPIA(T, P)){
            return T;
        }
        LIBERA(T);
        return NULL;
    }

    MON **PosT = &(T->inicio);

    while((PosP != NULL) && (PosQ != NULL)){

        if(PosP->grau < PosQ->grau){
            *PosT = criar_mon(PosP->coef, PosP->grau); if(*PosT == NULL){ LIBERA(T); return NULL; }
            PosT = &((*PosT)->prox);

            PosP = PosP->prox;
        }else if(PosQ->grau < PosP->grau){
            *PosT = criar_mon(PosQ->coef, PosQ->grau); if(*PosT == NULL){ LIBERA(T); return NULL; }
            PosT = &((*PosT)->prox);

            PosQ = PosQ->prox;
        }else{
            long long int s = PosP->coef + PosQ->coef;

            if(s != 0){
                *PosT = criar_mon( s, PosP->grau); if(*PosT == NULL){ LIBERA(T); return NULL; }
                PosT = &((*PosT)->prox);
            }
            
            PosP = PosP->prox; PosQ = PosQ->prox;
        }
    }

    MON *R = (PosP != NULL) ? PosP : PosQ;
    
    while (R != NULL) {
        *PosT = criar_mon(R->coef, R->grau); if(*PosT == NULL){ LIBERA(T); return NULL; }
        PosT = &((*PosT)->prox);
        R = R->prox;
    }

    return T;
} // Complexidade O(N + M) 😐



// R = PROD(&P, &Q); R = (p0 + Pp) * (q0 + Qp) = p0*q0 + q0*Pp + p0*Qp + Pp*Qp
POL* PROD(POL *P, POL *Q){

    if( (P == NULL) || (Q == NULL) ){ return NULL; }

    POL *T = criar_pol(); if(T == NULL){ return NULL; }

    if( (P->inicio == NULL) || (Q->inicio == NULL) ){ return T; }

    MON **PosT = &(T->inicio);

    MON *PosP = P->inicio, *PosQ = Q->inicio;

    while( (PosP != NULL) ){
        *PosT = SOMA(MonProd(Q, PosP->coef, PosP->grau), T); if(PosT == NULL){ LIBERA(T); return NULL}
        PosT = &((*PosT)->prox);
        PosP = PosP->prox;
    }

    return T;
} //Complexidade é O(N^2 + M^2) 🫩

void IMPRIME_AUX(MON *M){

    if(M == NULL){ return; }

    IMPRIME_AUX(M->prox);
    printf("%lld*x^%lld ", (M->coef), (M->grau));

    return;
}

bool IMPRIME(POL *P){

    if(P == NULL){ printf("-1\n"); return FALSE; }

    MON *M = P->inicio; if(M == NULL){ printf("-1\n"); return TRUE; }

    IMPRIME_AUX(M->prox);

    printf("%lld*x^%lld\n", (M->coef), (M->grau));

    return TRUE;

}

bool IMPRIMEINV(POL *P){

    if(P == NULL){ printf("-1\n"); return FALSE; }

    MON *Pos = P->inicio; if(Pos == NULL){ printf("-1\n"); return TRUE; }

    while(Pos->prox != NULL){
        printf("%lld*x^%lld ", (Pos->coef), (Pos->grau));
        Pos = Pos->prox;
    }

    printf("%lld*x^%lld\n", (Pos->coef), (Pos->grau));

    return TRUE;
}



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

/* *R = SOMA( &&P, &&Q);
POL *SOMA(POL *P, POL *Q){ 

    POL *T = Pol_criar();

    if (Q->grau > P->grau){

        T->grau = P->grau; T->coef = P->coef;

        if(P->prox == NULL){

            COPIA(T->prox, Q);
            return T;

        }

        T->prox = SOMA(P->prox, Q);
        return T;
    }

    if (P->grau > Q->grau){

        T->grau = Q->grau; T->coef = Q->coef;

        if(Q->prox == NULL){

            COPIA(T->prox, P);
            return T;

        }

        T->prox = SOMA(P, Q->prox);
        return T;
    }

    T->coef = P->coef + Q->coef; T->grau = P->grau;

    if(P->prox == NULL){
        if(Q->prox == NULL){
            if(T->coef == 0){ return NULL; }
            return T;
        }

        if(T->coef == 0){
            COPIA(T, Q->prox);
        }else{ COPIA(T->prox, Q->prox); }

        return T;
    }
    if(Q->prox == NULL){

        if(T->coef == 0){
            COPIA(T, P->prox);
        }else{ COPIA(T->prox, P->prox); }

        return T;
    }

    if(T->coef == 0){
        free(T);
        return SOMA(P->prox, Q->prox);
    }

    T->prox = SOMA(P->prox, Q->prox);
    return T;
} // Complexidade O(N + M) 😐
*/

/*
bool APAGAMON(MON **M){
    if((M == NULL) || (*M == NULL)){ return FALSE; }
    
    MON *Pos = *M, *Aux;
    
    while(Pos != NULL){
        Aux = Pos->prox;
        free(Pos);
        Pos = Aux;
    }

    *M = NULL;
    return TRUE;
}

MON* MonProd(MON *M, long long int c, long long int g){

    if(M == NULL){ return NULL; }
    
    MON *T = NULL;
    if(c == 0){ return NULL; }

    MON *Pos = M;
    MON **PosT = &(T);

    while(Pos != NULL){
        *PosT = criar_mon(Pos->coef * c, Pos->grau + g); if(*PosT == NULL){ APAGAMON(&T); return NULL; }
        PosT = &((*PosT)->prox);
        Pos = Pos->prox;
    }
    return T;
} // Complexidade O(N)
*/