#include <stdio.h>
#include "evento.h"

void cadastrarEvento(Evento* eventos, int* numEventos){

    Evento *e = &eventos[*numEventos];
    scanf("%s\n", e->nome);
    scanf("%d %d %d\n", &e->dia, &e->mes, &e->ano); // daria pra usar &eventos[*numEventos] direto no scanf, mas ai teria que ser &eventos[*numEventos].dia e nao ->
    *(numEventos)++;
}
void exibirEventos(Evento* eventos, int* numEventos){

    for(int i = 0; i<*numEventos; i++){
        Evento *e = &eventos[i];
        printf("%d - %s - %02d/%02d/%04d\n", i, e->nome, e->dia, e->mes, e->ano);
    }
}
void trocarDataEvento(Evento* eventos, int* numEventos){
    int id;
    scanf("%d\n", &id);
    if (id < 0 || id >= *numEventos){
        printf("Indice invalido!");
    }

    for(int i = 0; i<*numEventos; i++){
        if(i == id){
            Evento *e = &eventos[i];
            scanf("%d %d %d\n", &e->dia, &e->mes, &e->ano);
        }
    }
}
void trocarIndicesEventos(Evento* eventos, int* indiceA, int* indiceB, int* numEventos){
    if ((*indiceA < 0 || *indiceA >= *numEventos)&& (*indiceB < 0 || *indiceB >= *numEventos)){
        printf("Indices invalidos!");
    } else{
        Evento troca = eventos[*indiceA];
        eventos[*indiceA] = eventos[*indiceB];
        eventos[*indiceB] = troca;
    }
    

}
