#include "agencia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Agencia{
    int numero;
    char nome[100];
    Vector *contas;
};

/**
 * @brief Função para criar uma nova agência bancária.
 * @return Um ponteiro para a nova agência bancária criada. Se a memória não puder ser alocada, a função imprime uma mensagem de erro e termina o programa.
 */
tAgencia *CriaAgencia(){
    tAgencia *a = (tAgencia*)calloc(1, sizeof(tAgencia));
    if(!a)
        return NULL;

    a->contas = VectorConstruct();
    if(!a->contas){
        free(a);
        return NULL;
    }
    return a;
}

/**
 * @brief Função para destruir uma agência bancária.
 * @param agencia A agência bancária a ser destruída.
 */
void DestroiAgencia(DataType agencia){
    tAgencia *a = (tAgencia*)agencia;
    VectorDestroy(a->contas, DestroiConta);
    free(a);
}

/**
 * @brief Função para ler uma agência bancária no formato "numero;nome".
 * @param agencia A agência bancária a ser lida.
 */
void LeAgencia(tAgencia *agencia){
    scanf("%d;%99[^\n]", &agencia->numero, agencia->nome);
}

/**
 * @brief Função para adicionar uma conta bancária a uma agência bancária.
 * @param agencia A agência bancária.
 * @param conta A conta bancária a ser adicionada.
 */
void AdicionaConta(tAgencia *agencia, tConta *conta){
    VectorPushBack(agencia->contas, (DataType)conta);
}

/**
 * @brief Função para comparar um número de agência bancária com uma agência bancária.
 * @param numAgencia O número da agência bancária.
 * @param agencia2 A agência bancária a ser comparada.
 * @return 1 se os números forem iguais, 0 caso contrário.
 */
int ComparaAgencia(int numAgencia, tAgencia *agencia2){
    return numAgencia == agencia2->numero;
}

/**
 * @brief Função para obter o saldo médio das contas de uma agência bancária.
 * @param agencia A agência bancária.
 * @return O saldo médio das contas da agência.
 */
float GetSaldoMedioAgencia (tAgencia *agencia){
    int tamanho = VectorSize(agencia->contas);
    if(tamanho == 0){
        return 0.0f;
    }
    float soma = 0.0f;
    for(int i = 0; i<tamanho; i++){
        tConta *conta = (tConta*)VectorGet(agencia->contas, i);
        soma += GetSaldoConta(conta);
    }
    return soma/tamanho;
}

/**
 * @brief Função para imprimir os dados de uma agência bancária (nome, número, número de contas cadastradas e saldo médio).
 * @param agencia A agência bancária.
 */
void ImprimeDadosAgencia(tAgencia *agencia){
    printf("        Nome: %s\n", agencia->nome);
    printf("        Numero: %d\n", agencia->numero);
    printf("        Numero de contas cadastradas: %d\n", VectorSize(agencia->contas));
    printf("        Saldo médio: R$%.2f\n", GetSaldoMedioAgencia(agencia));
    printf("\n");
}