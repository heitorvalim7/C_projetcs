#ifndef _SISTEMA_H_
#define _SISTEMA_H_

#include "fila.h"
#include "reserva.h"
#include "passageiro.h"
#include "voo.h"
#include "data.h"
#include "aeronave.h"
#include "executiva.h"
#include "economica.h"
#include "prime.h"
#include "tripulante.h"
#include "pessoa.h"
#include "generico.h"
typedef struct Sistema Sistema;

/**
 * @brief Verifica se o passageiro e o voo estão cadastrados no sistema
 * @param s Ponteiro para o Sistema
 * @param cpfPassageiro CPF do passageiro
 * @return 1 se ambos estiverem cadastrados, 0 caso contrário     
 */
int sistemaVerificaDadosCadastradosPessoa(void *dado1, void *dado2);

/**
 * @brief Verifica se a aeronave está cadastrada no sistema
 * @param s Ponteiro para o Sistema
 * @param codigoAeronave Código da aeronave
 * @return 1 se a aeronave estiver cadastrada, 0 caso contrário     
 */
int sistemaVerificaDadosCadastradosAeronave(void *dado1, void *dado2);

/**
 * @brief Verifica se o voo está cadastrado no sistema
 * @param s Ponteiro para o Sistema
 * @param codigoVoo Código do voo
 * @return 1 se o voo estiver cadastrado, 0 caso contrário     
 */
int sistemaVerificaDadosCadastradosVoo(void *dado1, void *dado2);

/**
 * @brief Verifica se o passageiro e o voo estão cadastrados no sistema
 * @param s Ponteiro para o Sistema
 * @param codigoVoo Código do voo
 * @param cpfPassageiro CPF do passageiro
 * @return 1 se ambos estiverem cadastrados, 0 caso contrário     
 */
int sistemaVerificaDadosCadastrados(Sistema *s, char *codigoVoo, char *cpfPassageiro);

/**
 * @brief Busca um Voo pelo código
 * @param s Ponteiro para o Sistema
 * @param codigoVoo Código do voo
 * @return Ponteiro para Voo (interno) ou NULL se não encontrado
 */
Voo *sistemaBuscaVooPorCodigo(Sistema *s, char *codigoVoo);  

/**
 * @brief Busca uma Aeronave pelo código
 * @param s Ponteiro para o Sistema
 * @param codigoAeronave Código da aeronave
 * @return Ponteiro para Aeronave (interno) ou NULL se não encontrado
 */
Aeronave *sistemaBuscaAeronavePorCodigo(Sistema *s, char *codigoAeronave);


/**
 * @brief Cria um novo Sistema, inicializando bancos vazios e uma fila
 * @return Ponteiro para o Sistema (NULL em caso de erro)
 */
Sistema *criaSistema(void);

/**
 * @brief Desaloca o Sistema e todo o conteúdo (passageiros, tripulantes e fila)
 * @param s Ponteiro para o Sistema
 */
int sistemaProcessaReservasNaFila(Sistema *s, void *listapassageiros, void *listavoos, Reserva *reserva);

/*
 * @brief Roda o sistema, processando todas as reservas na fila
 * @param s Ponteiro para o Sistema
 */
void sistemaRoda(Sistema *s);

/**
 * @brief Desaloca o Sistema e todo o conteúdo (passageiros, tripulantes e fila)
 * @param s Ponteiro para o Sistema
 */
void desalocaSistema(Sistema *s);


/**
 * @brief Lê um Passageiro (chama `lePassageiro()`) e adiciona ao banco do Sistema.
 *        O Sistema passa a ser responsável pela desalocação do passageiro.
 * @param s Ponteiro para o Sistema
 * @return 1 em sucesso, 0 em falha
 */
void sistemaAdicionaPassageiro(Sistema *s);

/**
 * @brief Lê uma Reserva (chama `leReserva()`) e adiciona à fila do Sistema.
 *        O Sistema passa a ser responsável pela desalocação da reserva.
 * @param s Ponteiro para o Sistema
 * @return 1 em sucesso, 0 em falha
 */
void sistemaAdicionaReserva(Sistema *s);

/**
 * @brief Adiciona um Voo ao banco do Sistema. O Sistema passa a ser responsável
 *        pela desalocação do voo.
 * @param s Ponteiro para o Sistema
 * @param v Ponteiro para Voo (alocado pelo chamador)
 * @return 1 em sucesso, 0 em falha
 */
void sistemaAdicionaVoo(Sistema *s);

/*
 * @brief Adiciona uma Aeronave ao banco do Sistema. O Sistema passa a ser responsável
 *        pela desalocação da aeronave.
 * @param s Ponteiro para o Sistema
 * @param a Ponteiro para Aeronave (alocado pelo chamador)
 * @return 1 em sucesso, 0 em falha
 */
void sistemaAdicionaAeronave(Sistema *s);


/**
 * @brief Lê um Tripulante (chama `leTripulante()`) e adiciona ao banco do Sistema.
 *        O Sistema passa a ser responsável pela desalocação do tripulante.
 * @param s Ponteiro para o Sistema
 * @return 1 em sucesso, 0 em falha
 */
void sistemaAdicionaTripulante(Sistema *s);

