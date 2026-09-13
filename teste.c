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

POL *Pol_criar(){

    POL *P;

    P = (POL*) malloc(sizeof(POL));

    P->grau = 0;
    P->coef = 0;
    P->prox = NULL;

    return P;

} // Complexidade Const 🥴

void LIBERA(POL **P){ //Eu acho que isso aqui precisa de ponteiro duplo...
    if(*P == NULL){
        return;
    }
    LIBERA(&((*P)->prox));
    free(*P);
    return;
}

void COPIA(POL *Q, POL *P){

    if( Q == NULL ){

        *Q = Pol_criar();

    }

    Q->coef = P->coef; Q->grau = P->grau;

    if (P->prox != NULL){

        COPIA(Q->prox, P->prox);
        return;

    }

    if(Q->prox != NULL){
        LIBERA(&(Q->prox));
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

long long int COEF(POL *P, long long int g){

    if(P == NULL){
        return 0;
    }
    if(g == P->grau){
        return P->coef;
    }
    return COEF(P->prox; g);

}

POL *REMOVE(POL *P, long long int g){
    if(P == NULL){
        return NULL;
    }
    if(g == P->grau){
        POL Aux = *P;
        free(P);
        return Aux.prox;
    }
    P->prox = REMOVE(P->prox, g);
    return P;
}

void REMOVEMENOR(POL *P){
    if(P->prox == NULL){
        P->coef = 0; P->grau = 0;
        return;
    }

    P->coef = (P->prox)->coef; P->grau = (P->prox)->grau;
    POL Aux = *(P->prox);
    free(P->prox);
    P->prox = Aux.prox;
    return;
}

long long int MAIOR(POL *P){
    if(P->prox == NULL){
        return P->grau;
    }
    return MAIOR(P->prox);
}

// R = SOMA( &&P, &&Q);
POL SOMA(POL *P, POL *Q){ // Eu nn acho q precisa de ponteiro duplo, to viajando aqui
                            // Meu problema aqui é com a função COPIA que eu to usando

    POL *T; T = Pol_criar();

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
        MonProd(&T0, P->coef, P->grau);
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

    LIBERA(&&T1); LIBERA(&&T2);

    T0.prox = SOMA( &(&T01), &(&T02) );

    LIBERA(&&T01); LIBERA(&&T02);

    return T0;

} //Complexidade é O(N^2 + M^2) 🫩

void IMPRIME_AUX(POL *P){

    if(P == NULL){ return; }

    IMPRIME_AUX(P->prox);
    printf("%lld*x^%lld ", (P->coef), (P->grau));

    return;

}

void IMPRIME(POL *P){

    IMPRIME_AUX(P->prox);

    printf("%lld*x^%lld\n", (P->coef), (P->grau));

    return;

}

void IMPRIMEINV(POL *P){

    if(P->prox == NULL){

        printf("%lld*x^%lld\n", (P->coef), (P->grau));
        
        return;
    }

    printf("%lld*x^%lld ", (P->coef), (P->grau));
    IMPRIME(P->prox);

    return;

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