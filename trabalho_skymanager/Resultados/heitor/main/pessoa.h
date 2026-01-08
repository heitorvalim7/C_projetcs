#ifndef _PESSOA_H_
#define _PESSOA_H_

#include "data.h"

typedef struct Pessoa Pessoa;

/**
 * @brief Cria uma Pessoa com os dados fornecidos. Retorna NULL se os dados forem inválidos.
 */
Pessoa *criaPessoa( char *nome,  char *cpf,  char *telefone, char *genero, Data *nascimento);

/**
 * @brief Lê uma Pessoa da entrada padrão (formatos conforme especificação do trabalho).
 *        Deve ler: nome, cpf, telefone, genero (char), e a data de nascimento em três inteiros.
 */
Pessoa *lePessoa();

/** Funções compatíveis com callbacks genéricos */
void imprimePessoa(void *dado);
void desalocaPessoa(void *dado);
int comparaPessoa( void *a,  void *b); /* por CPF */

/** Getters */
char *getNomePessoa(Pessoa *p);
char *getCPFPessoa(Pessoa *p);
char *getTelefonePessoa(Pessoa *p);
char *getGeneroPessoa(Pessoa *p);
Data *getDataNascimentoPessoa(Pessoa *p);


#endif // _PESSOA_H_
