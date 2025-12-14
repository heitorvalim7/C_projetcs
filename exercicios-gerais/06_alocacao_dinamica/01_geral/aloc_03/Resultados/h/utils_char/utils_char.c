#include "utils_char.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Cria um vetor de caracteres de tamanho especificado, alocado dinamicamente.
 * Neste caso, a string deve ser inicializada com todas as suas posições com "_"
 * Se houver erro na alocação, imprime uma mensagem de erro e encerra o programa.
 * 
 * @param tamanho Tamanho do vetor a ser criado.
 * @return Ponteiro para o vetor criado.
 */
char *CriaVetor(int tamanho){
    char *vs;
    vs = (char *)calloc(tamanho+1, sizeof(char));
    for(int i = 0; i<tamanho; i++){
        vs[i] = '_';
    }
    vs[tamanho]='\0';

    return vs;
}

/**
 * Lê uma string do tamanho especificado.
 * 
 * @param vetor Ponteiro para o vetor a ser lido.
 * @param tamanho Tamanho do vetor a ser lido.
*/
void LeVetor(char *vetor, int tamanho){
    char c;
    for(int i = 0; i < tamanho; i++){
        scanf("%c", &c);
        if(c != '\n'){
            vetor[i]=c;
        }
    }
}



/**
 * Imprime a string
 * 
 * @param vetor Ponteiro para o vetor a ser lido.
 * @param tamanho Tamanho do vetor a ser lido.
*/
void ImprimeString(char *vetor, int tamanho){
    for(int i = 0; i<tamanho; i++){
        printf("%c", vetor[i]);
    }
    printf("\n");
}

/**
 * Libera a memória alocada para um vetor de caracteres.
 * 
 * @param vetor Ponteiro para o vetor a ser liberado.
*/
void LiberaVetor(char *vetor){
    free(vetor);
}
