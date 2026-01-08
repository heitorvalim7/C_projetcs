#ifndef _TRIPULANTE_H_
#define _TRIPULANTE_H_

#include "pessoa.h"

typedef struct Tripulante Tripulante;

/**
 * @brief Cria um novo tripulante com a `Pessoa` associada, cargo, horas trabalhadas e salário.
 * @param pessoa Ponteiro para `Pessoa` (a função faz cópia interna)
 * @param cargo Cargo/posição do tripulante
 * @param horasTrabalhadas Horas trabalhadas (inteiro)
 * @param salario Salário (float)
 * @return Ponteiro para o Tripulante criado
 */
Tripulante *criaTripulante(Pessoa *pessoa, char *cargo, int horasTrabalhadas, float salario);

/**
 * @brief Lê um tripulante a partir da entrada (lê os campos de Pessoa, depois cargo, horas e salário)
 * @return Ponteiro para o Tripulante criado
 */
Tripulante *leTripulante();

/** Funções compatíveis com callbacks genéricos */
void imprimeTripulante(void *dado);
void desalocaTripulante(void *dado);
int comparaTripulante(void *a, void *b); /* compara por CPF */

/** Getters */
Pessoa *getPessoaTripulante(Tripulante *t);
char *getCargoTripulante(Tripulante *t);
int getHorasTripulante(Tripulante *t);
float getSalarioTripulante(Tripulante *t);

/** Conveniência: acesso aos campos de `Pessoa` */
char *getCPFTripulante(Tripulante *t);
char *getNomeTripulante(Tripulante *t);
Data *getDataNascimentoTripulante(Tripulante *t);

/**
 * @brief Imprime ranking de tripulantes por horas trabalhadas (decrescente). A função reordena temporariamente
 *        os ponteiros para impressão; não altera a ordem do vetor passado pelo chamador.
 * @param tripulantes Vetor de ponteiros para Tripulante
 * @param count Quantidade de tripulantes no vetor
 * @param topN Número máximo de itens a imprimir (<=0 imprime todos)
 */
void tripulanteImprimeRankingPorHoras(Tripulante **tripulantes, int count);

#endif // _TRIPULANTE_H_
