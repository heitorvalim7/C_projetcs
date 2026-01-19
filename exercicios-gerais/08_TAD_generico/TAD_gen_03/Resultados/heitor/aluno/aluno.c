#include "aluno.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Aluno{
    char nome[100];
    char genero;
    float nota;
};

/**
 * @brief Aloca memoria para um aluno
 * 
 * @return A estrutura tAluno inicializada. Caso não seja possível alocar memória, o programa é encerrado.
*/
tAluno *CriaAluno(){
    tAluno *a = (tAluno*)calloc(1, sizeof(struct Aluno));
    if(!a){
        return NULL;
    }
    return a;

}

/**
 * @brief Libera a memoria alocada para um aluno
 * 
 * @param aluno Ponteiro para o aluno
 * Dica: Foi usado data_type para generalizar a funcao e usar na estrutura Vector. Por isso, é necessário fazer um cast para tAluno* dentro da função.
*/
void DestroiAluno(data_type aluno){
    tAluno *a = (tAluno*)aluno;
    free(a);
}

/**
 * @brief Le os dados de um aluno
 * 
 * @param aluno Ponteiro para o aluno
*/
void LeAluno(tAluno *aluno){
    scanf(" %99[^;];%c;%f", aluno->nome, &aluno->genero, &aluno->nota);
}

/**
 * @brief Retorna o genero de um aluno
 * 
 * @param aluno Ponteiro para o aluno
 * @return char Genero do aluno
*/
char GetGeneroAluno(tAluno *aluno){
    return aluno->genero;
}

/**
 * @brief Retorna a nota de um aluno
 * 
 * @param aluno Ponteiro para o aluno
 * @return float Nota do aluno
*/
float GetNotaAluno(tAluno *aluno){
    return aluno->nota;
}