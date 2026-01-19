#include "tripulante.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"

typedef struct Tripulante {
    Pessoa *pessoa;
    char *cargo;
    int horasTrabalhadas;
    float salario;
} Tripulante;

/**
 * @brief Cria um novo tripulante com a `Pessoa` associada, cargo, horas trabalhadas e salário.
 * @param pessoa Ponteiro para `Pessoa` (a função faz cópia interna)
 * @param cargo Cargo/posição do tripulante
 * @param horasTrabalhadas Horas trabalhadas (inteiro)
 * @param salario Salário (float)
 * @return Ponteiro para o Tripulante criado
 */
Tripulante *criaTripulante(Pessoa *pessoa, char *cargo, int horasTrabalhadas, float salario){
    if (!pessoa || !cargo || horasTrabalhadas < 0 || salario < 0) {
        return NULL;
    }

    Tripulante *t = (Tripulante *)malloc(sizeof(Tripulante));
    if (!t) return NULL;

    t->pessoa = pessoa; // Assume ownership of the Pessoa pointer
    strcpy(t->cargo = (char *)malloc(strlen(cargo) + 1), cargo);
    t->horasTrabalhadas = horasTrabalhadas;
    t->salario = salario;

    return t;
}

/**
 * @brief Lê um tripulante a partir da entrada (lê os campos de Pessoa, depois cargo, horas e salário)
 * @return Ponteiro para o Tripulante criado
 */
Tripulante *leTripulante(){
    Pessoa *pessoa = lePessoa();
    if (!pessoa) return NULL;

    char cargo[100];
    int horasTrabalhadas;
    float salario;

    if (scanf(" %[^\n]", cargo) != 1) {
        desalocaPessoa(pessoa);
        return NULL;
    }
    if (scanf(" %d", &horasTrabalhadas) != 1) {
        desalocaPessoa(pessoa);
        return NULL;
    }
    if (scanf("%f", &salario) != 1) {
        desalocaPessoa(pessoa);
        return NULL;
    }

    Tripulante *t = criaTripulante(pessoa, cargo, horasTrabalhadas, salario);
    return t;
}

/** Funções compatíveis com callbacks genéricos */
void imprimeTripulante(void *dado){
    Tripulante *t = (Tripulante *)dado;
    if (t) {
        imprimePessoa(t->pessoa);
        printf("- Cargo: %s\n", t->cargo);
        printf("- Horas Trabalhadas: %d\n", t->horasTrabalhadas);
        printf("- Salario: %.2f\n", t->salario);
        printf("======================\n");
    }
}
void desalocaTripulante(void *dado){
    Tripulante *t = (Tripulante *)dado;
    if (t) {
        desalocaPessoa(t->pessoa);
        free(t->cargo);
        free(t);
    }
}
int comparaTripulante(const void *a, const void *b){
    Tripulante *t1 = *(Tripulante **)a;
    Tripulante *t2 = *(Tripulante **)b;
    return getHorasTripulante(t2) - getHorasTripulante(t1);
} 

int verificaCPFTripulante(void *dado, void *chave) {
    if (!dado || !chave) return 0;
    Tripulante *t = (Tripulante *)dado;
    return strcmp(getCPFTripulante(t), (char *)chave) == 0;
}
/** Getters */
Pessoa *getPessoaTripulante(Tripulante *t){
    return t ? t->pessoa : NULL;
}
char *getCargoTripulante(Tripulante *t){
    return t ? t->cargo : NULL;
}
int getHorasTripulante(Tripulante *t){
    return t ? t->horasTrabalhadas : -1;
}
float getSalarioTripulante(Tripulante *t){
    return t ? t->salario : -1;
}   
size_t getTamanhoTripulante(){
    return sizeof(Tripulante);
}
char *getCPFTripulante(Tripulante *t){
    return getCPFPessoa(t->pessoa);
}
char *getNomeTripulante(Tripulante *t){
    return getNomePessoa(t->pessoa);
}
Data *getDataNascimentoTripulante(Tripulante *t){
    return getDataNascimentoPessoa(t->pessoa);
}
void tripulanteImprimeRankingPorHoras(Tripulante **tripulantes, int count){
    if (!tripulantes || count <= 0) return;

    // Criar um array temporário para ordenar
    Tripulante **tempArray = (Tripulante **)malloc(count * sizeof(Tripulante *));
    if (!tempArray) return;

    for (int i = 0; i < count; i++) {
        tempArray[i] = tripulantes[i];
    }

    // Ordenar por horas trabalhadas 
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (getHorasTripulante(tempArray[i]) < getHorasTripulante(tempArray[j])) {
                Tripulante *temp = tempArray[i];
                tempArray[i] = tempArray[j];
                tempArray[j] = temp;
            }
        }
    }

    // Imprimir o ranking
    
    printf("================================\n");
    printf("===== Ranking Tripulantes =====\n");
    printf("================================\n");
    for (int i = 0; i < count; i++) {
        imprimeTripulante(tempArray[i]);
    }
    printf("================================\n");

    free(tempArray);
}