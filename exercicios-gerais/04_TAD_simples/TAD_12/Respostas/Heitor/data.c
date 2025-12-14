#include <stdio.h>
#include "data.h"

Data criaData(int dia, int mes, int ano){
    Data d;
    d.dia = dia;
    d.mes = mes;
    d.ano = ano;
}

Data lerData(){
    Data d;
    scanf("%d/%d/%d\n", &d.dia, &d.mes, &d.ano);
    return d;
}

int diferencaAnoData(Data inicial, Data atual){
    if(inicial.dia > atual.dia && inicial.mes >= atual.mes){
        return atual.ano - inicial.ano -1;
    }
    if(inicial.dia <= atual.dia && inicial.mes <= atual.mes){
        return atual.ano - inicial.ano;
    }
}

void imprimeData(Data d){
    printf("%d/%d/%d", d.dia, d.dia, d.ano);
}
