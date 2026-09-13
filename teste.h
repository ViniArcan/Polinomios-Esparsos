#ifndef POL_H
#define POL_H

typedef long long int g;
typedef long long int c;

typedef struct POL POL;

POL* criar_pol(void);
MON* criar_mon(long long int c, long long int g);

void LIBERA(POL **P);
bool LIMPA(POL *P);
bool COPIA(POL *Q, POL *P);

long long int COEF(POL *P, long long int g);
long long int GRAU(POL *P);

bool REMOVE(POL *P, long long int g);
bool REMOVEMENOR(POL *P);

bool ESCALA(POL *P, long long int c);

bool ADD(POL *P, long long int c, long long int g);
POL* SOMA(POL *P, POL *Q);
POL* PROD(POL *P, POL *Q);

bool IMPRIME(POL *P);
bool IMPRIMEINV(POL *P);

#endif