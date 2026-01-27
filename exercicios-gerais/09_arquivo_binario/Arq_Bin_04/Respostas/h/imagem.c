#include "imagem.h"
#include <stdio.h>
#include <stdlib.h>

struct tImagem{
    int linhas, colunas;
    Tipo tipo;
    int bytesLidos;
    void *pixels;
};

/**
 * @brief Função para ler uma imagem de um arquivo binário e aloca-la na memória.
 * @param path O caminho para o arquivo de imagem.
 * @return Um ponteiro para a imagem lida. Se houver erro (de leitura ou alocação de memória), a função imprime uma mensagem de erro e termina o programa.
 */
Imagem *LerImagem(const char *caminho){
    FILE *f = fopen(caminho, "rb");
    Imagem *i = (Imagem*)calloc(1, sizeof(Imagem));

    fread(&i->linhas, sizeof(int), 1, f);
    fread(&i->colunas, sizeof(int), 1, f);
    fread(&i->tipo, sizeof(int), 1, f);

    i->pixels = malloc((i->linhas  * i->colunas)* 4);
    fread(i->pixels, 4, (i->linhas  * i->colunas), f);
    i->bytesLidos = 3 + (i->linhas  * i->colunas);

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
 * @brief Função para obter a altura de uma imagem.
 * @param img A imagem.
 * @return A altura da imagem.
 */
int ObterAlturaImagem(Imagem *img){
    return img->linhas;
}

/**
 * @brief Função para obter a largura de uma imagem.
 * @param img A imagem.
 * @return A largura da imagem.
 */
int ObterLarguraImagem(Imagem *img){
    return img->colunas;
}

/**
 * @brief Função para obter o tipo de uma imagem.
 * @param img A imagem.
 * @return O tipo da imagem.
 */
Tipo ObterTipoImagem(Imagem *img){
    return img->tipo;
}

/**
 * @brief Função para obter os dados de uma imagem.
 * @param img A imagem.
 * @return Um ponteiro para os dados da imagem.
 */
void *ObterDadosImagem(Imagem *img){
    return img->pixels;
}