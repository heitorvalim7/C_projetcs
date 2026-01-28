#include "estabelecimento.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

struct Estabelecimento{
    Vector *produtos;
    int qtd;
};

/**
 * @brief Função para criar um novo estabelecimento.
 * @return Um ponteiro para o estabelecimento recém-criado. Se houver erro na alocação, o programa é encerrado.
 */
tEstabelecimento *CriaEstabelecimento(){
    tEstabelecimento *e = (tEstabelecimento*)calloc(1, sizeof(tEstabelecimento));
    e->produtos = VectorConstruct();

    return e;
}

/**
 * @brief Função para destruir um estabelecimento.
 * @param estabelecimento Um ponteiro para o estabelecimento a ser destruído.
 */
void DestroiEstabelecimento(tEstabelecimento *estabelecimento){
    VectorDestroy(estabelecimento->produtos, (void (*)(void *))DestroiProduto);
    free(estabelecimento);
}

/**
 * @brief Função para adicionar um produto a um estabelecimento.
 * @param estabelecimento Um ponteiro para o estabelecimento.
 * @param produto Um ponteiro para o produto a ser adicionado.
 */
void AdicionaProdutoEstabelecimento(tEstabelecimento *estabelecimento, tProduto *produto){
    VectorPushBack(estabelecimento->produtos, produto);
}

/**
 * @brief Função para ler um estabelecimento de um arquivo binário.
 * Inicialmente, deverá ser lido o nome do arquivo binário pela entrada padrão.
 * O arquivo binário deverá ser composto por um inteiro que representa a quantidade de produtos no estabelecimento, seguido pelos produtos.
 * @param estabelecimento Um ponteiro para o estabelecimento a ser lido.
 */
void LeEstabelecimento(tEstabelecimento *estabelecimento){
    char arquivo[20];
    scanf("%s\n", arquivo);
    FILE *f = fopen(arquivo, "rb");
    fread(&estabelecimento->qtd, sizeof(int), 1, f);
    for(int i = 0; i<estabelecimento->qtd; i++){
        tProduto *p = LeProduto(f);
        AdicionaProdutoEstabelecimento(estabelecimento, p);
    }

    fclose(f);
}

/**
 * @brief Função para obter o valor total de produtos vendidos em um estabelecimento.
 * @param estabelecimento Um ponteiro para o estabelecimento.
 * @return O valor total de produtos vendidos.
*/
float GetValorTotalVendidoEstabelecimento(tEstabelecimento *estabelecimento){
    float valor = 0;

    for(int i = 0; i<estabelecimento->qtd; i++){
        valor += GetPrecoProduto((tProduto*)VectorGet(estabelecimento->produtos, i)) * GetQuantidadeVendidaProduto((tProduto*)VectorGet(estabelecimento->produtos, i));
    }

    return valor;
}

/**
 * @brief Função para imprimir na tela um relatório de um estabelecimento, cotendo o valor total vendido e a porcentagem de cada produto relativo ao total vendido.
 * Formato: Codigo;Nome;Preco;Quantidade vendida
 * @param estabelecimento Um ponteiro para o estabelecimento.
*/
void ImprimeRelatorioEstabelecimento(tEstabelecimento *estabelecimento){
    float valor =  GetValorTotalVendidoEstabelecimento(estabelecimento);
    printf("Valor total vendido: R$ %.2f\n", valor);
    printf("Produtos vendidos:\n");
    printf("Codigo;Nome;Preco;Quantidade vendida;Porcentagem\n");
    for(int i = 0; i<estabelecimento->qtd; i++){
        ImprimeProduto((tProduto*)VectorGet(estabelecimento->produtos, i));
        float valorVendidoProduto = GetPrecoProduto((tProduto*)VectorGet(estabelecimento->produtos, i)) * GetQuantidadeVendidaProduto((tProduto*)VectorGet(estabelecimento->produtos, i));
        float porcentagem = (valorVendidoProduto / valor) * 100;
        printf(";%.2f%%\n", porcentagem);
    }
}