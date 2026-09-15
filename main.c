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

void DEF(char nome[], int k, int Pos, PolNome *Polinomios){
    Polinomios[Pos].Pol = criar_pol(); strcpy(Polinomios[Pos].Nome, nome);

    POL *P = Polinomios[Pos].Pol;

    while(k > 0){
        long long int c, g;
        scanf("%lld %lld", &c, &g);
        ADD(P, c, g);
        k--;
    }
}

int BUSCA_NOME(PolNome *Polinomios, int Tam, char *nome) {
    for (int i = 0; i < Tam; i++) {
        if (strcmp(Polinomios[i].Nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

int main(void){

    PolNome *Polinomios = (PolNome*) malloc(MAX_POLS * sizeof(PolNome));
    if (Polinomios == NULL){ 
        printf("Falha na alocacao de memoria\n"); 
        return 1; 
    }

    int Tam = 0;
    char operacao[13];

    while(true){
        if(scanf("%12s", operacao) != 1){
            break; 
        }
        if(strcmp(operacao, "DEF") == 0){
            char nome[11];
            int k;
            
            scanf("%10s %d", nome, &k);

            int pos = BUSCA_NOME(Polinomios, Tam, nome);
            
            if (pos != -1) {
                LIMPA(Polinomios[pos].Pol);
                POL *P = Polinomios[pos].Pol;
                while(k > 0){
                    long long int c, g;
                    scanf("%lld %lld", &c, &g);
                    ADD(P, c, g);
                    k--;
                }
            } else if (Tam < MAX_POLS) {
                DEF(nome, k, Tam, Polinomios);
                Tam++;
            } else {
                printf("Quantidade de Polinomios esta no limite.\n");
                while (k > 0) {
                    long long int c, g;
                    scanf("%lld %lld", &c, &g);
                    k--;
                }
            }

        }else if(strcmp(operacao, "LIBERA") == 0){
            char nome[11];
            scanf("%10s", nome);

            int pos = BUSCA_NOME(Polinomios, Tam, nome);
            
            if (pos != -1) {
                LIBERA(Polinomios[pos].Pol);
                
                if (pos < Tam - 1) {
                    Polinomios[pos].Pol = Polinomios[Tam - 1].Pol;
                    strcpy(Polinomios[pos].Nome, Polinomios[Tam - 1].Nome);
                }
                Tam--;
            }

        }else if(strcmp(operacao, "IMPRIME") == 0){
            char nome[11];
            scanf("%10s", nome);

            int pos = BUSCA_NOME(Polinomios, Tam, nome);
            if(pos != -1){
                IMPRIME(Polinomios[pos].Pol);
            } else {
                printf("-1\n");
            }

        }else if(strcmp(operacao, "IMPRIMEINV") == 0){
            char nome[11];
            scanf("%10s", nome);

            int pos = BUSCA_NOME(Polinomios, Tam, nome);
            if(pos != -1){
                IMPRIMEINV(Polinomios[pos].Pol);
            } else {
                printf("-1\n");
            }

        }else if(strcmp(operacao, "REMOVE") == 0){
            char nome[11]; 
            long long int g;

            scanf("%10s %lld", nome, &g);

            int pos = BUSCA_NOME(Polinomios, Tam, nome);
            if(pos != -1){
                REMOVE(Polinomios[pos].Pol, g);
            }
        }else if(strcmp(operacao, "REMOVEMENOR") == 0){
            char nome[11];
            scanf("%10s", nome);

            int pos = BUSCA_NOME(Polinomios, Tam, nome);
            if(pos != -1){
                REMOVEMENOR(Polinomios[pos].Pol);
            } else {
                printf("-1\n");
            }

        }else if(strcmp(operacao, "GRAU") == 0){
            char nome[11];
            scanf("%10s", nome);

            int pos = BUSCA_NOME(Polinomios, Tam, nome);
            if(pos != -1){
                printf("%lld\n", GRAU(Polinomios[pos].Pol));
            } else {
                printf("-1\n");
            }

        }else if(strcmp(operacao, "COEF") == 0){
            char nome[11]; 
            long long int g;
            
            scanf("%10s %lld", nome, &g); 

            int pos = BUSCA_NOME(Polinomios, Tam, nome);
            if(pos != -1){
                printf("%lld\n", COEF(Polinomios[pos].Pol, g));
            } else {
                printf("-1\n");
            }

        }else if(strcmp(operacao, "ESCALA") == 0){
            char nome[11]; 
            long long int c;
            
            scanf("%10s %lld", nome, &c);

            int pos = BUSCA_NOME(Polinomios, Tam, nome);
            if(pos != -1){
                ESCALA(Polinomios[pos].Pol, c);
            }

        }else if(strcmp(operacao, "ADD") == 0){
            char nome[11]; 
            long long int c, g;

            scanf("%10s %lld %lld", nome, &c, &g);

            int pos = BUSCA_NOME(Polinomios, Tam, nome);
            if(pos != -1){
                ADD(Polinomios[pos].Pol, c, g);
            }

        }else if(strcmp(operacao, "SOMA") == 0){
            char nome1[11], nome2[11], nome3[11];
            scanf("%10s %10s %10s", nome1, nome2, nome3);

            int pos1 = BUSCA_NOME(Polinomios, Tam, nome1);
            int pos2 = BUSCA_NOME(Polinomios, Tam, nome2);

            if(pos1 == -1 || pos2 == -1){
                continue; 
            }

            int pos3 = BUSCA_NOME(Polinomios, Tam, nome3);
            
            if(pos3 != -1){
                LIBERA(Polinomios[pos3].Pol); 
                Polinomios[pos3].Pol = SOMA(Polinomios[pos1].Pol, Polinomios[pos2].Pol);
            } else {
                if(Tam < MAX_POLS){
                    Polinomios[Tam].Pol = SOMA(Polinomios[pos1].Pol, Polinomios[pos2].Pol); strcpy(Polinomios[Tam].Nome, nome3);
                    Tam++;
                }else{
                    printf("Quantidade de Polinomios esta no limite.\n");
                }
            }

        }else if(strcmp(operacao, "PROD") == 0){
            char nome1[11], nome2[11], nome3[11];
            scanf("%10s %10s %10s", nome1, nome2, nome3);

            int pos1 = BUSCA_NOME(Polinomios, Tam, nome1);
            int pos2 = BUSCA_NOME(Polinomios, Tam, nome2);

            if(pos1 == -1 || pos2 == -1){
                continue; 
            }

            int pos3 = BUSCA_NOME(Polinomios, Tam, nome3);
            
            if(pos3 != -1){
                LIBERA(Polinomios[pos3].Pol);
                Polinomios[pos3].Pol = PROD(Polinomios[pos1].Pol, Polinomios[pos2].Pol);
            }else{
                if(Tam < MAX_POLS){
                    Polinomios[Tam].Pol = PROD(Polinomios[pos1].Pol, Polinomios[pos2].Pol);
                    strcpy(Polinomios[Tam].Nome, nome3);
                    Tam++;
                }else{
                    printf("Quantidade de Polinomios esta no limite.\n");
                }
            }
        }else if(strcmp(operacao, "FIM") == 0){
            break;
        }
    }

    for(int i = 0; i < Tam; i++){
        LIBERA(Polinomios[i].Pol);
    }
    free(Polinomios);
    
    return 0;
}