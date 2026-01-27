#include "imagem.h"
#include <stdio.h>
#include <stdlib.h>


struct tImagem{
    Tipo tipo;
    int nlinhas, ncolunas, byteslidos;
    void *pixels;
};

/**
 * @brief Função para ler uma imagem de um arquivo binário e aloca-la na memória.
 * A função também armazena o número de bytes lidos na estrutura Imagem.
 * @param path O caminho para o arquivo de imagem.
 * @return Um ponteiro para a imagem lida. Se houver erro (de leitura ou alocação de memória), a função imprime uma mensagem de erro e termina o programa.
 */
Imagem *LerImagem(const char *caminho){
    FILE *f = fopen(caminho, "rb");
    if(!f){
        return NULL;
    }
    Imagem *i = (Imagem*)calloc(1, sizeof(Imagem));
    fread(&i->nlinhas, sizeof(int), 1, f);
    fread(&i->ncolunas, sizeof(int), 1, f);
    fread(&i->tipo, sizeof(int), 1, f);
    int totalPixels = i->ncolunas * i->nlinhas;
    i->pixels = malloc(totalPixels * 4);

    fread(i->pixels, 4, totalPixels, f);
    i->byteslidos = (totalPixels)  + 3;
    fclose(f);

    return i;
}

/**
 * @brief Função para destruir uma imagem.
 * @param img A imagem a ser destruída.
 */
void DestruirImagem(Imagem *img){
    free(img->pixels);
    free(img);
}

/**
 * @brief Função para obter o número de bytes lidos de uma imagem.
 * @param img A imagem.
 * @return O número de bytes lidos.
 */
int ObterNumeroBytesLidos(Imagem *img){
    return img->byteslidos;
}

/**
 * @brief Função para imprimir uma imagem.
 * @param img A imagem.
 */
void ImprimirImagem(Imagem *img) {
    
    for (int i = 0; i < img->nlinhas; i++) {
        for (int j = 0; j < img->ncolunas; j++) {
            // Calcula a posição no vetor linear
            int idx = i * img->ncolunas + j;

            if (img->tipo == 1) { // Tipo INT [cite: 340, 343]
                int *p = (int*)img->pixels;
                printf("%d ", p[idx]);
            } else { // Tipo FLOAT [cite: 340, 344]
                float *p = (float*)img->pixels;
                printf("%.2f ", p[idx]);
            }
        }
        // Após imprimir todos os J de uma linha, pula para a próxima
        printf("\n");
    }
}
