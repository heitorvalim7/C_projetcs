#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"
#define tam_cpf 20
#define tam_codigo_voo 20
#define tam_tipo_reserva 100

struct Sistema {
    Generico *bancoPassageiros; // Array de ponteiros para Passageiro
    Generico *bancoTripulantes; // Array de ponteiros para Tripulante
    Generico *bancoVoos;         // Array de ponteiros para Voo
    Generico *bancoAeronaves; // Array de ponteiros para Aeronave
    Fila *filaReservas;      // Fila de reservas
    Data *dataAtual;         // Data atual do sistema
};

/**
 * @brief Cria um novo Sistema, inicializando bancos vazios e uma fila
 * @return Ponteiro para o Sistema (NULL em caso de erro)
 */
Sistema *criaSistema(){
    Sistema *s = (Sistema *)malloc(sizeof(Sistema));
    if (!s) return NULL;

    s->bancoPassageiros = criaArray(imprimePassageiro, desalocaPassageiro, comparaPassageiro, verificaCPFPassageiro, getTamanhoPassageiro);
    s->bancoTripulantes = criaArray(imprimeTripulante, desalocaTripulante, comparaTripulante, verificaCPFTripulante, getTamanhoTripulante);
    s->bancoVoos = criaArray(imprimeVoo, desalocaVoo, comparaVoo, verificaCodigoVoo, NULL);
    s->bancoAeronaves = criaArray(imprimeAeronave, desalocaAeronave, comparaAeronave, verificaCodigoAeronave, NULL);
    s->filaReservas = criaFila();
    s->dataAtual = criaData(10, 12, 2025); // Inicializa com data 10/12/2025
    if (!s->filaReservas) {
        free(s);
        return NULL;
    }

    return s;
}

/*
 * @brief Roda o sistema, processando todas as reservas na fila
 * @param s Ponteiro para o Sistema
 */
void sistemaRoda(Sistema *sistema){
    char comando;



    while (scanf(" %c", &comando) == 1 && comando != 'F') {

        if (comando == 'P') {
            sistemaAdicionaPassageiro(sistema);
        }else if (comando == 'T') {
            sistemaAdicionaTripulante(sistema);
        }else if (comando == 'A') {
            sistemaAdicionaAeronave(sistema);
        } else if (comando == 'V') {
            sistemaAdicionaVoo(sistema);    
        } else if (comando == 'R') {
            sistemaAdicionaReserva(sistema);
        } else if (comando == 'E') {

            char acao[100];
            scanf(" %[^\n]", acao); 

            if (strcmp(acao, "PROCESSA RESERVAS") == 0) {
                
                processaReservasNaFila(sistemaGetFila(sistema), sistema, sistema);

            } else if (strcmp(acao, "CONSULTA RESERVAS") == 0) {

                printf("================================\n");
                printf("===== Consulta Reservas ========\n");
                printf("================================\n");
                imprimeFila(sistemaGetFila(sistema));
                printf("================================\n"); 

            } else if (strcmp(acao, "RELATORIO") == 0) {

                sistemaImprimeRelatorio(sistema); 

            } else if (strcmp(acao, "PASSAGEIROS") == 0) {

                sistemaImprimeBancoPassageiros(sistema); 

            } else if (strcmp(acao, "TRIPULANTES") == 0) {

                sistemaImprimeBancoTripulantes(sistema); 

            } else if(strcmp(acao, "RANKING PASSAGEIROS") == 0) {

                sistemaImprimeRankingPassageiros(sistema, sistemaQntdPassageiros(sistema));  
            
            } else if(strcmp(acao, "RANKING TRIPULANTES") == 0) {

                sistemaImprimeRankingTripulantes(sistema);  
            
            }
        }
    }
    return;
}


int sistemaProcessaReserva(void *ptr_sistema, void *ptr_voos, Reserva *reserva) {
    if (!ptr_sistema || !reserva) return 0;

    Sistema *s = (Sistema *)ptr_sistema;

    char *cpf = getCPFSolicitanteReserva(reserva);
    char *codVoo = getCodigoVooReserva(reserva);

    if (sistemaVerificaDadosCadastrados(s, cpf, codVoo)) {
        setStatusReserva(reserva, "CANCELADA"); 
        setPrecoReserva(reserva, 0.00);
        return 0;
    }

    Passageiro *p = sistemaBuscaPassageiroPorCpf(s, cpf);
    if (!p) {
        setStatusReserva(reserva, "CANCELADA"); 
         setPrecoReserva(reserva, 0.00);
        return 0;
    }
    
        Voo *v = sistemaBuscaVooPorCodigo(s, codVoo);
    if (!v) {
        setStatusReserva(reserva, "CANCELADA"); 
        setPrecoReserva(reserva, 0.00);
        return 0;
    }

    setStatusReserva(reserva, "CONFIRMADA"); 
    float precoFinal = sistemaCalculaPrecoReserva(s, reserva, p);
    setPrecoReserva(reserva, precoFinal);

    return 1;
}

