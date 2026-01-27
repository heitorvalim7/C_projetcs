#include "estabelecimento.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Estabelecimento{
    Vector *produtos;
};

/**
 * @brief Função para criar um novo estabelecimento.
 * @return Um ponteiro para o estabelecimento recém-criado. Se houver erro na alocação, o programa é encerrado.
 */
tEstabelecimento *CriaEstabelecimento(){
    tEstabelecimento *e = (tEstabelecimento*)calloc(1, sizeof(tEstabelecimento));
    e->produtos = VectorConstruct();

    if(!e){
        return NULL;
    }

    return e;
}

/**
 * @brief Função para destruir um estabelecimento.
 * @param estabelecimento Um ponteiro para o estabelecimento a ser destruído.
 */
void DestroiEstabelecimento(tEstabelecimento *estabelecimento){
    VectorDestroy(estabelecimento->produtos, DestroiProduto);
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
    int qtd;
    fread(&qtd, sizeof(int), 1, f);
    for(int i = 0; i<qtd; i++){
        tProduto *p = LeProduto(f);
        AdicionaProdutoEstabelecimento(estabelecimento, p);
    }

    fclose(f);
}

/**
 * @brief Função para imprimir produtos que estão faltando em um estabelecimento no seguinte formato: Codigo;Nome;Preco
 * @param estabelecimento Um ponteiro para o estabelecimento.
 */
void ImprimeProdutosEmFaltaEstabelecimento(tEstabelecimento *estabelecimento){
    int flag = 1;
    printf("Produtos em falta:\n");
    printf("Codigo;Nome;Preco\n");
    for(int i = 0; i<VectorSize(estabelecimento->produtos); i++){
        if(!TemEstoqueProduto((tProduto*)VectorGet(estabelecimento->produtos, i))){
            flag = 0;
            ImprimeProduto((tProduto*)VectorGet(estabelecimento->produtos, i));
        }
    }
    if(flag){
        printf("Nao ha produtos em falta!\n");
    }
}
