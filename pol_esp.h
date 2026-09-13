#ifndef POL_H
#define POL_H
#include <stdbool.h>

typedef struct pol POL;

POL* criar_pol(void);
void LIBERA(POL *P);
bool LIMPA(POL *P);

long long int COEF(POL *P, long long int g);
long long int GRAU(POL *P);

bool COPIA(POL *Q, POL *P);
bool REMOVE(POL *P, long long int g);
bool REMOVEMENOR(POL *P);
bool ADD(POL *P, long long int c, long long int g);

bool ESCALA(POL *P, long long int c);
POL* SOMA(POL *P, POL *Q);
POL* PROD(POL *P, POL *Q);

bool IMPRIME(POL *P);
bool IMPRIMEINV(POL *P);

#endif