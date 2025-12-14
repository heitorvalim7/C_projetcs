#include <stdio.h>
#include <string.h>
#include "paciente.h"
#include "lesao.h"
#include "data.h"

Paciente criaPaciente(char *nome, char *cartaoSus, char genero, Data dataNasc){
    Paciente p;
    strcpy(p.nome, nome);
    strcpy(p.cartaoSus, cartaoSus);
    p.genero = genero;
    p.dataNasc = dataNasc;
    p.numLesoes = 0;

    return p;
}

Paciente lerPaciente(){
    Paciente p;
    scanf("%[^\n]\n", p.nome);
    p.dataNasc = lerData();
    scanf("%[^\n]\n", p.cartaoSus);
    scanf("%c\n", &p.genero);
    p.numLesoes = 0;

    return p;
}

Paciente vinculaLesaoPaciente(Paciente p, Lesao l){
    p.lesoes[p.numLesoes] = l;
    p.numLesoes++;

    return p;
}

void getCartaoSusPaciente(Paciente p, char *cartaoSus){
    strcpy(cartaoSus, p.cartaoSus);
}

