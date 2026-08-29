#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct POL {

    bool monomio;

    long long int grau;
    int coef, tam;

    POL *Seq;

} POL;

