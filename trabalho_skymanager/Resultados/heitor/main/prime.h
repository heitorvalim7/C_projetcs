#ifndef _PRIME_H_
#define _PRIME_H_

/**
 * TAD Prime
 * Campos: nº de bagagens despachadas, tipo de refeição (COMPLETA/PARCIAL/NENHUMA), necessidade de motorista (Sim/Não)
 */

typedef struct Prime Prime;

/** Cria um Prime */
Prime *criaPrime(int nBagagensDespachadas, char *tipoRefeicao, char *precisaMotorista);

/** Lê um Prime da entrada: número de bagagens (int), tipo refeição (string: COMPLETA/PARCIAL/NENHUMA), precisa motorista (string: "Sim"/"Nao") */
Prime *lePrime();

/** Funções compatíveis com callbacks genéricos */
void imprimePrime(void *dado);
void desalocaPrime(void *dado);

/** Getters */
int getNumBagagensPrime(void *dado);
char *getTipoRefeicaoPrime(void *dado); /* retorna string: "COMPLETA"/"PARCIAL"/"NENHUMA" */
char *getPrecisaMotoristaPrime(void *dado); /* retorna string: "Sim"/"Nao" */

/** Tipo de reserva */
char getTipoPrime(); /* retorna 'P' */

#endif // _PRIME_H_
