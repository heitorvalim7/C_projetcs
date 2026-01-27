#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

struct Vector{
    DataType *data;
    int numElem;
};

/**
 * @brief Cria um vetor vazio
 * 
 * @return A estrutura Vector inicializada. Caso não seja possível alocar memória, o programa é encerrado.
*/
Vector *VectorConstruct(){
    Vector *v = (Vector*)calloc(1, sizeof(Vector));
    v->data = NULL;
    v->numElem = 0;

    return v;
}

/**
 * @brief Adiciona um elemento no final do vetor
 * 
 * @param v Ponteiro para o vetor
 * @param val Valor a ser adicionado
*/
void VectorPushBack(Vector *v, DataType val){
    v->data = (DataType)realloc(v->data, (v->numElem + 1) * sizeof(DataType));
    if(!v->data){
        return;
    }
    v->data[v->numElem] = val;
    v->numElem++;
}

/**
 * @brief Retorna o i-ésimo elemento do vetor
 * 
 * @param v Ponteiro para o vetor
 * @param i Índice do elemento
 * @return DataType Elemento do vetor
*/
DataType VectorGet(Vector *v, int i){
    return v->data[i];
}

/**
 * @brief Retorna o tamanho do vetor
 * 
 * @param v Ponteiro para o vetor
 * @return int Tamanho do vetor
*/
int VectorSize(Vector *v){
    return v->numElem;
}

/**
 * @brief Libera a memória alocada para o vetor
 * 
 * @param v Ponteiro para o vetor
 * @param destroy Função que libera a memória alocada para cada elemento do vetor
*/
void VectorDestroy(Vector *v, void (*destroy)(DataType)){
    for(int i = 0; i<v->numElem; i++){
        free(v->data[i]);
    }
    free(v->data);
    free(v);
}
