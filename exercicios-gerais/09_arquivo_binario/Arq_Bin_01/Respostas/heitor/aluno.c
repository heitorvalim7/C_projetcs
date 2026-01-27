#include "aluno.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno{
    char nome[101];
    char data[100];
    char curso[100];
    char periodo[100];
    int conclusao;
    float cra;
};

Aluno** CriaVetorAlunos(int numeroAlunos){
    Aluno **as = (Aluno**)calloc(numeroAlunos, sizeof(Aluno*));
    return as;
}

Aluno* CriaAluno(char *nome, char *dtNasc, char *cursoUfes, char* periodoIngresso, int percConclusao, float CRA){
    Aluno *a = (Aluno*)calloc(1, sizeof(Aluno));
    a->conclusao= percConclusao;
    a->cra=CRA;
    strcpy(a->curso, cursoUfes);
    strcpy(a->data, dtNasc);
    strcpy(a->nome, nome);
    strcpy(a->periodo, periodoIngresso);

    return a;
}

void LeAlunos(Aluno** vetorAlunos, int numeroAlunos){
    char nome[101];
    char data[100];
    char curso[100];
    char periodo[100];
    int conclusao;
    float cra;
    for(int i = 0; i<numeroAlunos; i++){
        scanf(" %[^\n]", nome);
        scanf(" %[^\n]", data);
        scanf(" %[^\n]", curso);
        scanf(" %[^\n]", periodo);
        scanf("%d", &conclusao);
        scanf("%f", &cra);
        vetorAlunos[i] = CriaAluno(nome, data, curso, periodo, conclusao, cra);
    }
}

void LiberaAlunos(Aluno** alunos, int numeroAlunos){
    for(int i = 0; i<numeroAlunos; i++){
        free(alunos[i]);
    }
    free(alunos);
}

void SalvaAlunosBinario(Aluno **alunos, char *fileName, int numeroAlunos) {
    FILE *arq = fopen(fileName, "wb"); // [cite: 114, 197]
    if (arq == NULL) return;

    size_t bytesTotais = 0;
    for (int i = 0; i < numeroAlunos; i++) {
        // 1. NOME: tam (4 bytes) + string (variável)
        int tamNome = strlen(alunos[i]->nome);
        bytesTotais += fwrite(&tamNome, sizeof(int), 1, arq) * sizeof(int); // [cite: 17, 188]
        bytesTotais += fwrite(alunos[i]->nome, sizeof(char), tamNome, arq) * sizeof(char); // [cite: 13, 14]

        // 2. DATA: tam (4 bytes) + string (variável)
        int tamData = strlen(alunos[i]->data);
        bytesTotais += fwrite(&tamData, sizeof(int), 1, arq) * sizeof(int);
        bytesTotais += fwrite(alunos[i]->data, sizeof(char), tamData, arq) * sizeof(char);

        // 3. CURSO: tam (4 bytes) + string (variável)
        int tamCurso = strlen(alunos[i]->curso);
        bytesTotais += fwrite(&tamCurso, sizeof(int), 1, arq) * sizeof(int); // Verifique se esta linha soma bytesTotais
        bytesTotais += fwrite(alunos[i]->curso, sizeof(char), tamCurso, arq) * sizeof(char);

        // 4. PERIODO: tam (4 bytes) + string (variável)
        int tamPeriodo = strlen(alunos[i]->periodo);
        bytesTotais += fwrite(&tamPeriodo, sizeof(int), 1, arq) * sizeof(int);
        bytesTotais += fwrite(alunos[i]->periodo, sizeof(char), tamPeriodo, arq) * sizeof(char);

        // 5. CAMPOS FIXOS: conclusao (4 bytes) + cra (4 bytes)
        bytesTotais += fwrite(&alunos[i]->conclusao, sizeof(int), 1, arq) * sizeof(int);
        bytesTotais += fwrite(&alunos[i]->cra, sizeof(float), 1, arq) * sizeof(float);
    }
    printf("Numero de bytes salvos: %zu\n", bytesTotais+4); // [cite: 16]
    fclose(arq); // [cite: 121, 130]
}

void CarregaAlunosBinario(Aluno **alunos, char *fileName) {
    FILE *arq = fopen(fileName, "rb"); // Modo de leitura binária [cite: 114]
    if (arq == NULL) return;

    int i = 0;
    int tam;
    // O fread retorna o número de elementos lidos [cite: 180]
    while (fread(&tam, sizeof(int), 1, arq) == 1) { 
        alunos[i] = (Aluno*)calloc(1, sizeof(Aluno)); // Aloca a estrutura do aluno

        // Lendo NOME
        fread(alunos[i]->nome, sizeof(char), tam, arq);
        alunos[i]->nome[tam] = '\0'; // Garante o terminador de string

        // Lendo DATA (Precisa ler o novo tamanho gravado)
        fread(&tam, sizeof(int), 1, arq);
        fread(alunos[i]->data, sizeof(char), tam, arq);
        alunos[i]->data[tam] = '\0';

        // Lendo CURSO
        fread(&tam, sizeof(int), 1, arq);
        fread(alunos[i]->curso, sizeof(char), tam, arq);
        alunos[i]->curso[tam] = '\0';

        // Lendo PERIODO
        fread(&tam, sizeof(int), 1, arq);
        fread(alunos[i]->periodo, sizeof(char), tam, arq);
        alunos[i]->periodo[tam] = '\0';

        // Lendo INTEIRO E FLOAT
        fread(&alunos[i]->conclusao, sizeof(int), 1, arq);
        fread(&alunos[i]->cra, sizeof(float), 1, arq);
        
        i++;
    }
    fclose(arq); // Sempre fechar após o uso [cite: 121]
}

void ImprimeAlunos(Aluno** alunos, int numeroAlunos){
    for(int i = 0; i < numeroAlunos; i++){
        printf("Aluno %d:\n", i);
        printf("Nome: %s\n", alunos[i]->nome);
        printf("Data Nascimento: %s\n", alunos[i]->data);
        printf("Curso: %s\n", alunos[i]->curso);
        printf("Periodo Ingresso: %s\n", alunos[i]->periodo);
        printf("%% Conclusao do Curso: %d\n", alunos[i]->conclusao);
        printf("CRA: %.2f\n", alunos[i]->cra);
    }
}