#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

int main() {
    int numeroAlunos;

    printf("Digite o numero de alunos: ");
    if (scanf("%d", &numeroAlunos) != 1) return 1;
    
    scanf("%*c");

    Aluno **vetorAlunos = CriaVetorAlunos(numeroAlunos);
    LeAlunos(vetorAlunos, numeroAlunos);

    SalvaAlunosBinario(vetorAlunos, "alunos.bin", numeroAlunos);

    LiberaAlunos(vetorAlunos, numeroAlunos);

    Aluno **vetorLido = CriaVetorAlunos(numeroAlunos);
    CarregaAlunosBinario(vetorLido, "alunos.bin");

    ImprimeAlunos(vetorLido, numeroAlunos);

    LiberaAlunos(vetorLido, numeroAlunos);

    return 0;
}