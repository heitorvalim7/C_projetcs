#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// constantes
#define MAX_CARROS 10
#define MAX_PISTAS 12
#define MAX_LARGURA 101 // largura maxima do mapa interno
#define MAX_ALTURA 35   // altura maxima do mapa interno
#define ALTURA_PERSONAGEM 2
#define LARGURA_PERSONAGEM 3
#define MAX_DESENHOS_CARRO 4
#define MAX_CARROS_ANIMACAO 4
#define ALTURA_MAX 500 //so pra evitar overflow
#define LARGURA_MAX 500 //so pra evitar overflow tb
#define MAX_VIDAS 3
//structs

typedef struct {
    char galinha[ALTURA_PERSONAGEM][LARGURA_PERSONAGEM + 2];
    char carro[ALTURA_PERSONAGEM][LARGURA_PERSONAGEM + 2];
    char carros_bonus[MAX_CARROS_ANIMACAO][ALTURA_PERSONAGEM][LARGURA_PERSONAGEM + 2];
    int animacao_bonus; // pra saber se tem bonus
} tDesenhos;


typedef struct {
    int x;
} tCarro;

typedef struct {
    char direcao;
    int velocidade;
    int num_carros;
    tCarro carros[MAX_CARROS];
} tPista;

typedef struct {
    int x_ini, y_ini;
    int x, y;
    int vidas;
    int pontos;
} tGalinha;

typedef struct {
    int idPista;
    int idCarro;
    int iteracao;
    int x;
    int y;
} tAtropelamentos;

typedef struct {
    int largura_mapa;
    int qtd_pistas;
    int animacao_bonus;
    int iteracao_atual;
    tPista pistas[MAX_PISTAS];
    tGalinha galinha;
    int movimentos_totais;
    int movimento_tras;
    int altura_maxima_chegada;
    int altura_maxima_atropelada;
    int altura_minima_atropelada;
    int heatmap[ALTURA_MAX][LARGURA_MAX];
    int marca_atropelamentos[ALTURA_MAX][LARGURA_MAX];
    int altura_mapa;
    tAtropelamentos atropelamentos[MAX_VIDAS * 10]; /* Um array grande o suficiente */
    int num_atropelamentos;
} tJogo;



//funcoes

tJogo leConfiguracoes(char diretorioDoCaso[]);
tDesenhos leDesenhos(char diretorioDoCaso[], int animacao_bonus);
tJogo calculaCoordenadasIniciais(tJogo jogo);
void ApresentaJogo(tJogo jogo, tDesenhos desenhos);
tGalinha MovimentaGalinha(tGalinha galinha, char mov, int largura_mapa);
tPista MovimentaCarrosNaPista(tPista pista, int largura);
int VerificaColisaoNaPista(tPista pista, tGalinha galinha);
void geraMapaInicial(tJogo jogo, tDesenhos desenhos, char diretorioDoCaso[]);
int VerificaColisao(tJogo jogo);
int VerificaVitoria(tJogo jogo);
void salvaResumo(tJogo jogo, int num_carro_colidido, char diretorio[]);
void geraRankingFinal(tJogo jogo, char diretorio[]);
void salvaEstatisticas(tJogo jogo, char diretorio[]);
tJogo inicializaHeatmap(tJogo jogo);
tJogo atualizaHeatmap(tJogo jogo);
tJogo marcaAtropelamentoHeatmap(tJogo jogo);
void salvaHeatmap(tJogo jogo, char diretorio[]);


//main

tJogo meuJogo;

