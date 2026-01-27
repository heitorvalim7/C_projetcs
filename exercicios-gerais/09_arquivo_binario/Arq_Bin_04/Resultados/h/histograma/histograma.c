#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "histograma.h"

struct tHistograma {
    int *contagem;
    int numIntervalos;
    int tamIntervalo;
};

Histograma* CalcularHistograma(Imagem* img, int nIntervalos) {
    Histograma* hist = (Histograma*)malloc(sizeof(Histograma));
    hist->numIntervalos = nIntervalos;

    if((256 % hist->numIntervalos)==0){
        hist->tamIntervalo = (256 / nIntervalos);
    } else hist->tamIntervalo = (256 / nIntervalos) + 1;

    hist->contagem = (int*)calloc(nIntervalos, sizeof(int));

    int totalPixels = ObterAlturaImagem(img) * ObterLarguraImagem(img);
    void* dados = ObterDadosImagem(img);
    int tipo = ObterTipoImagem(img);

    for (int i = 0; i < totalPixels; i++) {
        int valorPixel;

        if (tipo == 1) {
            valorPixel = ((int*)dados)[i];
        } else { 
            float fPixel = ((float*)dados)[i];
            valorPixel = (int)(fPixel * 255);
        }

        int bin = valorPixel / hist->tamIntervalo;
        
        if (bin >= nIntervalos) bin = nIntervalos - 1;
        
        hist->contagem[bin]++;
    }

    return hist;
}

void MostrarHistograma(Histograma* hist) {
    for (int i = 0; i < hist->numIntervalos; i++) {
        int limiteInferior = i * hist->tamIntervalo;
        int limiteSuperior = (i + 1) * hist->tamIntervalo;
        

        printf("[%d, %d): %d\n", limiteInferior, limiteSuperior, hist->contagem[i]);
    }
}

void DestruirHistograma(Histograma* hist) {
    if (hist) {
        free(hist->contagem);
        free(hist);
    }
}