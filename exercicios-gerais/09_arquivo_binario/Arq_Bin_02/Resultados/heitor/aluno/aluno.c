#include "aluno.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mantenha apenas UMA definição da struct
struct Aluno {
    char nome[101];
    char data[12];
    char curso[101];
    int periodo;
    float cra;
};

tAluno* CriarAluno(char* nome, char* dataNascimento, char* curso, int periodo, float coeficienteRendimento) {
    tAluno *a = (tAluno*)calloc(1, sizeof(tAluno));
    if (a == NULL) exit(1);
    
    // Agora com <string.h> incluído, strcpy funcionará
    if (nome) strcpy(a->nome, nome);
    if (dataNascimento) strcpy(a->data, dataNascimento);
    if (curso) strcpy(a->curso, curso);
    
    a->cra = coeficienteRendimento;
    a->periodo = periodo; 
    return a;
}

void DestruirAluno(tAluno* aluno) {
    free(aluno); // Libera a memória alocada [cite: 18, 130]
}

tAluno *LeAluno(FILE *arquivo_binario) {
    char nome[101], data[12], curso[51];
    float periodo, cra;

    // Em binário de tamanho fixo, lemos o bloco direto [cite: 58]
    // 1. Lê os 100 bytes do nome 
    if (fread(nome, sizeof(char), 100, arquivo_binario) != 100) return NULL;
    nome[100] = '\0'; 

    // 2. Lê os 11 bytes da data 
    fread(data, sizeof(char), 11, arquivo_binario);
    data[11] = '\0';

    // 3. Lê os 50 bytes do curso 
    fread(curso, sizeof(char), 50, arquivo_binario);
    curso[50] = '\0';

    // 4. Lê os dois floats de 4 bytes [cite: 308, 309]
    fread(&periodo, sizeof(float), 1, arquivo_binario);
    fread(&cra, sizeof(float), 1, arquivo_binario);

    // Adapte o CriarAluno para aceitar o periodo como float
    return CriarAluno(nome, data, curso, (int)periodo, cra);
}
float GetCoeficienteRendimentoAluno(tAluno* aluno){
    return aluno->cra;
}