int main(int argc, char *argv[]) {

    tDesenhos meusDesenhos;
    char diretorioDoCaso[1000];
    int i;
    int x, y;
    
    if (argc < 2) {
        printf("ERRO: Informe o diretorio com os arquivos de configuracao.\n");
        return 1;
    }


    strcpy(diretorioDoCaso, argv[1]);

    meuJogo = leConfiguracoes(diretorioDoCaso);
    meusDesenhos = leDesenhos(diretorioDoCaso, meuJogo.animacao_bonus);
    meuJogo = calculaCoordenadasIniciais(meuJogo);
    meuJogo = inicializaHeatmap(meuJogo);
    meuJogo.iteracao_atual=0;
    meuJogo.num_atropelamentos = 0;
    meuJogo.movimentos_totais = 0;
    meuJogo.movimento_tras = 0;
    meuJogo.altura_maxima_chegada = 0;
    meuJogo.altura_maxima_atropelada = -1; 
    meuJogo.altura_minima_atropelada = -1;
    meuJogo.galinha.pontos = 0;

    int fim_de_jogo = 0;

    while(!fim_de_jogo){

        ApresentaJogo(meuJogo, meusDesenhos);

        if (VerificaVitoria(meuJogo)) {
            fim_de_jogo = 1;
            printf("Parabens! Voce atravessou todas as pistas e venceu!\n");
            break;
        }

        // Verifica game over
        if (meuJogo.galinha.vidas <= 0) {
            fim_de_jogo = 1;
            printf("Voce perdeu todas as vidas! Fim de jogo.\n");
            break;
        }

        meuJogo = atualizaHeatmap(meuJogo);
        char comandos;
        int colisao;
        scanf(" %c", &comandos); 
        meuJogo.iteracao_atual++;

        if (comandos == 'w' || comandos == 's' || comandos == ' ') {
            meuJogo.movimentos_totais++;
            meuJogo.galinha = MovimentaGalinha(meuJogo.galinha, comandos, meuJogo.largura_mapa);
            if(comandos == 's'){
                meuJogo.movimento_tras++;
            }
        }
        int altura_atual = (meuJogo.galinha.y_ini - meuJogo.galinha.y) + 1;

        if (altura_atual > meuJogo.altura_maxima_chegada) {
            meuJogo.altura_maxima_chegada = altura_atual;
        }

        for (i = 0; i < meuJogo.qtd_pistas; i++) {
            meuJogo.pistas[i] = MovimentaCarrosNaPista(meuJogo.pistas[i], meuJogo.largura_mapa);
        }


        colisao = VerificaColisao(meuJogo);

        if (colisao) {
            meuJogo.galinha.pontos = 0;
            meuJogo = marcaAtropelamentoHeatmap(meuJogo);
            int altura_convertida = (meuJogo.galinha.y_ini - meuJogo.galinha.y) + 1;

            if (meuJogo.altura_maxima_atropelada == -1 || altura_convertida > meuJogo.altura_maxima_atropelada) {
                meuJogo.altura_maxima_atropelada = altura_convertida;
            }
            
            if (meuJogo.altura_minima_atropelada == -1 || altura_convertida < meuJogo.altura_minima_atropelada) {
                meuJogo.altura_minima_atropelada = altura_convertida;
            }


            meuJogo.galinha.vidas--;

            if (meuJogo.animacao_bonus == 1) {
                int pista_da_colisao_idx = (meuJogo.galinha.y - 1) / 3;
                if (meuJogo.pistas[pista_da_colisao_idx].velocidade > 1) {
                    meuJogo.pistas[pista_da_colisao_idx].velocidade--;
                }
            }
            
            meuJogo = atualizaHeatmap(meuJogo);
            
            int idx = meuJogo.num_atropelamentos;
            int pista_atual_idx = (meuJogo.galinha.y - 1) / 3;

            meuJogo.atropelamentos[idx].iteracao = meuJogo.iteracao_atual;
            meuJogo.atropelamentos[idx].idPista = pista_atual_idx + 1;
            meuJogo.atropelamentos[idx].idCarro = colisao;
            meuJogo.atropelamentos[idx].x = meuJogo.galinha.x;
            meuJogo.atropelamentos[idx].y = meuJogo.galinha.y;
            meuJogo.num_atropelamentos++;

            salvaResumo(meuJogo, colisao, diretorioDoCaso);

            meuJogo.galinha.x = meuJogo.galinha.x_ini;
            meuJogo.galinha.y = meuJogo.galinha.y_ini;
            
        }
        else {
            if (comandos == 'w') {
                meuJogo.galinha.pontos++;
                if (VerificaVitoria(meuJogo)) {
                    meuJogo.galinha.pontos += 10;
                }
            }
        }
    }
    FILE *arq_resumo;
    char caminho_resumo[1000];
    sprintf(caminho_resumo, "%s/saida/resumo.txt", diretorioDoCaso);
    
    
    arq_resumo = fopen(caminho_resumo, "a"); 
    if (arq_resumo) {
        fprintf(arq_resumo, "[%d] Fim de jogo.\n", meuJogo.iteracao_atual);
        fclose(arq_resumo);
    } else {
        printf("Erro ao abrir resumo.txt\n");
    }

    //atualiza as stats do jogo e faz o heatmap
    salvaEstatisticas(meuJogo, diretorioDoCaso);
    salvaHeatmap(meuJogo, diretorioDoCaso);
    geraRankingFinal(meuJogo, diretorioDoCaso);
    
    return 0;
}

