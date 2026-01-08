



#ifndef _RESERVA_H_
#define _RESERVA_H_

/**
 * Estrutura de uma Reserva contendo os parametros comuns entre todos os tipos de Reservas e um tipo genérico.
 */
typedef struct Reserva Reserva;

/**
 * @brief Função de callback para imprimir uma reserva quando for solicitada uma consulta
 * @param dado um tipo genérico para representar os tipos de reservas.
 */
typedef void (*func_ptr_imprime)(void *dado);

/**
 * @brief Função de callback para desalocar da memória uma implementação especifica de reserva
 * @param dado um tipo genérico para representar os tipos de reservas.
 */
typedef void (*func_ptr_desaloca)(void *dado);

/*
 * @brief Função de callback para obter o tipo de uma reserva
 * @return caracter representando o tipo da reserva ('E' = Econômica, 'X' = Executiva, 'P' = Prime)
*/
typedef char (*func_ptr_tipo)();

/*
 * @brief Função de callback para processar uma reserva. Processar significa determinar se ela pode ser confirmada ou deve ser cancelada.
 * @param listaPassageiros Ponteiro para a lista de passageiros cadastrados
 * @param listaVoos Ponteiro para a lista de voos cadastrados
 * @param res Reserva a ser processada
 * @return 1 se a reserva for confirmada, 0 se for cancelada
*/
typedef int (*func_ptr_processa)(void *listaPassageiros, void *listaVoos, Reserva *res);


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
                    func_ptr_imprime imprime, func_ptr_desaloca desaloca, func_ptr_processa processa);

/**
 * @brief Compara o CPF de quem solicitou a abertura da reserva com um CPF informado
 * @param r Reserva inicializada
 * @param cpf CPF a ser comparado
 * @return 1 se os CPFs forem iguais, 0 caso contrário
 */
int comparaCPFSolicitanteReserva(Reserva *r, char *cpf);

/**
 * @brief Processa uma reserva, verificando se os requisitos são atendidos e atualizando o status da reserva para CONFIRMADA ou CANCELADA
 * @param listaPassageiros Ponteiro para a lista de passageiros cadastrados
 * @param listaVoos Ponteiro para a lista de voos cadastrados
 * @param res Reserva a ser processada
 * @return 1 se a reserva for confirmada, 0 se for cancelada
 */
int processaReserva(void *listaPassageiros, void *listaVoos, Reserva *res);

/**
 * @brief  Desaloca uma reserva da memória
 * @param doc estrutura do tipo Reserva que deve ser liberada da memória
 */
void desalocaReserva(Reserva *r);

/**
 * @brief  Imprime uma reserva
 * @param doc Reserva a ser notificada
 */
void imprimeReserva(Reserva *r);

/**
 * @brief Atribui um preço a uma reserva
 * @param d Reserva inicializada
 * @param preco Preço a ser atribuido à reserva
 */
void setPrecoReserva(Reserva *d, float preco);

/**
 * @brief Atribui um status a uma reserva (CONFIRMADA, CANCELADA ou SOLICITADA)
 * @param d Reserva inicializada
 * @param status Status a ser atribuido à reserva
 */
void setStatusReserva(Reserva *d, char *status);

/**
 * @brief Atribui um ID a uma reserva
 * @param d Reserva inicializada
 * @param id ID a ser atribuido à reserva
 */
void setIDReserva(Reserva *d, char *id);

/**
 * @brief Obtem o código do voo associado a uma reserva
 * @param r Reserva inicializada
 * @return código do voo da Reserva
 */
char *getCodigoVooReserva(Reserva *r);

/**
 * @brief Obtem o tipo de uma reserva
 * @param r Reserva inicializada
 * @return tipo da Reserva
 */
char getTipoReserva(Reserva *r);


/**
 * @brief Obtem o CPF de quem solicitou a abertura da reserva
 * @param r Reserva inicializada
 * @return CPF de quem solicitou a abertura da reserva
 */
char *getCPFSolicitanteReserva(Reserva *r);

/**
 * @brief Obtem o status de uma reserva
 * @param r Reserva inicializada
 * @return status da Reserva
 */
char *getStatusReserva(Reserva *r);

/**
 * @brief Obtem o dado genérico de uma reserva
 * @param r Reserva inicializada
 * @return dado genérico da Reserva
 */
void *getDadoReserva(Reserva *r);


#endif  // _RESERVA_H_