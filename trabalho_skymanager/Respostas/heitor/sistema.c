#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"
#define tam_cpf 20
#define tam_codigo_voo 20
#define tam_tipo_reserva 100

struct Sistema {
    Passageiro **bancoPassageiros; // Array de ponteiros para Passageiro
    int numPassageiros;
    Tripulante **bancoTripulantes; // Array de ponteiros para Tripulante
    int numTripulantes;
    Voo **bancoVoos;         // Array de ponteiros para Voo
    int numVoos;
    Aeronave **bancoAeronaves; // Array de ponteiros para Aeronave
    int numAeronaves;
    Fila *filaReservas;      // Fila de reservas
    Data *dataAtual;         // Data atual do sistema
};

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
 * @brief Cria um novo Sistema, inicializando bancos vazios e uma fila
 * @return Ponteiro para o Sistema (NULL em caso de erro)
 */
Sistema *criaSistema(){
    Sistema *s = (Sistema *)malloc(sizeof(Sistema));
    if (!s) return NULL;

    s->bancoPassageiros = NULL;
    s->numPassageiros = 0;
    s->bancoTripulantes = NULL;
    s->numTripulantes = 0;
    s->bancoVoos = NULL;
    s->numVoos = 0;
    s->bancoAeronaves = NULL;
    s->numAeronaves = 0;
    s->filaReservas = criaFila();
    s->dataAtual = criaData(10, 12, 2025); // Inicializa com data 10/12/2025
    if (!s->filaReservas) {
        free(s);
        return NULL;
    }

    return s;
}

/**
 * @brief Desaloca o Sistema e todo o conteúdo (passageiros, tripulantes e fila)
 * @param s Ponteiro para o Sistema
 */
void desalocaSistema(Sistema *s){
    if (!s) return;

    for (int i = 0; i < s->numPassageiros; i++) {
        desalocaPassageiro(s->bancoPassageiros[i]);
    }
    free(s->bancoPassageiros);

    for (int i = 0; i < s->numTripulantes; i++) {
        desalocaTripulante(s->bancoTripulantes[i]);
    }
    free(s->bancoTripulantes);

    for(int i = 0; i < s->numVoos; i++) {
        desalocaVoo(s->bancoVoos[i]);
    }
    free(s->bancoVoos);

    for(int i = 0; i < s->numAeronaves; i++) {
        desalocaAeronave(s->bancoAeronaves[i]);
    }
    free(s->bancoAeronaves);    

    desalocaFila(s->filaReservas);
    if(s->dataAtual){
    desalocaData(s->dataAtual);
    }
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

    /* Lê passageiro da entrada */
    Passageiro *p = lePassageiro();
    if (!p) return;

    if (!sistemaVerificaDadosCadastradosPessoa(s, getCpfPassageiro(p))) {
        desalocaPassageiro(p);
        return;
    }
    Passageiro **tmp = (Passageiro **)realloc(s->bancoPassageiros, (s->numPassageiros + 1) * sizeof(Passageiro *));
    if (!tmp) {
        desalocaPassageiro(p);
        return;
    }

    s->bancoPassageiros = tmp;
    s->bancoPassageiros[s->numPassageiros] = p;
    s->numPassageiros++;
}

/**
 * @brief Adiciona um Voo ao banco do Sistema. O Sistema passa a ser responsável
 *        pela desalocação do voo.
 * @param s Ponteiro para o Sistema
 * @param v Ponteiro para Voo (alocado pelo chamador)
 */
