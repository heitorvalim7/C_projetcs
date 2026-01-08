#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#define TAM_PADRAO_ID_RESERVA 6

struct Fila {
    Reserva **reservas;
    int numReservas;
    int reservasConfirmadas;
};

/**
 * @brief Cria uma fila de reservas vazia
 * @return Ponteiro para a fila criada
 */
Fila *criaFila(){
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->reservas = NULL;
    f->numReservas = 0;
    f->reservasConfirmadas = 0;
    return f;
}

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
                         func_ptr_processa processa)
{
    if (!f || !cpfPassageiro || !codigoVoo || !dado || !getTipo || !notifica || !desaloca || !processa) {
        return;
    }

    Reserva *novaReserva = criaReserva(cpfPassageiro, codigoVoo, dado, getTipo, notifica, desaloca, processa);
    if (!novaReserva) {
        return;
    }

    f->reservas = (Reserva **)realloc(f->reservas, (f->numReservas + 1) * sizeof(Reserva *));
    f->reservas[f->numReservas] = novaReserva;
    char bufferID[32];
    sprintf(bufferID, "RES-%d", f->numReservas + 1);
    setIDReserva(f->reservas[f->numReservas], bufferID);
    f->numReservas++;

                                    
}


/** * @brief Desaloca toda a memória associada à fila de reservas
 * @param f Fila de reservas a ser desalocada
 */ 
void desalocaFila(Fila *f){
  for (int i = 0; i < f->numReservas; i++){
    desalocaReserva(f->reservas[i]);
  }

  if (f->reservas != NULL){
    free(f->reservas);
  }

  free(f);
}

/**
 * @brief Processa todas as reservas na fila, atualizando todas as informações necessárias que a fila mantém
 * @param f Fila de reservas a ser processada
 * @param listaPassageiros Ponteiro para a lista de passageiros cadastrados
 * @param listaVoos Ponteiro para a lista de voos cadastrados
 */
void processaReservasNaFila(Fila *f, void *listaPassageiros, void *listaVoos){
    for(int i = 0; i < f->numReservas; i++){
        int resultado = processaReserva(listaPassageiros, listaVoos, f->reservas[i]);
        if (resultado == 1){
            f->reservasConfirmadas++;
        }
    }
}

/**
 * @brief Imprime todas as reservas na fila quando solicitado uma consulta
 * @param f Fila de reservas a ser impressa
 */
void imprimeFila(Fila *f){
    if (!f) return;
    for (int i = 0; i < f->numReservas; i++) {
        imprimeReserva(f->reservas[i]);
    }
}

/**
 * @brief Obtém a quantidade de total de reservas na fila
 * @param f Fila de reservas
 * @return Quantidade de reservas na fila
 */
int getQntdReservaFila(Fila *f){
    if (!f) return 0;
    return f->numReservas;
}

/**
 * @brief Obtém a quantidade de reservas confirmadas na fila
 * @param f Fila de reservas
 * @return Quantidade de reservas confirmadas na fila
 */
int getQntdReservasConfirmadasFila(Fila *f){
    if (!f) return 0;
    return f->reservasConfirmadas;
}

/**
 * @brief Obtém uma reserva na posição especificada da fila
 * @param f Fila de reservas
 * @param posicao Posição da reserva desejada
 * @return Ponteiro para a reserva na posição especificada, ou NULL se a posição for inválida
 */
Reserva *getReservaNaPosicaoFila(Fila *f, int posicao){
    if (!f || posicao < 0 || posicao >= f->numReservas) {
        return NULL;
    }
    return f->reservas[posicao];
}