/**
 * @brief Busca um Passageiro pelo CPF
 * @param s Ponteiro para o Sistema
 * @param cpf CPF do passageiro
 * @return Ponteiro para Passageiro (interno) ou NULL se não encontrado
 */
Passageiro *sistemaBuscaPassageiroPorCpf(Sistema *s, char *cpf);

/**
 * @brief Busca um Tripulante pelo CPF
 * @param s Ponteiro para o Sistema
 * @param cpf CPF do tripulante
 * @return Ponteiro para Tripulante (interno) ou NULL se não encontrado
 */
Tripulante *sistemaBuscaTripulantePorCpf(Sistema *s, char *cpf);

/**
 * @brief Conveniência: obtém a Pessoa associada a um passageiro identificado pelo CPF
 * @param s Ponteiro para o Sistema
 * @param cpf CPF do passageiro
 * @return Ponteiro para Pessoa (interna) ou NULL
 */
Pessoa *sistemaGetPessoaPassageiroPorCpf(Sistema *s, char *cpf);

/**
 * @brief Conveniência: obtém a Pessoa associada a um tripulante identificado pelo CPF
 * @param s Ponteiro para o Sistema
 * @param cpf CPF do tripulante
 * @return Ponteiro para Pessoa (interna) ou NULL
 */
Pessoa *sistemaGetPessoaTripulantePorCpf(Sistema *s, char *cpf);

/**
 * @brief Obtém a fila de reservas do Sistema (não desalocar)
 * @param s Ponteiro para o Sistema
 * @return Ponteiro para Fila interna do Sistema
 */
Fila *sistemaGetFila(Sistema *s);

/**
 * @brief Calcula o preço de uma reserva com base no tipo e no passageiro
 * @param s Ponteiro para o Sistema
 * @param reserva Ponteiro para a Reserva
 * @param passageiro Ponteiro para o Passageiro
 * @return Preço calculado da reserva
 */
float sistemaCalculaPrecoReserva(Sistema *s, Reserva *reserva, Passageiro *passageiro);


/**
 * @brief Imprime todos os passageiros cadastrados
 * @param s Ponteiro para o Sistema
 */
void sistemaImprimeBancoPassageiros(Sistema *s);

/**
 * @brief Imprime todos os tripulantes cadastrados
 * @param s Ponteiro para o Sistema
 */
void sistemaImprimeBancoTripulantes(Sistema *s);

/**
 * @brief Retorna a quantidade de passageiros cadastrados
 * @param s Ponteiro para o Sistema
 * @return Quantidade de passageiros
 */
int sistemaQntdPassageiros(Sistema *s);

/**
 * @brief Retorna a quantidade de tripulantes cadastrados
 * @param s Ponteiro para o Sistema
 * @return Quantidade de tripulantes
 */
int sistemaQntdTripulantes(Sistema *s);

/**
 * @brief Calcula a média de idade (em anos) dos passageiros cadastrados
 *        Retorna apenas a parte inteira da média
 * @param s Ponteiro para o Sistema
 * @return Parte inteira da média de idade (int). Retorna 0 se não houver passageiros.
 */
int sistemaMediaIdadePassageiros(Sistema *s);

/**
 * @brief Calcula a média de horas trabalhadas pelos tripulantes (retorna apenas a parte inteira)
 * @param s Ponteiro para o Sistema
 * @return Parte inteira da média de horas trabalhadas (int). Retorna 0 se não houver tripulantes.
 */
int sistemaMediaHorasTrabalhadasTripulantes(Sistema *s);

/**
 * @brief Retorna a quantidade de reservas confirmadas
 * @param s Ponteiro para o Sistema
 * @return Quantidade de reservas confirmadas
 */
int sistemaQntdReservasConfirmadas(Sistema *s);

/**
 * @brief Retorna a quantidade de reservas canceladas
 * @param s Ponteiro para o Sistema
 * @return Quantidade de reservas canceladas
 */
int sistemaQntdReservasCanceladas(Sistema *s);

/**
 * @brief Retorna a quantidade total de reservas
 * @param s Ponteiro para o Sistema
 * @return Quantidade de reservas
 */
int sistemaQntdReservas(Sistema *s);

/**
 * @brief Retorna a quantidade de voos cadastrados
 * @param s Ponteiro para o Sistema
 * @return Quantidade de voos
 */
int sistemaQntdVoos(Sistema *s);

/**
 * @brief Retorna a quantidade de aeronaves cadastradas
 * @param s Ponteiro para o Sistema
 * @return Quantidade de aeronaves
 */
int sistemaQntdAeronaves(Sistema *s);

/**
 * @brief Imprime ranking de passageiros por reservas confirmadas (decrescente)
 * @param s Ponteiro para o Sistema
 * @param topN Número máximo de itens a imprimir (<=0 imprime todos)
 */
void sistemaImprimeRankingPassageiros(Sistema *s, int topN);

/**
 * @brief Imprime ranking de tripulantes por horas trabalhadas (decrescente)
 * @param s Ponteiro para o Sistema
 * @param topN Número máximo de itens a imprimir (<=0 imprime todos)
 */
void sistemaImprimeRankingTripulantes(Sistema *s);

/**
 * @brief Imprime um relatório resumido do sistema, com estatísticas principais
 * @param s Ponteiro para o Sistema
 */
void sistemaImprimeRelatorio(Sistema *s);
#endif /* _SISTEMA_H */