void sistemaAdicionaVoo(Sistema *s){ 
    if (!s) return;

    /* Lê voo da entrada */
    Voo *v = leVoo(s->bancoAeronaves, s->numAeronaves);
    if (!v) return;

    if(!sistemaVerificaDadosCadastradosVoo(s, getCodigoVoo(v))) {
        desalocaVoo(v);
        return;
    }
    if(sistemaVerificaDadosCadastradosAeronave(s, getCodigoAeronaveVoo(v))) {
        desalocaVoo(v);
        return;
    }
    Voo **tmp = (Voo **)realloc(s->bancoVoos, (s->numVoos + 1) * sizeof(Voo *));
    if (!tmp) {
        desalocaVoo(v);
        return;
    }

    s->bancoVoos = tmp;
    s->bancoVoos[s->numVoos] = v;
    s->numVoos++;

;
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

    if(!sistemaVerificaDadosCadastradosAeronave(s, getCodigoAeronave(a))) {
        desalocaAeronave(a);
        return;
    }

    Aeronave **tmp = (Aeronave **)realloc(s->bancoAeronaves, (s->numAeronaves + 1) * sizeof(Aeronave *));
    if (!tmp) {
        desalocaAeronave(a);
        return;
    }

    s->bancoAeronaves = tmp;
    s->bancoAeronaves[s->numAeronaves] = a;
    s->numAeronaves++;
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

    /* Lê tripulante da entrada */
    Tripulante *t = leTripulante();
    if (!t) return;

    if(!sistemaVerificaDadosCadastradosPessoa(s, getCPFTripulante(t))) {
        desalocaTripulante(t);
        return;
    }

    Tripulante **tmp = (Tripulante **)realloc(s->bancoTripulantes, (s->numTripulantes + 1) * sizeof(Tripulante *));
    if (!tmp) {
        desalocaTripulante(t);
        return;
    }

    s->bancoTripulantes = tmp;
    s->bancoTripulantes[s->numTripulantes] = t;
    s->numTripulantes++;
}

int sistemaVerificaDadosCadastradosPessoa(Sistema *s, char *cpfPassageiro){
    if (!s || !cpfPassageiro) return 0;

    Passageiro *p = sistemaBuscaPassageiroPorCpf(s, cpfPassageiro);
    if (!p) return 1;

    return 0;
}

