#include "tabuleiro.h"
#include <stdio.h>
#include <stdlib.h>

struct Tabuleiro{
    int peca;
    char desTab, pos[3][3];
};

/**
 * Aloca e retorna uma estrutura do tipo tTabuleiro.
 * Se a alocação falhar, o programa é encerrado.
 * 
 * @return a estrutura do tipo tTabuleiro alocada.
 */
tTabuleiro* CriaTabuleiro(){
    tTabuleiro *t;
    t = (tTabuleiro*)calloc(1, sizeof(struct Tabuleiro));
    t->desTab = '-';
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            t->pos[i][j]=t->desTab;
        }
    }
    return t;
}


/**
 * Libera a memória de uma estrutura do tipo tTabuleiro.
 * 
 * @param tabuleiro a estrutura do tipo tTabuleiro a ser liberada.
 */
void DestroiTabuleiro(tTabuleiro* tabuleiro){
    free(tabuleiro);
}


/**
 * Marca uma posição do tabuleiro com a peça do jogador.
 * 
 * @param tabuleiro o tabuleiro atual.
 * @param peca a peça do jogador (1 ou 2).
 * @param x a coordenada X da posição.
 * @param y a coordenada Y da posição.
 */
void MarcaPosicaoTabuleiro(tTabuleiro* tabuleiro, int peca, int x, int y){
    if(peca == 1){
        tabuleiro->pos[x][y]='X';
    }
    else tabuleiro->pos[x][y]='0';
}


/**
 * Verifica se há alguma posição livre no tabuleiro.
 * 
 * @param tabuleiro o tabuleiro atual.
 * 
 * @return 1 se há alguma posição livre, 0 caso contrário.
 */
int TemPosicaoLivreTabuleiro(tTabuleiro* tabuleiro){
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            if(tabuleiro->pos[i][j] == '-'){
                return 1;
            }
        }
    }
    return 0;
}


/**
 * Verifica se a posição do tabuleiro está marcada com a peça do jogador.
 * 
 * @param tabuleiro - o tabuleiro atual.
 * @param x a coordenada X da posição.
 * @param y a coordenada Y da posição.
 * @param peca a peça do jogador (1 ou 2).
 * 
 * @return 1 se a posição está marcada com a peça do jogador, 0 caso contrário.
 */
int EstaMarcadaPosicaoPecaTabuleiro(tTabuleiro* tabuleiro, int x, int y, int peca){
    if(peca == 1){
        if(tabuleiro->pos[x][y]=='X'){
            return 1;
        }
        return 0;
    }
    if(peca == 2){
        if(tabuleiro->pos[x][y]=='0'){
            return 1;
        }
        return 0;
    }
    return 0;
}


/**
 * Verifica se a posição do tabuleiro está livre.
 * 
 * @param tabuleiro o tabuleiro atual.
 * @param x a coordenada X da posição.
 * @param y a coordenada Y da posição.
 * 
 * @return 1 se a posição está livre, 0 caso contrário.
 */
int EstaLivrePosicaoTabuleiro(tTabuleiro* tabuleiro, int x, int y){
    if(tabuleiro->pos[x][y]=='-'){
        return 1;
    }
    return 0;
}


/**
 * Verifica se a posição do tabuleiro é válida.
 * 
 * @param x a coordenada X da posição.
 * @param y a coordenada Y da posição.
 * 
 * @return 1 se a posição é válida, 0 caso contrário.
 */
int EhPosicaoValidaTabuleiro(int x, int y){
    if(x<=2 && y <=2 && y>=0 && x >=0){
        return 1;
    }return 0;
}


/**
 * Imprime o tabuleiro.
 * 
 * @param tabuleiro o tabuleiro atual.
 */
void ImprimeTabuleiro(tTabuleiro* tabuleiro){
    for(int i = 0; i<3; i++){
        printf("           ");
        for(int j = 0; j<3; j++){
            printf("%c",tabuleiro->pos[j][i]);
        }
        printf("\n");
    }
}
