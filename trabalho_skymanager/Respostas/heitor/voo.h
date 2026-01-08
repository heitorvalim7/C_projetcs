#ifndef _VOO_H_
#define _VOO_H_

#include "data.h"

typedef struct Voo Voo;

/**
 * Cria um Voo com os dados fornecidos.
 * @param codigo Código do voo (string)
 * @param origem Cidade/airport de origem (string)
 * @param destino Cidade/airport de destino (string)
 * @param codigoAeronave Código da aeronave (string)
 * @param data Ponteiro para `Data` (cópia não é feita automaticamente; passe uma cópia se necessário)
 * @param horaSaida Horário de saída (int)
 * @param horaChegada Horário de chegada (int)
 * @param preco Preço do voo (float)
 * @return Ponteiro para o Voo criado (ou NULL em erro)
 */
Voo *criaVoo(char *codigo, char *origem, char *destino, char *codigoAeronave, Data *data, int horaSaida, int horaChegada, float preco);

/** Lê um Voo da entrada padrão conforme especificação do trabalho */
Voo *leVoo();

/** Desaloca um Voo (compatível com callbacks genéricos) */
void desalocaVoo(void *dado);

/** Comparação por código do voo (retorna 1 se iguais, 0 caso contrário) */
int comparaVoo(void *a, void *b);

/** Getters */
char *getCodigoVoo(Voo *v);
char *getOrigemVoo(Voo *v);
char *getDestinoVoo(Voo *v);
char *getCodigoAeronaveVoo(Voo *v);
Data *getDataVoo(Voo *v);
int getHoraSaidaVoo(Voo *v);
int getHoraChegadaVoo(Voo *v);
float getPrecoVoo(Voo *v);

#endif // _VOO_H_
