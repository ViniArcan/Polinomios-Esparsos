#ifndef POL_H
#define POL_H

#define TAM_MAX 10000000000 /* eu acho que isso ta bom */

typedef long long int g;
typedef int c;

/*
typedef struct {
    unsigned long long grau;
    int coef;
    int prox;
} mon;
*/

typedef struct POL {
    unsigned long long grau;
    int coef;
    struct POL* prox;
} POL;

/*
typedef struct POL {  Usando uma estrutura de arvore para nossos Polinomios,
                        assim podemos conseguir complexidade linear (na vdd é até um pouco melhor) e quadratica para o produto 
    bool monomio;

    long long int grau;  Se colocarmos os graus em ordem crescente, então podemos apenas colocar a diferença do anterior pro proximo.
                            Dessa forma podemos poupar algumas computações na multiplicação
    int coef;

    struct POL* Seq;

} */

POL *Pol_criar(void);

POL *SOMA(POL *P, POL *Q);
POL *PROD(POL *P, POL *Q);

POL *ADD(POL *P, int c, int g);

void ESCALA(POL *P, int c);

void REMOVE(POL *P, int g);
void REMOVEMENOR(POL *P);

int COEF(POL *P, int g);
long long int GRAU(POL *P);

void IMPRIME(POL *P);
void IMPRIMEINV(POL *P);
void LIBERA(POL *P);

#endif