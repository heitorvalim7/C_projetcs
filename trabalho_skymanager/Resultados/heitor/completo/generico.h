#ifndef _GENERICO_H_
#define _GENERICO_H_

#include <stdlib.h>

typedef struct Generico Generico;

typedef void (*func_ptr_desaloca_generico)(void *dado);
typedef void (*func_ptr_imprime_generico)(void *dado);
typedef int (*func_ptr_compara_generico)(const void *dado1, const void *dado2);
typedef int (*func_ptr_verifica_generico)(void *dado1, void *dado2);
typedef size_t(*func_ptr_getSize_generico)();


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
    func_ptr_getSize_generico getSize);

/**
 * @brief Adiciona um elemento ao array
 * @param array Ponteiro para a estrutura Array
 * @param dado Ponteiro para o elemento a ser adicionado        
 */
void adicionaItemArray(Generico *array, void *dado);

/**
 * @brief Limpa cada item individualmente usando o callback de desalocação e depois libera o array em si.
 * @param array Ponteiro para a estrutura Array
 */
void desalocaArray(Generico *array);

/**
 * @brief Imprime todos os elementos do array usando o callback de impressão
 * @param array Ponteiro para a estrutura Array
 */
void imprimeArray(Generico *array);

/** 
 * @brief Ordena os elementos do array usando o callback de comparação
 * @param array Ponteiro para a estrutura Array
 */
void ordenaArray(Generico *array);

/**
 * @brief Obtém um elemento do array com base em uma chave usando o callback de comparação
 * @param array Ponteiro para a estrutura Array
 * @param chave Chave para buscar o elemento
 * @return Ponteiro para o elemento encontrado ou NULL se não encontrado
 */
void *getItemVerificacaoArray(Generico *array, char *chave);

/**
 * @brief Obtém um elemento do array com base na posição
 * @param array Ponteiro para a estrutura Array
 * @param posicao Posição do elemento a ser obtido
 * @return Ponteiro para o elemento na posição especificada
 */
void *getItemPosicaoArray(Generico *array, int posicao);

/**
 * @brief Obtém o tamanho atual do array
 * @param array Ponteiro para a estrutura Array
 * @return Tamanho do array
 */
int getTamanhoArray(Generico *array);

#endif // _GENERICO_H_