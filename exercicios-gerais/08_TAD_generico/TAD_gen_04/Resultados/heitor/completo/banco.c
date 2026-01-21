#include "banco.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Banco{
    char nome[100];
    Vector *agencias;
};

/**
 * @brief Função para criar um novo banco.
 * @return Um ponteiro para o novo banco criado. Se a memória não puder ser alocada, a função imprime uma mensagem de erro e termina o programa.
 */
tBanco *CriaBanco(){
    tBanco *b = (tBanco*)calloc(1, sizeof(tBanco));
    if(!b){
        return NULL;
    }
    b->agencias = VectorConstruct();
    if(!b->agencias){
        free(b);
        return NULL;
    }
    return b;
}

/**
 * @brief Função para destruir um banco.
 * @param banco O banco a ser destruído.
 */
void DestroiBanco(tBanco *banco){
    VectorDestroy(banco->agencias, DestroiAgencia);
    free(banco);
}

/**
 * @brief Função para ler o nome de um banco.
 * @param banco O banco a ser lido.
 */
void LeBanco(tBanco *banco){
    scanf("%99[^\n]", banco->nome);
}

/**
 * @brief Função para adicionar uma agência a um banco.
 * @param banco O banco.
 * @param agencia A agência a ser adicionada.
 */
void AdicionaAgencia(tBanco *banco, tAgencia *agencia){
    VectorPushBack(banco->agencias, (DataType)agencia);
}

/**
 * @brief Função para inserir uma conta em uma agência pertencente ao banco.
 * @param banco O banco.
 * @param numAgencia O número da agência.
 * @param cliente A conta a ser inserida.
 * @pre A agência deve pertencer ao banco.
*/
void InsereContaBanco(tBanco *banco, int numAgencia, tConta *cliente){
    int encontrado = 0;
    for(int i = 0; i<VectorSize(banco->agencias); i++){
        tAgencia *a = (tAgencia*)VectorGet(banco->agencias, i);
        if(ComparaAgencia(numAgencia, a)){
            AdicionaConta(a, cliente);
            encontrado = 1;
            break;
        }   
    }
    if(!encontrado){
        return;
    }
}

/**
 * @brief Função para imprimir o relatório de um banco, com o nome do banco e a lista de agências.
 * @param banco O banco.
 */
void ImprimeRelatorioBanco(tBanco *banco){
    printf("%s\n", banco->nome);
    printf("Lista de agencias:\n");
    for(int i = 0; i<VectorSize(banco->agencias); i++){
        tAgencia *a = (tAgencia*)VectorGet(banco->agencias, i);
        ImprimeDadosAgencia(a);
    }
}