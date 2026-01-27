#include "base_alunos.h"
#include "aluno.h"
#include <stdio.h>
#include <stdlib.h>

struct BaseAlunos{
    tAluno **alunos;
};

/**
 * @brief Função para criar uma nova base de alunos.
 * 
 * @return Um ponteiro para a base de alunos recém-criada. Se houver erro na alocação de memória, o programa é encerrado.
 */
tBaseAlunos* CriarBaseAlunos(){
    tBaseAlunos *b = (tBaseAlunos*)calloc(1, sizeof(tBaseAlunos));
    return b;
}

/**
 * @brief Função para destruir uma base de alunos.
 * 
 * @param baseAlunos A base de alunos a ser destruída.
 */
void DestruirBaseAlunos(tBaseAlunos* baseAlunos){
    
}

/**
 * @brief Função para ler uma base de alunos de um arquivo binário.
 * 
 * @param baseAlunos A base de alunos para ler o arquivo.
 * @param nomeArquivo O nome do arquivo a ser lido.
 */
void LerBaseAlunos(tBaseAlunos* baseAlunos, char* nomeArquivo);

/**
 * @brief Função para obter o coeficiente de rendimento médio de uma base de alunos.
 * 
 * @param baseAlunos A base de alunos para obter o coeficiente de rendimento médio.
 * @return O coeficiente de rendimento médio da base de alunos.
 */
float GetCoeficienteRendimentoMedioBaseAlunos(tBaseAlunos* baseAlunos);