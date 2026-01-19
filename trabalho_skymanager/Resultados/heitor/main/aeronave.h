#ifndef _AERONAVE_H_
#define _AERONAVE_H_

typedef struct Aeronave Aeronave;

/**
 * Cria uma Aeronave.
 * @param codigo Código da aeronave (string)
 * @param modelo Modelo da aeronave (string)
 * @param capacidade Capacidade (número de passageiros)
 * @return Ponteiro para a Aeronave criada
 */
Aeronave *criaAeronave(char *codigo, char *modelo, int capacidade);

void imprimeAeronave(void *dado);

/** Lê uma Aeronave da entrada padrão (codigo, modelo, capacidade) */
Aeronave *leAeronave();

/** Desaloca uma Aeronave (compatível com callbacks genéricos) */
void desalocaAeronave(void *dado);

/** Compara por código (retorna 1 se iguais, 0 caso contrário) */
int comparaAeronave(const void *a, const void *b);

int verificaCodigoAeronave(void *dado, void *chave);

/** Getters */
char *getCodigoAeronave(Aeronave *a);
char *getModeloAeronave(Aeronave *a);
int getCapacidadeAeronave(Aeronave *a);

#endif // _AERONAVE_H_
