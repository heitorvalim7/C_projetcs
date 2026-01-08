#include "pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

typedef struct Pessoa {
    char *nome;
    char *cpf;
    char *telefone;
    char *genero;
    Data *nascimento;
} Pessoa;

/**
 * @brief Cria uma Pessoa com os dados fornecidos. Retorna NULL se os dados forem inválidos.
 */
Pessoa *criaPessoa( char *nome,  char *cpf,  char *telefone, char *genero, Data *nascimento){
    if (!nome || !cpf || !telefone || !genero || !nascimento) {
        return NULL;
    }

    Pessoa *p = (Pessoa *)malloc(sizeof(Pessoa));
    if (!p) return NULL;

    strcpy(p->nome = (char *)malloc(strlen(nome) + 1), nome);
    strcpy(p->cpf = (char *)malloc(strlen(cpf) + 1), cpf);
    strcpy(p->telefone = (char *)malloc(strlen(telefone) + 1), telefone);
    strcpy(p->genero = (char *)malloc(strlen(genero) + 1), genero);
    p->nascimento = nascimento;
    if (!p->nascimento) {
        free(p->nome);
        free(p->cpf);
        free(p->telefone);
        free(p->genero);
        free(p);
        return NULL;
    }

    return p;
}

/**
 * @brief Lê uma Pessoa da entrada padrão (formatos conforme especificação do trabalho).
 *        Deve ler: nome, cpf, telefone, genero (char), e a data de nascimento em três inteiros.
 */
Pessoa *lePessoa(){
    char nome[100], cpf[15], telefone[15];
    char genero[100];
    Data *nascimento;

    if (scanf(" %[^\n]", nome) != 1) return NULL;
    if (scanf(" %[^\n]", cpf) != 1) return NULL;
    nascimento = leData();
    if (!nascimento) return NULL;
    if (scanf(" %[^\n]", telefone) != 1) return NULL;
    if (scanf(" %[^\n]", genero) != 1) return NULL;
    return criaPessoa(nome, cpf, telefone, genero, nascimento);
}

/** Funções compatíveis com callbacks genéricos */
void imprimePessoa(void *dado){
    Pessoa *p = (Pessoa *)dado;
    if (p) {
        printf("- Nome: %s\n", p->nome);
        printf("- CPF: %s\n", p->cpf);
        printf("- Data de Nascimento: ");
        imprimeData(p->nascimento);
        printf("- Telefone: %s\n", p->telefone);
        printf("- Genero: %s\n", p->genero);
    }
}
void desalocaPessoa(void *dado){
    Pessoa *p = (Pessoa *)dado;
    if (p) {
        free(p->nome);
        free(p->cpf);
        free(p->telefone);
        free(p->genero);
        desalocaData(p->nascimento);
        free(p);
    }
}
int comparaPessoa( void *a,  void *b){
    Pessoa *p1 = (Pessoa *)a;
    Pessoa *p2 = (Pessoa *)b;
    return strcmp(p1->cpf, p2->cpf);    
} /* por CPF */

/** Getters */
char *getNomePessoa(Pessoa *p){
    return p->nome;
}
char *getCPFPessoa(Pessoa *p){
    return p->cpf;
}       
char *getTelefonePessoa(Pessoa *p){
    return p->telefone;
}
char *getGeneroPessoa(Pessoa *p){
    return p->genero;
}
Data *getDataNascimentoPessoa(Pessoa *p){
    return p->nascimento;
}

