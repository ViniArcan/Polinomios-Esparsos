#ifndef POL_H
#define POL_H

#define TAM_MAX 10000000000 /* eu acho que isso ta bom */

typedef long long int g;
typedef int c;

typedef struct pol_ POL;

POL *Pol_criar(void);

POL *SOMA(POL *A, POL *B);
POL *PROD(POL *A, POL *B);

POL *ADD(POL *A, int c, int g);

void ESCALA(POL *A, int c);

void REMOVE(POL *A, int g);
void REMOVEMENOR(POL *A);

int COEF(POL *A, int g);
long long int GRAU(POL *A);

void IMPRIME(POL *A);
void IMPRIMEINV(POL *A);
void LIBERA(POL *A);

#endif