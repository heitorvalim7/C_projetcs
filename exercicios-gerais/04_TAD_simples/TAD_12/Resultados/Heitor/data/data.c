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
