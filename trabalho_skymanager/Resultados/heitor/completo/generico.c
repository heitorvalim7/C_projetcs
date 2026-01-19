#include "generico.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Generico {
    void **arrayGenerico;
    int tamanho;
    func_ptr_imprime_generico imprime;
    func_ptr_desaloca_generico desaloca;
    func_ptr_compara_generico compara;
    func_ptr_verifica_generico verifica;
    func_ptr_getSize_generico getSize;
} Generico;

/**
 * @brief Aloca uma estrutura Array na memória e inicializa os parâmetro necessários
 * @param imprime Função de callback para imprimir um elemento do array
 * @param desaloca Função de callback para desalocar um elemento do array
 * @param compara Função de callback para comparar dois elementos do array
 * @param verifica Função de callback para verificar um elemento do array
 * @param getSize Função de callback para obter o tamanho do array
 * @return  Uma estrutura Array inicializada.
 */
Generico *criaArray(func_ptr_imprime_generico imprime, 
    func_ptr_desaloca_generico desaloca, 
    func_ptr_compara_generico compara, 
    func_ptr_verifica_generico verifica, 
    func_ptr_getSize_generico getSize)
{
    Generico *novoArray = (Generico *)malloc(sizeof(Generico));
    if (!novoArray) {
        return NULL;
}

    novoArray->arrayGenerico = NULL;
    novoArray->tamanho = 0;
    novoArray->imprime = imprime;
    novoArray->desaloca = desaloca;
    novoArray->compara = compara;
    novoArray->verifica = verifica;
    novoArray->getSize = getSize;

    return novoArray;
}

/**
 * @brief Adiciona um elemento ao array
 * @param array Ponteiro para a estrutura Array
 * @param dado Ponteiro para o elemento a ser adicionado        
 */
void adicionaItemArray(Generico *array, void *dado) {
    if (!array || !dado) return;

    void **temp = (void **)realloc(array->arrayGenerico, (array->tamanho + 1) * sizeof(void *));
    if (!temp) return;

    array->arrayGenerico = temp;
    array->arrayGenerico[array->tamanho] = dado;
    array->tamanho++;
}

/**
 * @brief Limpa cada item individualmente usando o callback de desalocação e depois libera o array em si.
 * @param array Ponteiro para a estrutura Array
 */
void desalocaArray(Generico *array){
    for (int i = 0; i < array->tamanho; i++) {
        array->desaloca(array->arrayGenerico[i]);
    }
    free(array->arrayGenerico);
    free(array);
}

/**
 * @brief Imprime todos os elementos do array usando o callback de impressão
 * @param array Ponteiro para a estrutura Array
 */
void imprimeArray(Generico *array){
    for (int i = 0; i < array->tamanho; i++) {
        array->imprime(array->arrayGenerico[i]);
    }
}

/** 
 * @brief Ordena os elementos do array usando o callback de comparação
 * @param array Ponteiro para a estrutura Array
 */
void ordenaArray(Generico *array){
    qsort(array->arrayGenerico, array->tamanho, sizeof(void *), 
        (int (*)(const void *, const void *))array->compara);
}

/**
 * @brief Obtém um elemento do array com base em uma chave usando o callback de comparação
 * @param array Ponteiro para a estrutura Array
 * @param chave Chave para buscar o elemento
 * @return Ponteiro para o elemento encontrado ou NULL se não encontrado
 */
void *getItemVerificacaoArray(Generico *array, char *chave) {
    if (!array || !array->verifica || !chave) return NULL;

    for (int i = 0; i < array->tamanho; i++) {
        if (array->verifica(array->arrayGenerico[i], chave)) {
            return array->arrayGenerico[i];
        }
    }
    return NULL;
}

/**
 * @brief Obtém um elemento do array com base na posição
 * @param array Ponteiro para a estrutura Array
 * @param posicao Posição do elemento a ser obtido
 * @return Ponteiro para o elemento na posição especificada
 */
void *getItemPosicaoArray(Generico *array, int posicao){
    if (posicao < 0 || posicao >= array->tamanho) {
        return NULL;
    }
    return array->arrayGenerico[posicao];
}

/**
 * @brief Obtém o tamanho atual do array
 * @param array Ponteiro para a estrutura Array
 * @return Tamanho do array
 */
int getTamanhoArray(Generico *array){
    return array->tamanho;
}