float sistemaCalculaPrecoReserva(Sistema *s, Reserva *reserva, Passageiro *passageiro){
    if (!s || !reserva) return 0;
    char tipo = getTipoReserva(reserva);
    char *codigoVoo = getCodigoVooReserva(reserva);
    char *programaPassageiro = getProgramaPassageiro(passageiro);
    Voo *voo = sistemaBuscaVooPorCodigo(s, codigoVoo);
    int numeroBagagens;
    if (!voo) return 0; 
    float precoBase = getPrecoVoo(voo);
    if (tipo == 'X') { 
        numeroBagagens = getNumBagagensExecutiva(getDadoReserva(reserva));
        precoBase *= 1.3f;
    } else if (tipo == 'P') {
        numeroBagagens = getNumBagagensPrime(getDadoReserva(reserva));
        precoBase *= 1.7f;
    } else { 
        numeroBagagens = getNumBagagensEconomica(getDadoReserva(reserva));
        precoBase *= 1.0f;
    }

    if(strcmp(programaPassageiro, "OURO") == 0){
        precoBase *= 0.95f; 
    }
    else if(strcmp(programaPassageiro, "PRATA") == 0){
        precoBase *= 0.98f; 
    }

    precoBase += numeroBagagens * 50;
    

    
    return precoBase;
}
    


/**
 * @brief Desaloca o Sistema e todo o conteúdo (passageiros, tripulantes e fila)
 * @param s Ponteiro para o Sistema
 */
void desalocaSistema(Sistema *s){
    if (!s) return;
    desalocaArray(s->bancoPassageiros);
    desalocaArray(s->bancoTripulantes);
    desalocaArray(s->bancoVoos);
    desalocaArray(s->bancoAeronaves);
    desalocaFila(s->filaReservas);
    desalocaData(s->dataAtual);
    free(s);
}

void sistemaAdicionaReserva(Sistema *s){
    if (!s) return;
    char cpfPassageiro[tam_cpf];
    char codigoVoo[tam_codigo_voo];
    char tipoReserva[tam_tipo_reserva];

    scanf("%s\n", cpfPassageiro);
    scanf("%s\n", codigoVoo);
    scanf("%s\n", tipoReserva);
    if(strcmp(tipoReserva, "ECONOMICA") == 0){
        Economica *dadoEconomica = leEconomica();
        if (!dadoEconomica) {
            return;
        }
        insereReservaNaFila(s->filaReservas, cpfPassageiro, codigoVoo, dadoEconomica,
                            getTipoEconomica,
                            imprimeEconomica,
                            desalocaEconomica,
                            sistemaProcessaReserva);
    }else if(strcmp(tipoReserva, "EXECUTIVA") == 0){
        Executiva *dadoExecutiva = leExecutiva();
        if (!dadoExecutiva) {
            return;
        }
        insereReservaNaFila(s->filaReservas, cpfPassageiro, codigoVoo, dadoExecutiva,
                            getTipoExecutiva,
                            imprimeExecutiva,
                            desalocaExecutiva,
                            sistemaProcessaReserva);
    }else if(strcmp(tipoReserva, "PRIME") == 0){
        Prime *dadoPrime = lePrime();
        if (!dadoPrime) {
            return;
        }
        insereReservaNaFila(s->filaReservas, cpfPassageiro, codigoVoo, dadoPrime,
                            getTipoPrime,
                            imprimePrime,
                            desalocaPrime,
                            sistemaProcessaReserva);
    } 

} 

/**
 * @brief Adiciona um Passageiro ao banco do Sistema. O Sistema passa a ser responsável
 *        pela desalocação do passageiro (ou seja, guarda o ponteiro passado).
 * @param s Ponteiro para o Sistema
 * @param p Ponteiro para Passageiro (alocado pelo chamador)
 */
