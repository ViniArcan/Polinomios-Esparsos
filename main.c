#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pol_esp.h"

void DEF(char nome[], int k, int Tam, PolNome *Polinomios){

    (*Polinomios)[Tam].Pol = criar_pol(); (*Polinomios)[Tam].Nome = nome;

    while(k>0){
        long long int c, g;
        scanf("%lld %lld", &c, &g);
        ADD(P, c, g);
        k--;
    }
}

typedef struct PolNome{
    POL *Pol;
    char Nome[];
}

bool main(){

    PolNome *Polinomios[512] = (PolNome*) malloc(512 * sizeof(PolNome));
    if (Polinomios == NULL){ printf("Falha na alocacao de memoria :(\n"); return false; }

    int Tam = 0;

    while(true){



    }

    free(Polinomios);
    Polinomios = NULL;
    return true;
}