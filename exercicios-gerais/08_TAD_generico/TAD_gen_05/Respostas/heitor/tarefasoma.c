#include "tarefasoma.h"
#include <stdio.h>
#include <stdlib.h>

struct soma{
    float n1;
    float n2;
};

/**
 * @brief Cria uma tarefa do tipo soma de dois números
 * 
 * @param n1 - Primeiro número que será somado quando a tarefa for executada
 * @param n2 - Segundo número que será somado quando a tarefa for executada
 *
 * @return Um ponteiro para a tarefa criada
 */
tSoma* CriaTarefaSoma(float n1, float n2){
    tSoma *s = (tSoma*)calloc(1, sizeof(struct soma));
    s->n1 = n1;
    s->n2 = n2;
    return s;
}

/**
 * @brief Função que executa uma tarefa de soma de dois números
 *
 * @param sum - Ponteiro para a tarefa a ser executada
 *
 */
void ExecutaTarefaSoma(void *sum){
    tSoma *s=(tSoma*)sum;
    float resultado = s->n1 + s->n2;
    printf("\nO resultado da soma de %.2f com %.2f eh: %.2f", s->n1, s->n2, resultado);
}

/**
 * @brief Função que destrói (libera a memória) uma tarefa de soma de dois números
 *
 * @param sum - Ponteiro para a tarefa a ser destruída
 *
 */
void DestroiTarefaSoma(void *sum){
    free((tSoma*)sum);
}