void sistemaAdicionaPassageiro(Sistema *s){
    if (!s) return;
    Passageiro *p = lePassageiro();
    if (!p) return;

    // Verifica se CPF já existe usando a busca genérica
    if (getItemVerificacaoArray(s->bancoPassageiros, getCpfPassageiro(p))) {
        desalocaPassageiro(p); // Ignora se duplicado [cite: 35, 37]
        return;
    }

    adicionaItemArray(s->bancoPassageiros, p);
}

/**
 * @brief Adiciona um Voo ao banco do Sistema. O Sistema passa a ser responsável
 *        pela desalocação do voo.
 * @param s Ponteiro para o Sistema
 * @param v Ponteiro para Voo (alocado pelo chamador)
 */
void sistemaAdicionaVoo(Sistema *s) {
    Voo *v = leVoo();
    if (!v) return;

    if (getItemVerificacaoArray(s->bancoVoos, getCodigoVoo(v))) {
        desalocaVoo(v);
        return;
    }
    if(getItemVerificacaoArray(s->bancoAeronaves, getCodigoAeronaveVoo(v)) == NULL){
        desalocaVoo(v);
        return;
    }
    adicionaItemArray(s->bancoVoos, v);
}


/*
 * @brief Adiciona uma Aeronave ao banco do Sistema. O Sistema passa a ser responsável
 *        pela desalocação da aeronave.
 * @param s Ponteiro para o Sistema
 * @param a Ponteiro para Aeronave (alocado pelo chamador)
 */
void sistemaAdicionaAeronave(Sistema *s){
    if (!s) return;

    /* Lê aeronave da entrada */
    Aeronave *a = leAeronave();
    if (!a) return;

    if(getItemVerificacaoArray(s->bancoAeronaves, getCodigoAeronave(a))) {
        desalocaAeronave(a);
        return;
    }
    adicionaItemArray(s->bancoAeronaves, a);
}

/**
 * @brief Adiciona um Tripulante ao banco do Sistema. O Sistema passa a ser responsável
 *        pela desalocação do tripulante.
 * @param s Ponteiro para o Sistema
 * @param t Ponteiro para Tripulante (alocado pelo chamador)
 * @return 1 em sucesso, 0 em falha
 */
void sistemaAdicionaTripulante(Sistema *s){
    if (!s) return;
    Tripulante *t = leTripulante();
    if (!t) return;

    if (getItemVerificacaoArray(s->bancoTripulantes, getCPFTripulante(t))) {
        desalocaTripulante(t); 
        return;
    }

    adicionaItemArray(s->bancoTripulantes, t);
}

int sistemaVerificaDadosCadastradosPessoa(void *dado1, void *dado2){
    Sistema *s = (Sistema *)dado1;
    char *cpfPassageiro = (char *)dado2;

    if (!s || !cpfPassageiro) return 0;

    Passageiro *p = sistemaBuscaPassageiroPorCpf(s, cpfPassageiro);
    if (!p) return 1;

    return 0;
}

int sistemaVerificaDadosCadastradosAeronave(void *dado1, void *dado2){
    Sistema *s = (Sistema *)dado1;
    char *codigoAeronave = (char *)dado2;

    if (!s || !codigoAeronave) return 0;

    Aeronave *a = sistemaBuscaAeronavePorCodigo(s, codigoAeronave);
    if (!a) return 1;

    return 0;
}

int sistemaVerificaDadosCadastrados(Sistema *s, char *codigoVoo, char *cpfPassageiro){
    if (!s || !cpfPassageiro) return 0;

    Passageiro *p = sistemaBuscaPassageiroPorCpf(s, cpfPassageiro);
    if (!p) return 0;

    if (!codigoVoo) return 0;

    Voo *v = sistemaBuscaVooPorCodigo(s, codigoVoo);
    if (!v) return 0;

    return 1;
}

int sistemaVerificaDadosCadastradosVoo(void *dado1, void *dado2){
    Sistema *s = (Sistema *)dado1;
    char *codigoVoo = (char *)dado2;

    if (!s || !codigoVoo) return 0;

    Voo *v = sistemaBuscaVooPorCodigo(s, codigoVoo);
    if (!v) return 1;

    return 0;
}

Voo *sistemaBuscaVooPorCodigo(Sistema *s, char *codigoVoo){
    return (Voo *)getItemVerificacaoArray(s->bancoVoos, codigoVoo);
}

Aeronave *sistemaBuscaAeronavePorCodigo(Sistema *s, char *codigoAeronave){
    return (Aeronave *)getItemVerificacaoArray(s->bancoAeronaves, codigoAeronave);
}

