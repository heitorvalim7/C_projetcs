

#ifndef _ECONOMICA_H_
#define _ECONOMICA_H_

#define TAM_ASSENTO_ESPECIAL 4

typedef struct Economica Economica;

/**
 * @brief Cria uma nova reserva do tipo Econômica
 * @param nBagagens Número de bagagens permitidas
 * @param assentoEspecial Assento especial solicitado
 * @return Ponteiro para a nova reserva criada
 */
Economica *criaEconomica(int nBagagens, char *assentoEspecial);

/**
 * @brief Lê os dados de uma reserva do tipo Econômica a partir da entrada padrão de acordo com a especificação do trabalho
 * @return Ponteiro para a nova reserva criada
 */
Economica *leEconomica();

/**
 * @brief Imprime os detalhes de uma reserva do tipo Econômica
 * @param dado Ponteiro genérico para a reserva do tipo Econômica
 */
void imprimeEconomica(void *dado);

/**
 * @brief Desaloca a memória associada a uma reserva do tipo Econômica
 * @param dado Ponteiro genérico para a reserva do tipo Econômica
 */
void desalocaEconomica(void *dado);

/**
 * @brief Obtém o número de bagagens permitidas em uma reserva do tipo Econômica
 * @param dado Ponteiro genérico para a reserva do tipo Econômica
 * @return Número de bagagens permitidas
 */
int getNumBagagensEconomica(void *dado);

/**
 * @brief Obtém o tipo da reserva do tipo Econômica
 * @return Caractere representando o tipo da reserva ('E' para Econômica)
 */
char getTipoEconomica();

#endif // _ECONOMICA_H_