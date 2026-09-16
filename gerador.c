#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_GRAU 500000
#define MAX_TERMOS 30000
#define MAX_ESCALA 20000

void gerar_polinomio(const char *nome) {
    printf("DEF %s %d\n", nome, MAX_TERMOS);

    int *graus = (int *)malloc((MAX_GRAU + 1) * sizeof(int)); if (graus == NULL) { exit(1); }

    for (int i = 0; i <= MAX_GRAU; i++) {
        graus[i] = i;
    }

    for (int i = 0; i < MAX_TERMOS; i++) {
        int j = i + rand() % (MAX_GRAU + 1 - i);
        int temp = graus[i];
        graus[i] = graus[j];
        graus[j] = temp;
    }

    for (int i = 0; i < MAX_TERMOS; i++) {
        int coef = (rand() % 2001) - 1000; if(coef == 0){ coef = 1; }
        printf("%d %d\n", coef, graus[i]);
    }

    free(graus);

    for (int i = 0; i < MAX_ESCALA; i++) {
        int c = (rand() % 2 == 0) ? -1 : 1;
        printf("ESCALA %s %d\n", nome, c);
    }
}

int main(void) {

    srand((unsigned int)time(NULL));

    gerar_polinomio("A");

    printf("IMPRIME A\n");
    printf("GRAU A\n");

    gerar_polinomio("B");

    printf("SOMA A B R\n");
    printf("FIM\n");

    return 0;
}