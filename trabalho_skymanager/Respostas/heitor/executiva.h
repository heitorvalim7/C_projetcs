#ifndef _EXECUTIVA_H_
#define _EXECUTIVA_H_

#define TAM_ASSENTO_ESPECIAL 4 /* manter compatibilidade se necessário */

typedef struct Executiva Executiva;

/**
 * @brief Cria uma nova reserva do tipo Executiva
 * @param nBagagens Número de bagagens permitidas
 * @param acessoLounge 1 se tem acesso ao lounge, 0 caso contrário
 * @param precisaRefeicao 1 se precisa de refeição, 0 caso contrário
 * @return Ponteiro para a nova reserva criada
 */
Executiva *criaExecutiva(int nBagagens, char *acessoLounge, char *precisaRefeicao);

/**
 * @brief Lê os dados de uma reserva do tipo Executiva a partir da entrada padrão
 * @return Ponteiro para a nova reserva criada
 */
Executiva *leExecutiva();

/**
 * @brief Imprime os detalhes de uma reserva do tipo Executiva
 * @param dado Ponteiro genérico para a reserva do tipo Executiva
 */
void imprimeExecutiva(void *dado);

/**
 * @brief Desaloca a memória associada a uma reserva do tipo Executiva
 * @param dado Ponteiro genérico para a reserva do tipo Executiva
 */
void desalocaExecutiva(void *dado);

/** Getters específicos */
int getNumBagagensExecutiva(void *dado);
char *getAcessoLoungeExecutiva(void *dado);
char *getPrecisaRefeicaoExecutiva(void *dado);

/** Tipo */
char getTipoExecutiva();

#endif // _EXECUTIVA_H_
