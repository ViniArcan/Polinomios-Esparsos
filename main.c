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



int main(){

    PolNome *Polinomios = (PolNome*) malloc(MAX_POLS * sizeof(PolNome));
    if (Polinomios == NULL){ printf("Falha na alocacao de memoria :(\n"); return 1; }

    int Tam = 0;
    char operacao[13];

    while(true){



        if(scanf("%12s", operacao) != 1){
            break; 
        }

        if(strcmp(operacao, "DEF") == 0){
            char nome[11]; int k;
            
            scanf("%10s %d", nome, &k);
            
            if (Tam < MAX_POLS){
                DEF(nome, k, Tam, Polinomios);
                Tam++;
            } else {
                printf("Tem muito Polinimio po...\n");
            }
        }else if(strcmp(operacao, "IMPRIME") == 0){
            char nome[11]; int flag = 1;

            scanf("%10s", nome);

            for(int i=0; i<Tam; i++){
                if(strcmp(Polinomios[i].Nome, nome) == 0){
                    IMPRIME(Polinomios[i].Pol);
                    flag = 0;
                    break;
                }
            }
            if(flag){ printf("-1\n"); }
        }else if(strcmp(operacao, "IMPRIMEINV") == 0){
            char nome[11]; int flag = 1;

            scanf("%10s", nome);

            for(int i=0; i<Tam; i++){
                if(strcmp(Polinomios[i].Nome, nome) == 0){
                    IMPRIMEINV(Polinomios[i].Pol);
                    flag = 0;
                    break;
                }
            }
            if(flag){ printf("-1\n"); }

        }else if(strcmp(operacao, "REMOVEMENOR") == 0){
            char nome[11]; int flag = 1;

            scanf("%10s", nome);

            for(int i=0; i<Tam; i++){
                if(strcmp(Polinomios[i].Nome, nome) == 0){
                    REMOVEMENOR(Polinomios[i].Pol);
                    flag = 0;
                    break;
                }
            }
            if(flag){ printf("-1\n"); }

        }else if(strcmp(operacao, "GRAU") == 0){ //TEM CONDIÇÃO PARA CONSIDERAR AQUI!!!!! SE O POL FOR NULO...
            char nome[11]; int flag = 1;

            scanf("%10s", nome);

            for(int i=0; i<Tam; i++){
                if(strcmp(Polinomios[i].Nome, nome) == 0){
                    printf("%lld\n", GRAU(Polinomios[i].Pol));
                    flag = 0;
                    break;
                }
            }
            if(flag){ printf("-1\n"); }

        }else if(strcmp(operacao, "COEF") == 0){
            char nome[11]; long long int g; int flag = 1;

            scanf("%10s %lld", nome, g);

            for(int i=0; i<Tam; i++){
                if(strcmp(Polinomios[i].Nome, nome) == 0){
                    printf("%lld\n", COEF(Polinomios[i].Pol, g));
                    flag = 0;
                    break;
                }
            }
            if(flag){ printf("-1\n"); }

        }
        else if(strcmp(operacao, "FIM") == 0){
            break;
        }


    }

    for(int i=0; i<Tam; i++){
        LIBERA(Polinomios[i].Pol);
    }

    free(Polinomios);
    Polinomios = NULL;
    return 0;
}