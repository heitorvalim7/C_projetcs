#include "agendatarefas.h"
#include "tarefaimprime.h"
#include "tarefasoma.h"
#include "tarefamultiplica.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main (){
    int num;
    int prioridade;
    char tarefa;
    char frase[100];
    float n1, n2;
    char buffer[100];

    printf("Digite o numero de tarefas: ");
    scanf(" %d", &num);
    tAgendaTarefas *a=CriaAgendaDeTarefas(num);

    for(int i = 0; i<num; i++){

        scanf(" %d", &prioridade);
        scanf(" %c", &tarefa);

        if( tarefa == 'I'){
            scanf(" %[^\n]", frase);
            tImpr *i = CriaTarefaImprimir(frase);
            CadastraTarefaNaAgenda(a, prioridade, i, ExecutaTarefaImprimir, DestroiTarefaImprimir);
        }
        else if(tarefa == 'M'){
            scanf("%f %f", &n1, &n2);
            tMult *i = CriaTarefaMultiplicar(n1, n2);
            CadastraTarefaNaAgenda(a, prioridade, i, ExecutaTarefaMultiplicar, DestroiTarefaMultiplicar);
        }
        else if(tarefa == 'S'){
            scanf("%f %f", &n1, &n2);
            tSoma *i = CriaTarefaSoma(n1, n2);
            CadastraTarefaNaAgenda(a, prioridade, i, ExecutaTarefaSoma, DestroiTarefaSoma);
        }
        else {
            scanf(" %[^\n]\n");
            printf("\nDigite um tipo de tarefa suportado (I/S/M))");
            limpaBuffer();
            i--;
        }
    }
    ExecutarTarefasDaAgenda(a);
    DestroiAgendaDeTarefas(a);
}