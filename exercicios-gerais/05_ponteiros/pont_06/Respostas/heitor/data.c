#include "data.h"
#include <stdio.h>

void InicializaDataParam(int dia, int mes, int ano, tData *data){
    data->ano = ano;

    if (mes >= 1 && mes <= 12)
        data->mes = mes;
    else
        data->mes = 12; 

    int maxDias = InformaQtdDiasNoMes(data);

    if (dia < 1)
        data->dia = 1;
    else if (dia > maxDias)
        data->dia = maxDias;
    else
        data->dia = dia;
}
void LeData( tData *data ){
    scanf("%d %d %d\n", &data->dia, &data->mes, &data->ano);
    InicializaDataParam(data->dia, data->mes, data->ano, data);
}
void ImprimeData( tData *data ){
    printf("'%02d/%02d/%04d'", data->dia, data->mes, data->ano);
}
int EhBissexto( tData *data ){
    if ((data->ano % 4 == 0 && data->ano % 100 != 0) || (data->ano % 400 == 0)){
        return 1;
    }
    return 0;
}
int InformaQtdDiasNoMes( tData *data ){
    switch (data->mes)
    {
    case 1:
        return 31;
  
    case 2:
        if(EhBissexto(data)){
            return 29;
        } else return 28;
        
    case 3:
        return 31;
        
    case 4:
        return 30;
        
    case 5:
        return 31;
        
    case 6:
        return 30;
        
    case 7:
        return 31;
        
    case 8:
        return 31;
        
    case 9:
        return 30;
        
    case 10:
        return 31;
        
    case 11:
        return 30;
        
    case 12:
        return 31;
        
    default:
        return 0;
    }
    
}
void AvancaParaDiaSeguinte( tData *data ){
    data->dia++;
    if(InformaQtdDiasNoMes(data)<data->dia){
        data->dia = 1;
        data->mes++;
        if(data->mes > 12){
            data->mes = 1;
            data->ano++;
        }
    }
}
int EhIgual( tData *data1, tData *data2 ){
    if(data1->dia == data2->dia && data1->mes == data2->mes && data1->ano == data2->ano){
        return 1;
    }
    return 0;
}

