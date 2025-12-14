#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "locadora.h"



struct Locadora{
    tFilme **f;
    int numFilmes;
    int lucro;
};

/**
 * @brief Cria uma nova instância de tLocadora e inicializa filme como NULL, numFilmes como 0 e lucro como 0.
 * 
 * @return tLocadora* Ponteiro para a nova instância de tLocadora criada ou encerra o programa caso não haja memória suficiente.
 */
tLocadora* CriarLocadora (){
    tLocadora *l;
    l = (tLocadora*)calloc(1, sizeof(struct Locadora));
    l->f = NULL;
    l->lucro = 0;
    l->numFilmes = 0;
    return l;
}

/**
 * @brief Destrói uma instância de tLocadora.
 * 
 * @param locadora Ponteiro para a instância de tLocadora a ser destruída.
 */
void DestruirLocadora (tLocadora* locadora){
    for(int i = 0; i < locadora->numFilmes; i++){
        DestruirFilme(locadora->f[i]);
    }
    free(locadora->f);
    free(locadora);
}

/**
 * @brief Verifica se um filme está cadastrado na locadora.
 * 
 * @param locadora Ponteiro para a instância de tLocadora a ser verificada.
 * @param codigo Código do filme a ser verificado.
 * @return int 1 se o filme está cadastrado, 0 caso contrário.
 */
