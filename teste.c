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

long long int GRAU(POL *P){
    if(P == NULL){ return -1; }
    
    MON *Pos = P->inicio; if(Pos == NULL){ return -1; }

    while(Pos->prox != NULL){
        Pos = Pos->prox;
    }

    return Pos->grau;
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

bool ESCALA(POL *P, long long int c){
    if(P == NULL){ return FALSE; }

    if(c == 0){ LIMPA(P); return TRUE; }

    MON *Pos = P->inicio; if(Pos == NULL){ return TRUE; }

    while(Pos != NULL){
        Pos->coef *= c;
        Pos = Pos->prox;
    }
    return TRUE;
}

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
                *PosT = criar_mon(s, PosP->grau); if(*PosT == NULL){ LIBERA(T); return NULL; }
                PosT = &((*PosT)->prox);
            }
            
            PosP = PosP->prox; PosQ = PosQ->prox;
        }
    }

    MON *R = (PosP != NULL) ? PosP : PosQ;

    while (R != NULL) {
        //COPIA(*PosT, R);
        *PosT = criar_mon(R->coef, R->grau); if(*PosT == NULL){ LIBERA(T); return NULL; }
        PosT = &((*PosT)->prox);
        R = R->prox;
    }

    return T;
} // Complexidade O(N + M) 😐

// *R = PROD(&P, &Q);
POL* PROD(POL *P, POL *Q) {
    if (P == NULL || Q == NULL) { return NULL; }

    POL *T = criar_pol(); if (T == NULL) { return NULL; }

    if (P->inicio == NULL || Q->inicio == NULL) { return T; }

    MON *PosP = P->inicio;

    while (PosP != NULL) {
        MON *PosQ = Q->inicio;
        MON **PosT = &(T->inicio);

        while (PosQ != NULL) {
            long long int c = PosP->coef * PosQ->coef;
            long long int g = PosP->grau + PosQ->grau;

            while (*PosT != NULL && (*PosT)->grau < g) {
                PosT = &((*PosT)->prox);
            }

            if (*PosT != NULL && (*PosT)->grau == g) {
                (*PosT)->coef += c;

                if ((*PosT)->coef == 0) {
                    MON *Aux = *PosT;
                    *PosT = Aux->prox;
                    free(Aux);

                } else {
                    PosT = &((*PosT)->prox);
                }
            } 

            else {
                MON *M = criar_mon(c, g); if (M == NULL) { LIBERA(T); return NULL; }
                M->prox = *PosT;
                *PosT = M;
                
                PosT = &((*PosT)->prox);
            }

            PosQ = PosQ->prox;
        }

        PosP = PosP->prox;
    }

    return T;
} //Complexidade é O(N^2 * M) 🫩

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