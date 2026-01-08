#include <stdio.h>
#include <stdlib.h>
#include "data.h"

struct Data {
    int dia;
    int mes;
    int ano;
};

int ehBissexto(int ano) {
    if (ano % 400 == 0) return 1;
    if (ano % 100 == 0) return 0;
    return (ano % 4 == 0);
}

int validaData( Data *d) {
    if (!d) return 0;
    if (d->ano < 0) return 0;
    if (d->mes < 1 || d->mes > 12) return 0;
    int mdays = 31;
    switch (d->mes) {
        case 4: case 6: case 9: case 11: mdays = 30; break;
        case 2: mdays = ehBissexto(d->ano) ? 29 : 28; break;
        default: mdays = 31; break;
    }
    if (d->dia < 1 || d->dia > mdays) return 0;
    return 1;
}

Data *criaData(int dia, int mes, int ano) {
    Data tmp = { .dia = dia, .mes = mes, .ano = ano };
    if (!validaData(&tmp)) return NULL;
    Data *d = (Data *)malloc(sizeof(Data));
    if (!d) return NULL;
    d->dia = dia; d->mes = mes; d->ano = ano;
    return d;
}

Data *leData() {
    int dia, mes, ano;
    if (scanf("%d/%d/%d", &dia, &mes, &ano) != 3) return NULL;
    return criaData(dia, mes, ano);
}

void imprimeData(void *dado) {
    if (!dado) return;
    Data *d = (Data *)dado;
    printf("%d/%d/%d\n", d->dia, d->mes, d->ano);
}

void desalocaData(Data *d) {
    if(d) {
        free(d);
    }
}

int getDia(Data *d) { return d ? d->dia : -1; }
int getMes(Data *d) { return d ? d->mes : -1; }
int getAno(Data *d) { return d ? d->ano : -1; }

int comparaData( Data *a,  Data *b) {
    if (!a || !b) return 0;
    if (a->ano != b->ano) return a->ano - b->ano;
    if (a->mes != b->mes) return a->mes - b->mes;
    return a->dia - b->dia;
}

int calculaIdade(Data *dataNascimento, Data *dataAtual) {
    if (!dataNascimento || !dataAtual) return -1;

    int idade = dataAtual->ano - dataNascimento->ano;

    // Ajusta se o aniversário ainda não ocorreu no ano atual
    if (dataAtual->mes < dataNascimento->mes || 
        (dataAtual->mes == dataNascimento->mes && dataAtual->dia < dataNascimento->dia)) {
        idade--;
    }

    return idade;
}