// funcoes feitas 

tJogo leConfiguracoes(char diretorioDoCaso[]) {
    tJogo jogo;
    char caminhoConfig[1000];
    FILE* arq;
    char buffer[200]; //armazena o que tem em cada linha
    int i, c;
    jogo.iteracao_atual = 0;
    jogo.galinha.pontos = 0;
    int direcao_temp, vel;
    char d;
    int valores[20];

    sprintf(caminhoConfig, "%s/config_inicial.txt", diretorioDoCaso); // juntas os dois (nome e caminho)
    arq = fopen(caminhoConfig, "r");

    if (!arq) { 
        printf("ERRO (%s): Nao foi possivel abrir config_inicial.txt", caminhoConfig); 
        exit(1);
    }

    fscanf(arq, "%d\n", &jogo.animacao_bonus);
    fscanf(arq, "%d %d\n", &jogo.largura_mapa, &jogo.qtd_pistas);
    
    for (i = 0; i < jogo.qtd_pistas; i++) { //loop se repete pra cada pista
        fgets(buffer, 200, arq); //fgets le a linha toda e guarda no buffer
        if(strlen(buffer)<2){  //se nao tem nada entao:
            jogo.pistas[i].num_carros=0;
        }
        else if(buffer[0]=='G'){ // se a linha comeca com G de galinha
            sscanf(buffer, "G %d %d", &jogo.galinha.x_ini, &jogo.galinha.vidas);
            jogo.pistas[i].num_carros = 0;
        }
        else{ // le a direcao e o num de carros ate o max de carros
            sscanf(buffer, "%c %d %d %d %d %d %d %d %d %d %d %d %d", 
            &d, &valores[0], &valores[1], &valores[2], &valores[3], &valores[4],
            &valores[5], &valores[6], &valores[7], &valores[8], &valores[9],
            &valores[10], &valores[11]);

            jogo.pistas[i].direcao = d;
            jogo.pistas[i].velocidade = valores[0];
            jogo.pistas[i].num_carros = valores[1];

            //cada carro com seu valor especifico ate o num de carros
            for (c = 0; c < jogo.pistas[i].num_carros; c++) {
                jogo.pistas[i].carros[c].x = valores[2 + c];
            }
        }
    }

    fclose(arq);
    return jogo;
}



tGalinha MovimentaGalinha(tGalinha galinha, char mov, int lagura_mapa) {
    int alturaMaximaY = (meuJogo.qtd_pistas -1 ) * 3 - 2; 
    int margem_lateral = 1;
    int largura = lagura_mapa;

    if(mov == 'w' && galinha.y > 1) {
        galinha.y -= 3;
    }
    else if(mov == 's' && galinha.y < alturaMaximaY) {
        galinha.y += 3;
    }
    else if(mov == ' ' ){
        galinha.x = galinha.x;
    }

    return galinha;
}


tPista MovimentaCarrosNaPista(tPista pista, int largura) {
    int i;
    if(pista.direcao == 'D') {
        for(i = 0; i < pista.num_carros; i++) {
            pista.carros[i].x = pista.carros[i].x + pista.velocidade;
            if(pista.carros[i].x > largura) {
                pista.carros[i].x = (pista.carros[i].x - largura);
                if (pista.carros[i].x == 0){
                    pista.carros[i].x = 1;
                } 
            }
        }
    } else if(pista.direcao == 'E') {
        for(i = 0; i < pista.num_carros; i++) {
            pista.carros[i].x = pista.carros[i].x - pista.velocidade;
            if(pista.carros[i].x < 1) {
                pista.carros[i].x = largura + pista.carros[i].x;
            }
        }
    }
    return pista;
}