int sistemaVerificaDadosCadastradosAeronave(Sistema *s, char *codigoAeronave){
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

int sistemaVerificaDadosCadastradosVoo(Sistema *s, char *codigoVoo){
    if (!s || !codigoVoo) return 0;

    Voo *v = sistemaBuscaVooPorCodigo(s, codigoVoo);
    if (!v) return 1;

    return 0;
}

Voo *sistemaBuscaVooPorCodigo(Sistema *s, char *codigoVoo){
    if (!s || !codigoVoo) return NULL;
    for (int i = 0; i < s->numVoos; i++) {
        if (strcmp(getCodigoVoo(s->bancoVoos[i]), codigoVoo) == 0) {
            return s->bancoVoos[i];
        }
    }
    return NULL;
}

Aeronave *sistemaBuscaAeronavePorCodigo(Sistema *s, char *codigoAeronave){
    if (!s || !codigoAeronave) return NULL;
    for (int i = 0; i < s->numAeronaves; i++) {
        if (strcmp(getCodigoAeronave(s->bancoAeronaves[i]), codigoAeronave) == 0) {
            return s->bancoAeronaves[i];
        }
    }
    return NULL;
}

/**
 * @brief Busca um Passageiro pelo CPF
 * @param s Ponteiro para o Sistema
 * @param cpf CPF do passageiro
 * @return Ponteiro para Passageiro (interno) ou NULL se não encontrado
 */
Passageiro *sistemaBuscaPassageiroPorCpf(Sistema *s,  char *cpf){
    if (!s || !cpf) return NULL;
    for (int i = 0; i < s->numPassageiros; i++) {
        if (strcmp(getCPFPessoa(getPessoaPassageiro(s->bancoPassageiros[i])), cpf) == 0) {
            return s->bancoPassageiros[i];
        }
    }
    return NULL;
}

/**
 * @brief Busca um Tripulante pelo CPF
 * @param s Ponteiro para o Sistema
 * @param cpf CPF do tripulante
 * @return Ponteiro para Tripulante (interno) ou NULL se não encontrado
 */
Tripulante *sistemaBuscaTripulantePorCpf(Sistema *s, char *cpf){
    if (!s || !cpf) return NULL;
    for (int i = 0; i < s->numTripulantes; i++) {
        if (strcmp(getCPFTripulante(s->bancoTripulantes[i]), cpf) == 0) {
            return s->bancoTripulantes[i];
        }
    }
    return NULL;
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

    for (int i = 0; i < s->numPassageiros; i++) {
        imprimePassageiro(s->bancoPassageiros[i]);
    }
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
    for (int i = 0; i < s->numTripulantes; i++) {
        imprimeTripulante(s->bancoTripulantes[i]);
    }
    printf("================================\n");

}

/**
 * @brief Retorna a quantidade de passageiros cadastrados
 * @param s Ponteiro para o Sistema
 * @return Quantidade de passageiros
 */
int sistemaQntdPassageiros(Sistema *s){
    if (!s) return 0;
    return s->numPassageiros;
}

/**
 * @brief Retorna a quantidade de tripulantes cadastrados
 * @param s Ponteiro para o Sistema
 * @return Quantidade de tripulantes
 */
int sistemaQntdTripulantes(Sistema *s){
    if (!s) return 0;
    return s->numTripulantes;
}

/**
 * @brief Calcula a média de idade (em anos) dos passageiros cadastrados
 * @param s Ponteiro para o Sistema
 * @return Média de idade (int). Retorna 0 se não houver passageiros.
 */
int sistemaMediaIdadePassageiros(Sistema *s){
    if (!s || s->numPassageiros == 0) return 0;

    int somaIdades = 0;
    for (int i = 0; i < s->numPassageiros; i++) {
        Pessoa *pessoa = getPessoaPassageiro(s->bancoPassageiros[i]);
        Data *d = getDataNascimentoPessoa(pessoa);
        int idade = calculaIdade(d, s->dataAtual);
        somaIdades += idade;    
    }

    return somaIdades / s->numPassageiros;
}

/**
 * @brief Calcula a média de horas trabalhadas pelos tripulantes (retorna apenas a parte inteira)
 * @param s Ponteiro para o Sistema
 * @return Parte inteira da média de horas trabalhadas (int). Retorna 0 se não houver tripulantes.
 */
int sistemaMediaHorasTrabalhadasTripulantes(Sistema *s){
    if (!s || s->numTripulantes == 0) return 0;

    int somaHoras = 0;
    for (int i = 0; i < s->numTripulantes; i++) {
        somaHoras += getHorasTripulante(s->bancoTripulantes[i]);
    }

    return somaHoras / s->numTripulantes;
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
    if( !s) return 0;
    return s->numVoos;
}

/**
 * @brief Retorna a quantidade de aeronaves cadastradas
 * @param s Ponteiro para o Sistema
 * @return Quantidade de aeronaves
 */
int sistemaQntdAeronaves(Sistema *s){
    if( !s) return 0;
    return s->numAeronaves;
}

/**
 * @brief Imprime ranking de passageiros por reservas confirmadas (decrescente)
 * @param s Ponteiro para o Sistema
 * @param topN Número máximo de itens a imprimir (<=0 imprime todos)
 */
void sistemaImprimeRankingPassageiros(Sistema *s, int topN){
    if (!s) return;
    passageiroImprimeRankingPorReservas(s->bancoPassageiros, s->numPassageiros, topN);
}

/**
 * @brief Imprime ranking de tripulantes por horas trabalhadas (decrescente)
 * @param s Ponteiro para o Sistema
 * @param topN Número máximo de itens a imprimir (<=0 imprime todos)
 */
void sistemaImprimeRankingTripulantes(Sistema *s){
    if (!s) return;
    tripulanteImprimeRankingPorHoras(s->bancoTripulantes, s->numTripulantes);
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