int VerificarFilmeCadastrado (tLocadora* locadora, int codigo){
    for( int i = 0; i<locadora->numFilmes; i++){
        if(EhMesmoCodigoFilme(locadora->f[i], codigo)){
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Cadastra um novo filme na locadora caso ele não esteja cadastrado.
 * 
 * @param locadora Ponteiro para a instância de tLocadora a ser atualizada.
 * @param filme Ponteiro para o filme a ser cadastrado.
 */
void CadastrarFilmeLocadora (tLocadora *locadora, tFilme *filme){
    locadora->f = realloc(locadora->f, (locadora->numFilmes + 1) * sizeof(tFilme*));
    locadora->f[locadora->numFilmes] = filme;
    locadora->numFilmes++;
    printf("Filme cadastrado %d - ", ObterCodigoFilme(filme));
    ImprimirNomeFilme(filme);
    printf("\n");
}

/**
 * @brief Lê os dados de cadastro de um filme e o cadastra na locadora.
 * 
 * @param Locadora Ponteiro para a instância de tLocadora a ser atualizada.
 */
void LerCadastroLocadora (tLocadora* Locadora){
    char c;

    while(1){

       c = getchar();

        // Ignora quebras de linha
        while (c == '\n' || c == ' ') {
            c = getchar();
        }

        // Se for #, terminou o cadastro
        if (c == '#') {
            break;
        }

        // Devolve o caractere para o buffer
        ungetc(c, stdin);

        tFilme *f;
        f = CriarFilme();
        int codigo;
        scanf("%d,", &codigo);
        LeFilme(f, codigo);
        CadastrarFilmeLocadora(Locadora, f);
       
    }
    
}

/**
 * @brief Aluga um ou mais filmes da locadora.
 * 
 * @param locadora Ponteiro para a instância de tLocadora a ser atualizada.
 * @param codigos Vetor contendo os códigos dos filmes a serem alugados.
 * @param quantidadeCodigos Número de códigos de filmes a serem alugados.
 */
void AlugarFilmesLocadora (tLocadora* locadora, int* codigos, int quantidadeCodigos){
    int total = 0;
    int custo = 0;
    for(int i = 0; i<locadora->numFilmes; i++){
        for(int j = 0; j<quantidadeCodigos; j++){
            if(EhMesmoCodigoFilme(locadora->f[i], codigos[i]) && ObterQtdEstoqueFilme(locadora->f[i])>0){
                AlugarFilme(locadora->f[i]);
                total++;
                custo += ObterValorFilme(locadora->f[i]);
            }
        }
    }
    free(codigos);
    printf("Total de filmes alugados: %d com custo de R$%d\n", total, custo);
}

/**
 * @brief Lê o aluguel de um conjunto de filmes a partir da entrada padrão e os aluga na locadora.
 * 
 * @param locadora Ponteiro para a instância de tLocadora a ser atualizada.
 */
void LerAluguelLocadora (tLocadora* locadora){
    int *codigos = NULL;
    int qtdcod = 0;
    int codigo = 0;
    int lendoNumero = 0;
    char c;

    while ((c = getchar()) != EOF){
        // Fim da lista
        if (c == '#'){
            break;
        }

        // Ignora separadores
        if (c == ' ' || c == '\n'){
            if (lendoNumero){
                // terminou um número
                codigos = realloc(codigos, (qtdcod + 1) * sizeof(int));
                codigos[qtdcod++] = codigo;

                codigo = 0;
                lendoNumero = 0;
            }
            continue;
        }

        // Se for dígito
        if (c >= '0' && c <= '9'){
            lendoNumero = 1;
            codigo = codigo * 10 + (c - '0');
        }
    }

    // Caso o último número venha antes do '#'
    if (lendoNumero){
        codigos = realloc(codigos, (qtdcod + 1) * sizeof(int));
        codigos[qtdcod++] = codigo;
    }

    AlugarFilmesLocadora(locadora, codigos, qtdcod);
}


/**
 * @brief Devolve um ou mais filmes alugados da locadora.
 * 
 * @param locadora Ponteiro para a instância de tLocadora a ser atualizada.
 * @param codigos Vetor contendo os códigos dos filmes a serem devolvidos.
 * @param quantidadeCodigos Número de códigos de filmes a serem devolvidos.
 */
void DevolverFilmesLocadora (tLocadora* locadora, int* codigos, int quantidadeCodigos){
    for(int i = 0; i<locadora->numFilmes; i++){
        for(int j = 0; j<quantidadeCodigos; j++){
            if(EhMesmoCodigoFilme(locadora->f[i], codigos[i]) && ObterQtdAlugadaFilme(locadora->f[i])>0){
                DevolverFilme(locadora->f[i]);
                printf("Filme %d - ", ObterCodigoFilme(locadora->f[i]));
                ImprimirNomeFilme(locadora->f[i]);
                printf(" Devolvido!\n");
            }
        }
    }
}    

/**
 * @brief Lê os dados de devolução de um ou mais filmes e os devolve na locadora.
 * 
 * @param locadora Ponteiro para a instância de tLocadora a ser atualizada.
 */
void LerDevolucaoLocadora (tLocadora* locadora){
    int *codigos = NULL;
    char c;
    int codigo;
    int qtdcod = 0;
    codigos = (int*) calloc (1, sizeof(int));
    while(1){
        scanf("%d", &codigo);
        codigos = realloc(codigos, (qtdcod + 1) * sizeof(int));
        codigos[qtdcod] = codigo;
        qtdcod++;

        c = getchar();  // lê o separador
        if (c == '#') {
            break;
        }
    }
    DevolverFilmesLocadora(locadora, codigos, qtdcod);
    free(codigos);
    
}

/**
 * @brief Ordena os filmes cadastrados na locadora por ordem alfabética.
 * 
 * @param locadora Ponteiro para a instância de tLocadora a ser atualizada.
 */
void OrdenarFilmesLocadora (tLocadora* locadora){
    for(int i = 0; i<locadora->numFilmes-1; i++){
        for(int j = i+1; j<locadora->numFilmes; j++){
            if(CompararNomesFilmes(locadora->f[i], locadora->f[j])>0){
                tFilme *aux = locadora->f[i];
                locadora->f[i]= locadora->f[j];
                locadora->f[j] = aux;
            }
        }
    }
}

/**
 * @brief Consulta o estoque de filmes da locadora.
 * 
 * @param locadora Ponteiro para a instância de tLocadora a ser consultada.
 */
void ConsultarEstoqueLocadora (tLocadora* locadora){
    printf("~ESTOQUE~\n");
    for(int i = 0; i<locadora->numFilmes; i++){
        printf("%d - ", ObterCodigoFilme(locadora->f[i]));
        ImprimirNomeFilme(locadora->f[i]);
        printf(" Fitas em estoque: %d\n", ObterQtdEstoqueFilme(locadora->f[i]));
    }
}

/**
 * @brief Consulta o lucro da locadora.
 * 
 * @param locadora Ponteiro para a instância de tLocadora a ser consultada.
 */
void ConsultarLucroLocadora (tLocadora* locadora){
    for(int i = 0; i<locadora->numFilmes; i++){
        locadora->lucro += ObterValorFilme(locadora->f[i]); 
    }
    
}