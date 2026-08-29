#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct POL { /* Usando uma estrutura de arvore para nossos Polinomios,
                        assim podemos conseguir complexidade linear (na vdd é até um pouco melhor) e quadratica para o produto */
    bool monomio;

    long long int grau;
    int coef;

    struct POL* Seq;

}

bool SOMA(POL **P, POL **Q, POL *R){
    if (Q.grau > P.grau){
        R.grau = P.grau; R.coef = P.coef;
        if(P.Seq == NULL){
            R.Seq = *Q; /*  isso aqui tá errado... (A gente ta passando o ponteiro de Q para R. Se Q for alterado dps, R tbm será)
                            Vamo ter que criar uma função Copiar(POL P) para poder lidar com isso */
            return TRUE;
        }
        return SOMA(&P.Seq, Q, R.Seq);
    }
    if(P.grau > Q.grau){
        R.grau = Q.grau; R.coef = Q.coef;
        if(Q.Seq == NULL){
            R.Seq = *P;
            return TRUE;
        }
        return SOMA(P, &Q.Seq, R.Seq);
    }
    R.grau = P.grau; R.coef = P.coef + Q.coef;
    return TRUE;
}


/*  Bem, eu tentei pensar um pouco na soma usando outros TAD (listas de todo tipo),
    e o melhor que saia era na minha cabeça era n log(n) (eu sou meio burro e quase ctz deve tbm ter um jeitinho linear).
    Mas usando arvore a lógica é +/- assim:
    Pensa 2 Polnimios P e Q, de N e M elementos respct (SPG N >= M), temos que a complexidade da soma é tipo uma função C(N, M).
    Assumindo que as arvores são meio que distribuidas uniformimente,
    temos que nosso algorimo de soma quebra ela em duas avores menores (de aprox msm tamanho)
    e soma tudo com recursão. Tipo assim:

    Complexidade( Soma(P, Q) ) = Complexidade( Soma(P.Par, Q.Par) ) + Complexidade( Soma(P.Impar, Q.Impar) )
    
    Como podemos esperar que cada arvore filho tem aprox metade do tam do pai, então podemos cotar a complexidade por:
    
    C(N ,M) = C(N/2, M/2) + C(N/2, M/2) = 2 C(N/2, M/2)
    
    Disso, é só spammar essa relação:

    C(N ,M) = 2 C(N/2, M/2) = 4 C(N/4, M/4) = ... = 2^(log(M)) * C(N/(2^(log(M))), 1)
    
    Considera que 2^((log(M))) é praticamente M e dá pra cotar que C(N,1) aprox ( log(N) + 1 ):
    
    C(N,M) = M * C(N/M, 1) = M * ( log(N/M) + 1 )
    
    Temos algo que em média é um meio melhor que linear (normalmente complexidade linear fica em O(N) (do maior termo), esse aí ta em função do menor)*/