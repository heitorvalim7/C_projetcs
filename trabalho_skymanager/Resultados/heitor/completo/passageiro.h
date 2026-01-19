#ifndef _PASSAGEIRO_H_
#define _PASSAGEIRO_H_

#include "pessoa.h"
#include "stdlib.h"

typedef struct Passageiro Passageiro;

/**
 * Cria um Passageiro. A função faz cópia interna da `Pessoa` fornecida.
 * @param pessoa Ponteiro para `Pessoa` (copiado internamente)
 * @param programa Nome do programa de fidelidade
 */
Passageiro *criaPassageiro(Pessoa *pessoa, char *programa);

/**
 * Lê um Passageiro da entrada: ler Pessoa (com `lePessoa()`), depois uma linha com o nome do programa
 * e um inteiro com os pontos.
 */
Passageiro *lePassageiro();

/* Funções compatíveis com callbacks genéricos */
void imprimePassageiro(void *dado);
void desalocaPassageiro(void *dado);
int comparaPassageiro(const void *a, const void *b); /* compara por CPF */
int verificaCPFPassageiro(void *dado1, void *dado2);
/* Getters */
Pessoa *getPessoaPassageiro(Passageiro *p);
char *getProgramaPassageiro(Passageiro *p);
char *getCpfPassageiro(Passageiro *p);
size_t getTamanhoPassageiro();

/* Contador de reservas confirmadas */
void incrementaReservasConfirmadas(Passageiro *p);
int getReservasConfirmadas(Passageiro *p);

/**
 * @brief Imprime ranking de passageiros por reservas confirmadas (decrescente). Reordena temporariamente os ponteiros
 *        para impressão; não altera a ordem do vetor passado.
 * @param passageiros Vetor de ponteiros para Passageiro
 * @param count Quantidade de passageiros no vetor
 * @param topN Número máximo de itens a imprimir (<=0 imprime todos)
 */
void passageiroImprimeRankingPorReservas(Passageiro **passageiros, int count, int topN);

#endif // _PASSAGEIRO_H_
