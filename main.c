#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pol_esp.h"

#define MAX_POLS 512

typedef struct {
    POL *Pol;
    char Nome[11];
} PolNome;

void DEF(char nome[], int k, int Tam, PolNome *Polinomios){

    Polinomios[Tam].Pol = criar_pol(); strcpy(Polinomios[Tam].Nome, nome);

    POL *P = Polinomios[Tam].Pol;

    while(k>0){
        long long int c, g;
        scanf("%lld %lld", &c, &g);
        ADD(P, c, g);
        k--;
    }
}



bool main(){

    PolNome *Polinomios[512] = (PolNome*) malloc(MAX_POLS * sizeof(PolNome));
    if (Polinomios == NULL){ printf("Falha na alocacao de memoria :(\n"); return 1; }

    int Tam = 0;
    char operacao[13];

    while(true){



        if(scanf("%12s", comando) != 1){
            break; 
        }

        if(strcmp(comando, "DEF") == 0){
            char nome[32];
            int k;
            
            scanf("%10s %d", nome, &k);
            
            if (Tam < MAX_POLS){
                DEF(nome, k, Tam, Polinomios);
                Tam++;
            } else {
                printf("Tem muito Polinimio po...\n");
            }
        }
        else if(strcmp(comando, "FIM") == 0){
            break;
        }


    }

    for(int i=0; i<Tam; i++){
        LIBERA(Polinomios[i].Pol);
    }

    free(Polinomios);
    Polinomios = NULL;
    return true;
}