int VerificaColisaoNaPista(tPista pista, tGalinha galinha) {
    int i;
    for(i = 0; i < pista.num_carros; i++) {
       
        if(abs(pista.carros[i].x - galinha.x) <= 1) {  
            return i + 1; 
        }
    }
    return 0;
}
int VerificaColisao(tJogo jogo) {
    int pista_galinha = (jogo.galinha.y - 1) / 3;

    if (pista_galinha < 0 || pista_galinha >= jogo.qtd_pistas)
        return 0; // Fora das pistas

    return VerificaColisaoNaPista(jogo.pistas[pista_galinha], jogo.galinha);
}
int VerificaVitoria(tJogo jogo) {
    return (jogo.galinha.y == 1);
}

tDesenhos leDesenhos(char diretorioDoCaso[], int animacao_bonus) {
    tDesenhos desenho;
    char caminho[1000];
    FILE *arq;
    int i;

    desenho.animacao_bonus = animacao_bonus;

    sprintf(caminho, "%s/personagens.txt", diretorioDoCaso);
    arq = fopen(caminho, "r");

    if (!arq) {
        printf("Erro ao abrir personagens.txt\n");
        exit(1);
    }

    // Ler galinha (2 linhas)
    for (i = 0; i < ALTURA_PERSONAGEM; i++) {
        fgets(desenho.galinha[i], LARGURA_PERSONAGEM + 2, arq);
        desenho.galinha[i][LARGURA_PERSONAGEM] = '\0'; // Garantir terminação
    }

    // Ler carro padrão (2 linhas)
    for (i = 0; i < ALTURA_PERSONAGEM; i++) {
        fgets(desenho.carro[i], LARGURA_PERSONAGEM + 2, arq);
        desenho.carro[i][LARGURA_PERSONAGEM] = '\0';
    }

    // Se animacao_bonus == 1, ler os 4 carros extras
    if (animacao_bonus == 1) {
        for (int c = 0; c < MAX_CARROS_ANIMACAO; c++) {
            for (i = 0; i < ALTURA_PERSONAGEM; i++) {
                fgets(desenho.carros_bonus[c][i], LARGURA_PERSONAGEM + 2, arq);
                desenho.carros_bonus[c][i][LARGURA_PERSONAGEM] = '\0';
            }
        }
    }

    fclose(arq);
    return desenho;
}
tJogo calculaCoordenadasIniciais(tJogo jogo) {
    jogo.galinha.y_ini = (jogo.qtd_pistas - 1) * 3 - 1;
    jogo.galinha.y = jogo.galinha.y_ini;
    jogo.galinha.x = jogo.galinha.x_ini;
    return jogo;
}

