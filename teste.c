#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <teste.h>


POL Pol_criar(){
    POL P;
    P.TAM = TAM;
    P.grau = -1;
    P.prox = NULL;

    return P;
}

void ADD(POL *P, int c, unsigned long long g){

    if(P->grau < g){
        P-> grau = g; P->coef = c;
        return;
    }
    POL *Rem, *Pos = P;
    while( (g > Pos->grau) && (Pos != NULL)){
        Rem = Pos;
        Pos = P->prox;
    }
    if(g == Pos->grau){
        Pos->coef += c;
        return;
    }
    POL T = Pol_criar();
    T.grau = g; T.coef = c; T.prox = Pos;
    Rem->prox = *T;
    return;

}

void LIBERA(POL *P){
    if (P->termos != NULL) {
        free(P->termos);
        P->termos = NULL;
    }
    P->num = 0;
}

POL SOMA(POL *P, POL *Q){
    int N = P->num + Q-> num;
    POL R = Pol_criar(N);

    for(int i = 0; i<N)
}

/*
bool SOMA(POL **P, POL **Q, POL *R){
    if (Q.grau > P.grau){
        R.grau = P.grau; R.coef = P.coef;
        if(P.Seq == NULL){
            R.Seq = *Q;   isso aqui tá errado... (A gente ta passando o ponteiro de Q para R. Se Q for alterado dps, R tbm vai ser)
                            Vamo ter que criar uma função Copiar(POL P) para poder lidar com isso 
            return TRUE;
        }
        return SOMA(P.Seq, Q, R.Seq);
    }
    if(P.grau > Q.grau){
        R.grau = Q.grau; R.coef = Q.coef;
        if(Q.Seq == NULL){
            R.Seq = *P;
            return TRUE;
        }
        return SOMA(P, &Q.Seq, R.Seq);
    }
    R.grau = P.grau; R.coef = P.coef + Q.coef;
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