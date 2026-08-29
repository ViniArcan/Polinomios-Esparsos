#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct POL { /* Usando uma estrutura de arvore para nossos Polinomios,
                        assim podemos conseguir complexidade linear (na vdd é até um pouco melhor) e quadratica para o produto */
    bool monomio;

    long long int grau;
    int coef, tam;

    POL *Par, *Impar;

}