/* --- FUNÇAO GERAR ARQUIVOS --- */
void geraMapaInicial(tJogo jogo, tDesenhos desenhos, char diretorioDoCaso[]){
    char mapa[MAX_ALTURA][MAX_LARGURA];
    int altura_mapa = (jogo.qtd_pistas - 1) * 3 + 2;
    int l, c, i, j, lin, col;
    char caminhoSaida[1000];
    FILE* arq;
    int linha_lateral;
    int carro_x, carro_y;
    int x_inicio_desenho;

    for(l = 0; l < altura_mapa; l++){
        for(c = 0; c < jogo.largura_mapa; c++){
            mapa[l][c] = ' ';
        }
    }
    /* desenha as linhas que separam as pistas */
    for (i = 0; i < jogo.qtd_pistas - 1; i++) {
        linha_lateral = (i * 3) + 2;
        for (j = 0; j < jogo.largura_mapa; j += 3) {
            mapa[linha_lateral][j] = '-';
            mapa[linha_lateral][j+1] = '-';
        }
    }

    /* desenha os carros */
    for (i = 0; i < jogo.qtd_pistas; i++) {
        for (c = 0; c < jogo.pistas[i].num_carros; c++) {
            carro_x = jogo.pistas[i].carros[c].x;
            carro_y = (i * 3) + 1; 
            x_inicio_desenho = carro_x -1;

            for (lin = 0; lin < ALTURA_PERSONAGEM; lin++) {
                for (col = 0; col < LARGURA_PERSONAGEM; col++) {
                    if ((carro_y + lin - 1) < altura_mapa && (x_inicio_desenho + col) < jogo.largura_mapa) {
                        mapa[carro_y + lin - 1][x_inicio_desenho + col] = desenhos.carro[lin][col];
                    }
                    
                }
            }
        }
    }

   // desenha galinha
   x_inicio_desenho = jogo.galinha.x - 1;
   for (lin = 0; lin < ALTURA_PERSONAGEM; lin++) {
       for (col = 0; col < LARGURA_PERSONAGEM; col++) {
           if ((jogo.galinha.y + lin - 1) < altura_mapa && (x_inicio_desenho + col) < jogo.largura_mapa) {
               mapa[jogo.galinha.y + lin - 1][x_inicio_desenho + col] = desenhos.galinha[lin][col];
           }
       }   
   }


    /* 5. Abre o arquivo de saída e escreve o mapa formatado */

    sprintf(caminhoSaida, "%s/saida/inicializacao.txt", diretorioDoCaso);
    arq = fopen(caminhoSaida, "w");
    
    fprintf(arq, "+");
    
    for(j = 0; j < jogo.largura_mapa; j++){
        fprintf(arq, "-");
    } 
    fprintf(arq, "+\n");

    for (i = 0; i < altura_mapa; i++) {
        fprintf(arq, "|");
        for (j = 0; j < jogo.largura_mapa; j++) {
            fprintf(arq, "%c", mapa[i][j]);
        }
        fprintf(arq, "|\n");
    }

    fprintf(arq, "+");
    for(j = 0; j < jogo.largura_mapa; j++){
        fprintf(arq, "-");
    } 
    fprintf(arq, "+\n");
    
    fprintf(arq, "A posicao central da galinha iniciara em (%d %d).\n", jogo.galinha.x_ini, jogo.galinha.y_ini);

    fclose(arq);
}
void salvaResumo(tJogo jogo, int num_carro_colidido, char diretorio[]) {
    FILE *arq;
    char caminho[1000];
    int pista_galinha = (jogo.galinha.y - 1) / 3;

    sprintf(caminho, "%s/saida/resumo.txt", diretorio);

    arq = fopen(caminho, "a");
    if (!arq) {
        printf("Erro ao abrir resumo.txt\n");
        return;
    }
    
    fprintf(arq, "[%d] Na pista %d o carro %d atropelou a galinha na posicao (%d, %d).\n",
            jogo.iteracao_atual, pista_galinha + 1, num_carro_colidido, jogo.galinha.x, jogo.galinha.y + 1);

}

void salvaEstatisticas(tJogo jogo, char diretorio[]) {
    FILE *arq;
    char caminho[1000];

    sprintf(caminho, "%s/saida/estatisticas.txt", diretorio);
    arq = fopen(caminho, "w");
    if (!arq) {
        printf("Erro ao criar estatisticas.txt\n");
        return;
    }

    fprintf(arq, "Numero total de movimentos: %d\n", jogo.movimentos_totais);
    fprintf(arq, "Altura maxima que a galinha chegou: %d\n", jogo.altura_maxima_chegada);

    if (jogo.altura_maxima_atropelada != -1)
        fprintf(arq, "Altura maxima que a galinha foi atropelada: %d\n", jogo.altura_maxima_atropelada);
    else
        fprintf(arq, "Altura maxima que a galinha foi atropelada: 0\n");

    if (jogo.altura_minima_atropelada != -1)
        fprintf(arq, "Altura minima que a galinha foi atropelada: %d\n", jogo.altura_minima_atropelada);
    else
        fprintf(arq, "Altura minima que a galinha foi atropelada: 0\n");

    fprintf(arq, "Numero de movimentos na direcao oposta: %d\n", jogo.movimento_tras);

    fclose(arq);
}
tJogo inicializaHeatmap(tJogo jogo) {
    int i, j;
    for (i = 0; i < ALTURA_MAX; i++) {
        for (j = 0; j < LARGURA_MAX; j++) {
            jogo.heatmap[i][j] = 0;
            jogo.marca_atropelamentos[i][j] = 0;
        }
    }
    jogo.altura_mapa = (jogo.qtd_pistas - 1) * 3 + 2;
    return jogo;
}

