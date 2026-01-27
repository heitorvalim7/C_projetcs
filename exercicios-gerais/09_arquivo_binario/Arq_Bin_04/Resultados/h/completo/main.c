#include "histograma.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    char nome[100];
    int intervalos;
    scanf("%s", nome);
    scanf("%d", &intervalos);
    Imagem *i = LerImagem(nome);
    Histograma *h = CalcularHistograma(i, intervalos);
    MostrarHistograma(h);
    DestruirHistograma(h);
    DestruirImagem(i);

    return 0;
}