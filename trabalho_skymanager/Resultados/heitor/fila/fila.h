

#ifndef _FILA_H_
#define _FILA_H_

#include "reserva.h"

typedef struct Fila Fila;

/**
 * @brief Cria uma fila de reservas vazia
 * @return Ponteiro para a fila criada
 */
Fila *criaFila();

/**
 * @brief Insere uma nova reserva na fila e realiza todas as operações de memória necessárias
 * @param f Fila de reservas
 * @param cpfPassageiro CPF do passageiro que está solicitando a reserva
 * @param codigoVoo Código do voo associado à reserva
 * @param dado   Uma reserva genérica  (considerando que existe mais de um tipo de reserva) 
 * @param getTipo   Função de callback que retorna o tipo da reserva
 * @param notifica  Função de callback que irá imprimir uma reserva quando for solicitada uma consulta
 * @param desaloca  Função de callback que irá desalocar  uma reserva da memória
 * @param processa  Função de callback que irá processar uma reserva
 */
void insereReservaNaFila(Fila *f, char *cpfPassageiro, char *codigoVoo, void *dado,
                         func_ptr_tipo getTipo,      
                         func_ptr_imprime notifica, 
                         func_ptr_desaloca desaloca, 
                         func_ptr_processa processa);


/** * @brief Desaloca toda a memória associada à fila de reservas
 * @param f Fila de reservas a ser desalocada
 */ 
void desalocaFila(Fila *f);

/**
 * @brief Processa todas as reservas na fila, atualizando todas as informações necessárias que a fila mantém
 * @param f Fila de reservas a ser processada
 * @param listaPassageiros Ponteiro para a lista de passageiros cadastrados
 * @param listaVoos Ponteiro para a lista de voos cadastrados
 */
void processaReservasNaFila(Fila *f, void *listaPassageiros, void *listaVoos);

/**
 * @brief Imprime todas as reservas na fila quando solicitado uma consulta
 * @param f Fila de reservas a ser impressa
 */
void imprimeFila(Fila *f);

/**
 * @brief Obtém a quantidade de total de reservas na fila
 * @param f Fila de reservas
 * @return Quantidade de reservas na fila
 */
int getQntdReservaFila(Fila *f);

/**
 * @brief Obtém a quantidade de reservas confirmadas na fila
 * @param f Fila de reservas
 * @return Quantidade de reservas confirmadas na fila
 */
int getQntdReservasConfirmadasFila(Fila *f);

/**
 * @brief Obtém uma reserva na posição especificada da fila
 * @param f Fila de reservas
 * @param posicao Posição da reserva desejada
 * @return Ponteiro para a reserva na posição especificada, ou NULL se a posição for inválida
 */
Reserva *getReservaNaPosicaoFila(Fila *f, int posicao);

#endif // _FILA_H_