tJogo atualizaHeatmap(tJogo jogo) {
    int i, j;
    for (i = 0; i < 2; i++) { // galinha tem altura de 2
        int y = jogo.galinha.y + i;
        for (j = 0; j < 3; j++) { // largura de 3
            int x = jogo.galinha.x + j;
            if (y >= 0 && y < jogo.altura_mapa && x >= 0 && x < jogo.largura_mapa) {
                if (jogo.heatmap[y][x] < 99) {
                    jogo.heatmap[y][x]++;
                }
            }
        }
    }
    return jogo;
}
tJogo marcaAtropelamentoHeatmap(tJogo jogo) {
    int linha1 = jogo.galinha.y;
    int linha2 = jogo.galinha.y + 1;

    
    if (linha1 >= 0 && linha1 < jogo.altura_mapa) {
        jogo.marca_atropelamentos[linha1][0] = 1; 
    }
    if (linha2 >= 0 && linha2 < jogo.altura_mapa) {
        jogo.marca_atropelamentos[linha2][0] = 1;
    }
    return jogo;
}
void salvaHeatmap(tJogo jogo, char diretorio[]) {
    FILE *arq;
    char caminho[1000];
    int i, j;

    sprintf(caminho, "%s/saida/heatmap.txt", diretorio);
    arq = fopen(caminho, "w");
    if (!arq) {
        printf("Erro ao criar heatmap.txt\n");
        return;
    }

    for (i = 0; i < jogo.altura_mapa; i++) {
        
        if (jogo.marca_atropelamentos[i][0] == 1) {
            for (j = 0; j < jogo.largura_mapa; j++) {
                fprintf(arq, "  *"); 
            }
        } else {
            for (j = 0; j < jogo.largura_mapa; j++) {
                int valor = jogo.heatmap[i][j] > 99 ? 99 : jogo.heatmap[i][j];
                fprintf(arq, "%3d", valor); 
            }
        }
        fprintf(arq, "\n");
    }

    fclose(arq);
}
void ApresentaJogo(tJogo jogo, tDesenhos desenhos) {
    
    char mapa[MAX_ALTURA][MAX_LARGURA];
    int altura_mapa;
    int i, j, c, lin, col;
    int x_inicio_desenho;
    int id_desenho_carro;

    altura_mapa = (jogo.qtd_pistas - 1) * 3 + 2;

    //preenche a tela com espaco pra evitar erro na matriz
    for(i = 0; i < altura_mapa; i++) {
        for(j = 0; j < jogo.largura_mapa; j++) {
            mapa[i][j] = ' ';
        }
    }

    //desenha as linhas
    for (i = 0; i < jogo.qtd_pistas - 1; i++) {
        int linha_borda = (i * 3) + 2;
        for (j = 0; j < jogo.largura_mapa; j += 3) {
            mapa[linha_borda][j] = '-';
            mapa[linha_borda][j+1] = '-';
        }
    }

    //desenha os carros
    for (i = 0; i < jogo.qtd_pistas; i++) {
        for (c = 0; c < jogo.pistas[i].num_carros; c++) {
            int carro_x = jogo.pistas[i].carros[c].x;
            int carro_y = (i * 3) + 1; 
            x_inicio_desenho = carro_x - 1;

            
            id_desenho_carro = 0; 
            if (jogo.animacao_bonus == 1) {
                id_desenho_carro = jogo.iteracao_atual % MAX_DESENHOS_CARRO;
            }

            
            for (lin = 0; lin < ALTURA_PERSONAGEM; lin++) {
                for (col = 0; col < LARGURA_PERSONAGEM; col++) {
                    
                    if ((carro_y + lin - 1) < altura_mapa && (x_inicio_desenho + col) < jogo.largura_mapa && jogo.animacao_bonus==0) {
                        mapa[carro_y + lin - 1][x_inicio_desenho + col] = desenhos.carro[lin][col];
                    }
                    if ((carro_y + lin - 1) < altura_mapa && (x_inicio_desenho + col) < jogo.largura_mapa && jogo.animacao_bonus==1) {
                        mapa[carro_y + lin - 1][x_inicio_desenho + col] = desenhos.carros_bonus[id_desenho_carro][lin][col];
                    }
                    
                }
            }
        }
    }

    // desenha galinha
    x_inicio_desenho = jogo.galinha.x - 1;
    for (lin = 0; lin < ALTURA_PERSONAGEM; lin++) {
        for (col = 0; col < LARGURA_PERSONAGEM; col++) {
             
            if ((jogo.galinha.y + lin - 1) < altura_mapa && (x_inicio_desenho + col) < jogo.largura_mapa) {
                mapa[jogo.galinha.y + lin - 1][x_inicio_desenho + col] = desenhos.galinha[lin][col];
            }
        }   
    }
    
    // Imprime tudo na tela 
    printf("Pontos: %d | Vidas: %d | Iteracoes: %d\n", jogo.galinha.pontos, jogo.galinha.vidas, jogo.iteracao_atual);
    
    printf("+");
    for(j = 0; j < jogo.largura_mapa; j++) {
        printf("-");
    }
    printf("+\n");

    for (i = 0; i < altura_mapa; i++) {
        printf("|");
        for (j = 0; j < jogo.largura_mapa; j++) {
            printf("%c", mapa[i][j]);
        }
        printf("|\n");
    }

    printf("+");
    for(j = 0; j < jogo.largura_mapa; j++) {
        printf("-");
    }
    printf("+\n");
}
void geraRankingFinal(tJogo jogo, char diretorio[]) {
    int i, j;
    tAtropelamentos temp; //para a troca

    for (i = 0; i < jogo.num_atropelamentos - 1; i++) {
        for (j = 0; j < jogo.num_atropelamentos - i - 1; j++) {
            
            int precisaTrocar = 0; //flag

            //criterio idpista
            if (jogo.atropelamentos[j].idPista > jogo.atropelamentos[j+1].idPista) {
                precisaTrocar = 1;
            } 
            
            else if (jogo.atropelamentos[j].idPista == jogo.atropelamentos[j+1].idPista) {
                
                // criterio idcarro
                if (jogo.atropelamentos[j].idCarro > jogo.atropelamentos[j+1].idCarro) {
                    precisaTrocar = 1;
                }
                
                else if (jogo.atropelamentos[j].idCarro == jogo.atropelamentos[j+1].idCarro) {
                    
                    // criterio iteracao
                    if (jogo.atropelamentos[j].iteracao < jogo.atropelamentos[j+1].iteracao) {
                        precisaTrocar = 1;
                    }
                }
            }

            // se a flag foi ativada, troca dos elementos
            if (precisaTrocar) {
                temp = jogo.atropelamentos[j];
                jogo.atropelamentos[j] = jogo.atropelamentos[j+1];
                jogo.atropelamentos[j+1] = temp;
            }
        }
    }

    FILE *arq;
    char caminho[1000];
    sprintf(caminho, "%s/saida/ranking.txt", diretorio);

    arq = fopen(caminho, "w");
    if (!arq) {
        printf("Erro ao criar ranking.txt\n");
        return;
    }

    fprintf(arq, "id_pista,id_carro,iteracao\n"); 

    for (i = 0; i < jogo.num_atropelamentos; i++) {
        fprintf(arq, "%d,%d,%d\n", 
                jogo.atropelamentos[i].idPista, 
                jogo.atropelamentos[i].idCarro, 
                jogo.atropelamentos[i].iteracao);
    }

    fclose(arq);
}