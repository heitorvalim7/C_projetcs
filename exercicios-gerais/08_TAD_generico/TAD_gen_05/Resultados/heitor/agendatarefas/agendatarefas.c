#include "agendatarefas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int prioridade;
    void *dado;
    void (*executa)(void*);
    void (*desaloca)(void*);
}tarefaInterna;

struct agendatarefas{
    tarefaInterna **tarefas;
    int numElem;
    int qtdAtual;
};


/**
 * @brief Cria uma variável para um tipo genérico que representa uma Agenda de Tarefas
 *
 * @param numElem A quantidade de tarefas que serão armazenadas no agendador
 *
 * @return Um ponteiro para a agenda de tarefas
 */
tAgendaTarefas* CriaAgendaDeTarefas(int numElem){
    tAgendaTarefas *a = (tAgendaTarefas*)calloc(1, sizeof(tAgendaTarefas));
    a->tarefas = (tarefaInterna**)calloc(numElem, sizeof(tarefaInterna*));
    a->qtdAtual = 0;

    return a;
}

/**
 * @brief Destroi a agenda de tarefas (libera a memória)
 *
 * @param tar - A agenda que terá seu conteúdo liberado/destruído
 */
void DestroiAgendaDeTarefas(tAgendaTarefas* tar) {
    if (!tar) return;

    if (tar->tarefas) {
        for (int i = 0; i < tar->qtdAtual; i++) {
            if (tar->tarefas[i] != NULL) {
                if (tar->tarefas[i]->desaloca) {
                    tar->tarefas[i]->desaloca(tar->tarefas[i]->dado);
                }
                free(tar->tarefas[i]);
            }
        }
        free(tar->tarefas);
    }
    free(tar);
}


/**
 * @brief Cadastra uma tarefa em um agendador de tarefas
 *
 * @param tar - Pointeiro para a agenda de tarefas
 * @param prioridade - Prioridade de execução da nova tarefa
 * @param tarefa - Ponteiro para nova tarefa a ser executada
 * @param executa - Ponteiro para função (callback) que será chamada quando for a hora de executar a tarefa
 * @param destroi - Ponteiro para função (callback) que será chamada quando for a hora de destruir a tarefa (liberar a memória)
 *
 */
void CadastraTarefaNaAgenda(tAgendaTarefas* tar, int prioridade, void *tarefa, void (*executa)(void*), void (*destroi)(void*) ){
    tarefaInterna *nova = (tarefaInterna*)calloc(1, sizeof(tarefaInterna));
    nova->dado = tarefa;
    nova->prioridade = prioridade;
    nova->executa = executa;
    nova->desaloca = destroi;
    tar->tarefas[tar->qtdAtual]=nova;
    tar->qtdAtual++;
}   

/**
 * @brief Executa as tarefas que estão salvas na agenda de tarefas passada como parâmetro.
 *
 * @param tar Agenda de tarefas
 *
 */
void ExecutarTarefasDaAgenda(tAgendaTarefas* tar){

    for(int i = 0; i<tar->qtdAtual-1; i++){
        for(int j = 0; j<tar->qtdAtual-i-1; j++){
            if(tar->tarefas[j]->prioridade < tar->tarefas[j+1]->prioridade){
                tarefaInterna *temp = tar->tarefas[j];
                tar->tarefas[j] = tar->tarefas[j + 1];
                tar->tarefas[j + 1] = temp;
            }
        }
    }

    for(int i = 0; i<tar->qtdAtual; i++){
        if(tar->tarefas[i]->executa){
            tar->tarefas[i]->executa(tar->tarefas[i]->dado);
        }
    }
}