/**
 * @brief Busca um Passageiro pelo CPF
 * @param s Ponteiro para o Sistema
 * @param cpf CPF do passageiro
 * @return Ponteiro para Passageiro (interno) ou NULL se não encontrado
 */
Passageiro *sistemaBuscaPassageiroPorCpf(Sistema *s, char *cpf){
    return (Passageiro *)getItemVerificacaoArray(s->bancoPassageiros, cpf);
}

/**
 * @brief Busca um Tripulante pelo CPF
 * @param s Ponteiro para o Sistema
 * @param cpf CPF do tripulante
 * @return Ponteiro para Tripulante (interno) ou NULL se não encontrado
 */
Tripulante *sistemaBuscaTripulantePorCpf(Sistema *s, char *cpf){
    return (Tripulante *)getItemVerificacaoArray(s->bancoTripulantes, cpf);
}

/**
 * @brief Conveniência: obtém a Pessoa associada a um passageiro identificado pelo CPF
 * @param s Ponteiro para o Sistema
 * @param cpf CPF do passageiro
 * @return Ponteiro para Pessoa (interna) ou NULL
 */
Pessoa *sistemaGetPessoaPassageiroPorCpf(Sistema *s, char *cpf){
    if (!s || !cpf) return NULL;
    Passageiro *p = sistemaBuscaPassageiroPorCpf(s, cpf);
    if (!p) return NULL;
    return getPessoaPassageiro(p);
}

/**
 * @brief Conveniência: obtém a Pessoa associada a um tripulante identificado pelo CPF
 * @param s Ponteiro para o Sistema
 * @param cpf CPF do tripulante
 * @return Ponteiro para Pessoa (interna) ou NULL
 */
Pessoa *sistemaGetPessoaTripulantePorCpf(Sistema *s, char *cpf){
    if (!s || !cpf) return NULL;
    Tripulante *t = sistemaBuscaTripulantePorCpf(s, cpf);
    if (!t) return NULL;
    return getPessoaTripulante(t);
}

/**
 * @brief Obtém a fila de reservas do Sistema (não desalocar)
 * @param s Ponteiro para o Sistema
 * @return Ponteiro para Fila interna do Sistema
 */
Fila *sistemaGetFila(Sistema *s){
    if (!s) return NULL;
    return s->filaReservas;
}


/**
 * @brief Imprime todos os passageiros cadastrados
 * @param s Ponteiro para o Sistema
 */
void sistemaImprimeBancoPassageiros(Sistema *s){
    if (!s) return;

    printf("================================\n");
    printf("===== Banco de Passageiros =====\n");
    printf("================================\n");

    imprimeArray(s->bancoPassageiros);
    printf("================================\n");

}

/**
 * @brief Imprime todos os tripulantes cadastrados
 * @param s Ponteiro para o Sistema
 */
void sistemaImprimeBancoTripulantes(Sistema *s){
    if (!s) return;
    printf("================================\n");
    printf("===== Banco de Tripulantes =====\n");
    printf("================================\n");
    imprimeArray(s->bancoTripulantes);
    printf("================================\n");

}

/**
 * @brief Retorna a quantidade de passageiros cadastrados
 * @param s Ponteiro para o Sistema
 * @return Quantidade de passageiros
 */
int sistemaQntdPassageiros(Sistema *s){
    return getTamanhoArray(s->bancoPassageiros);
}

/**
 * @brief Retorna a quantidade de tripulantes cadastrados
 * @param s Ponteiro para o Sistema
 * @return Quantidade de tripulantes
 */
int sistemaQntdTripulantes(Sistema *s){
    return getTamanhoArray(s->bancoTripulantes);
}

/**
 * @brief Calcula a média de idade (em anos) dos passageiros cadastrados
 * @param s Ponteiro para o Sistema
 * @return Média de idade (int). Retorna 0 se não houver passageiros.
 */
int sistemaMediaIdadePassageiros(Sistema *s) {
    if (!s) return 0;

    int tam = getTamanhoArray(s->bancoPassageiros);
    if (tam == 0) return 0;

    int somaIdades = 0;
    for (int i = 0; i < tam; i++) {
        Passageiro *p = (Passageiro *)getItemPosicaoArray(s->bancoPassageiros, i);
        
        Pessoa *pessoa = getPessoaPassageiro(p);
        Data *d = getDataNascimentoPessoa(pessoa);
        
        somaIdades += calculaIdade(d, s->dataAtual);
    }

    return somaIdades / tam; // Retorna a parte inteira [cite: 293]
}

