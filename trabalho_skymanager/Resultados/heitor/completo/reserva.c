#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reserva.h"
#define tam_status 25

struct Reserva {
    char *id;           // Adicionado para setIDReserva
    char status[tam_status];       // Adicionado para setStatusReserva (ex: "CONFIRMADA")
    float preco;        // Adicionado para setPrecoReserva
    char *cpfPassageiro;
    char *codigoVoo;
    void *dado;
    func_ptr_tipo getTipo;
    func_ptr_imprime notifica; // Note que o parâmetro se chama 'imprime' no criaReserva
    func_ptr_desaloca desaloca;
    func_ptr_processa processa;
};

/**
 * @brief Aloca uma estrutura Reserva na memória e inicializa os parâmetro necessários
 * @param cpfPassageiro CPF do passageiro que está solicitando a reserva
 * @param codigoVoo Código do voo associado à reserva
 * @param dado   Uma reserva genérica  (considerando que existe mais de um tipo de reserva) 
 * @param getTipo   Função de callback que retorna o tipo da reserva
 * @param imprime  Função de callback que irá imprimir uma reserva quando for solicitada uma consulta
 * @param desaloca  Função de callback que irá desalocar  uma reserva da memória
 * @param processa  Função de callback que irá processar uma reserva
 * @return  Uma estrutura Reserva inicializada.
 */
Reserva *criaReserva(char *cpfPassageiro, char *codigoVoo, void *dado, func_ptr_tipo getTipo,
func_ptr_imprime imprime, func_ptr_desaloca desaloca, func_ptr_processa processa){
    
    if (!cpfPassageiro || !codigoVoo || !dado || !getTipo || !imprime || !desaloca || !processa) {
        return NULL;
    }

    Reserva *r = (Reserva *)malloc(sizeof(Reserva));
    if (!r) return NULL;

    strcpy(r->cpfPassageiro = (char *)malloc(strlen(cpfPassageiro) + 1), cpfPassageiro);
    strcpy(r->codigoVoo = (char *)malloc(strlen(codigoVoo) + 1), codigoVoo);
    r->dado = dado;
    r->getTipo = getTipo;
    r->notifica = imprime;
    r->desaloca = desaloca;
    r->processa = processa;
    r->preco = 0.0f; // Inicializa o preço como 0
    strcpy(r->status, "SOLICITADA"); // Inicializa o status como "SOLICITADA"
    r->id = NULL; // Inicializa o ID como NULL

    return r;
}


/**
 * @brief Compara o CPF de quem solicitou a abertura da reserva com um CPF informado
 * @param r Reserva inicializada
 * @param cpf CPF a ser comparado
 * @return 1 se os CPFs forem iguais, 0 caso contrário
 */
int comparaCPFSolicitanteReserva(Reserva *r, char *cpf){
    if (!r || !cpf) return 0;
    return strcmp(r->cpfPassageiro, cpf) == 0;
}

/**
 * @brief Processa uma reserva, verificando se os requisitos são atendidos e atualizando o status da reserva para CONFIRMADA ou CANCELADA
 * @param listaPassageiros Ponteiro para a lista de passageiros cadastrados
 * @param listaVoos Ponteiro para a lista de voos cadastrados
 * @param res Reserva a ser processada
 * @return 1 se a reserva for confirmada, 0 se for cancelada
 */
int processaReserva(void *listaPassageiros, void *listaVoos, Reserva *res){
    if (!res || !listaPassageiros || !listaVoos) return 0;
    return res->processa(listaPassageiros, listaVoos, res);
}

/**
 * @brief  Desaloca uma reserva da memória
 * @param doc estrutura do tipo Reserva que deve ser liberada da memória
 */
void desalocaReserva(Reserva *r){
    if (!r) return;
    free(r->cpfPassageiro);
    free(r->codigoVoo);
    if (r->id) {
        free(r->id);
    }
    r->desaloca(r->dado);
    free(r);
}

/**
 * @brief  Imprime uma reserva
 * @param doc Reserva a ser notificada
 */
void imprimeReserva(Reserva *r) {
    if (r && r->notifica) {
        printf("- ID: %s\n", r->id ? r->id : "N/A");
        printf("- Passageiro: %s\n", r->cpfPassageiro);
        printf("- Status: %s\n", r->status);
        printf("- Codigo do Voo: %s\n", r->codigoVoo);
        printf("- Preco: %.2f\n", r->preco);
        r->notifica(r->dado); // Chama a função de impressão específica (E, X ou P)
        printf("===============================\n");
    }
}

/**
 * @brief Atribui um preço a uma reserva
 * @param d Reserva inicializada
 * @param preco Preço a ser atribuido à reserva
 */
void setPrecoReserva(Reserva *d, float preco){
    if (!d) return;
    d->preco = preco;           
}

/**
 * @brief Atribui um status a uma reserva (CONFIRMADA, CANCELADA ou SOLICITADA)
 * @param d Reserva inicializada
 * @param status Status a ser atribuido à reserva
 */
void setStatusReserva(Reserva *d, char *status){
    if (!d || !status) return;
    strcpy(d->status, status);
}

/**
 * @brief Atribui um ID a uma reserva
 * @param d Reserva inicializada
 * @param id ID a ser atribuido à reserva
 */
void setIDReserva(Reserva *d, char *id){
    if (!d || !id) return;
    if (d->id) {
        free(d->id);
    }
    strcpy(d->id = (char *)malloc(strlen(id) + 1), id);
}

/**
 * @brief Obtem o código do voo associado a uma reserva
 * @param r Reserva inicializada
 * @return código do voo da Reserva
 */
char *getCodigoVooReserva(Reserva *r){
    if (!r) return NULL;
    return r->codigoVoo;
}

/**
 * @brief Obtem o tipo de uma reserva
 * @param r Reserva inicializada
 * @return tipo da Reserva
 */
char getTipoReserva(Reserva *r){
    if (!r || !r->getTipo) return '\0';
    return r->getTipo();
}


/**
 * @brief Obtem o CPF de quem solicitou a abertura da reserva
 * @param r Reserva inicializada
 * @return CPF de quem solicitou a abertura da reserva
 */
char *getCPFSolicitanteReserva(Reserva *r){
    if (!r) return NULL;
    return r->cpfPassageiro;
}

/**
 * @brief Obtem o status de uma reserva
 * @param r Reserva inicializada
 * @return status da Reserva
 */
char *getStatusReserva(Reserva *r){
    if (!r) return NULL;
    return r->status;
}

/**
 * @brief Obtem o dado genérico de uma reserva
 * @param r Reserva inicializada
 * @return dado genérico da Reserva
 */
void *getDadoReserva(Reserva *r){
    if (!r) return NULL;
    return r->dado;
}