/**
 * @brief Calcula a média de horas trabalhadas pelos tripulantes (retorna apenas a parte inteira)
 * @param s Ponteiro para o Sistema
 * @return Parte inteira da média de horas trabalhadas (int). Retorna 0 se não houver tripulantes.
 */
int sistemaMediaHorasTrabalhadasTripulantes(Sistema *s){
    if (!s) return 0;

    int tam = getTamanhoArray(s->bancoTripulantes);
    if (tam == 0) return 0;
    int somaHoras = 0;
    for (int i = 0; i < tam; i++) {
        Tripulante *t = (Tripulante *)getItemPosicaoArray(s->bancoTripulantes, i);
        somaHoras += getHorasTripulante(t);
    }

    return somaHoras / tam;
}

/**
 * @brief Retorna a quantidade de reservas confirmadas
 * @param s Ponteiro para o Sistema
 * @return Quantidade de reservas confirmadas
 */
int sistemaQntdReservasConfirmadas(Sistema *s){
    if (!s) return 0;
    return getQntdReservasConfirmadasFila(s->filaReservas);
}

/**
 * @brief Retorna a quantidade de reservas canceladas
 * @param s Ponteiro para o Sistema
 * @return Quantidade de reservas canceladas
 */
int sistemaQntdReservasCanceladas(Sistema *s){
    if (!s) return 0;
    int totalReservas = getQntdReservaFila(s->filaReservas);
    int confirmadas = getQntdReservasConfirmadasFila(s->filaReservas);
    return totalReservas - confirmadas;
}

/**
 * @brief Retorna a quantidade total de reservas
 * @param s Ponteiro para o Sistema
 * @return Quantidade de reservas
 */
int sistemaQntdReservas(Sistema *s){
    if (!s) return 0;
    return getQntdReservaFila(s->filaReservas);
}

/**
 * @brief Retorna a quantidade de voos cadastrados
 * @param s Ponteiro para o Sistema
 * @return Quantidade de voos
 */
int sistemaQntdVoos(Sistema *s){
    return getTamanhoArray(s->bancoVoos);
}

/**
 * @brief Retorna a quantidade de aeronaves cadastradas
 * @param s Ponteiro para o Sistema
 * @return Quantidade de aeronaves
 */
int sistemaQntdAeronaves(Sistema *s){
    return getTamanhoArray(s->bancoAeronaves);
}

/**
 * @brief Imprime ranking de passageiros por reservas confirmadas (decrescente)
 * @param s Ponteiro para o Sistema
 * @param topN Número máximo de itens a imprimir (<=0 imprime todos)
 */
void sistemaImprimeRankingPassageiros(Sistema *s, int topN){
    if (!s) return;
    ordenaArray(s->bancoPassageiros); 
    printf("================================\n");
    printf("===== Ranking Passageiros =====\n");
    printf("================================\n");
    imprimeArray(s->bancoPassageiros);
    printf("================================\n");
}

/**
 * @brief Imprime ranking de tripulantes por horas trabalhadas (decrescente)
 * @param s Ponteiro para o Sistema
 * @param topN Número máximo de itens a imprimir (<=0 imprime todos)
 */
void sistemaImprimeRankingTripulantes(Sistema *s){
    if (!s) return;
    ordenaArray(s->bancoTripulantes); 
    printf("================================\n");
    printf("===== Ranking Tripulantes =====\n");
    printf("================================\n");
    imprimeArray(s->bancoTripulantes); 
    printf("================================\n");
}
void sistemaImprimeRelatorio(Sistema *s){
    printf("=============================\n");
    printf("========= RELATORIO =========\n");
    printf("=============================\n");
    printf("- Aeronaves: %d\n", sistemaQntdAeronaves(s));
    printf("- Voos: %d\n", sistemaQntdVoos(s));
    printf("- Reservas: %d\n", sistemaQntdReservas(s));
    printf("- Reservas confirmadas: %d\n", sistemaQntdReservasConfirmadas(s));
    printf("- Passageiros: %d\n", sistemaQntdPassageiros(s));
    printf("- Media de idade passageiros: %d\n", sistemaMediaIdadePassageiros(s));
    printf("- Tripulantes: %d\n", sistemaQntdTripulantes(s));
    printf("- Media de horas trabalhadas: %d\n", sistemaMediaHorasTrabalhadasTripulantes(s));  
    printf("=============================\n");
}

