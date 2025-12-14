#include <stdio.h>
#include <string.h>
#include "data.h"
#include "lesao.h"
#include "paciente.h"
#define MAX_P 100

int main(){
    Paciente bancoDePacientes[MAX_P];
    int numP = 0;
    char opcao;

    while(1){
        scanf("%c\n", &opcao);

        if(opcao == 'P' && numP < 100){
            bancoDePacientes[numP] = lerPaciente();
            numP++;
        }
        if(opcao == 'L'){
            Lesao l;
            l = lerLesao();
            char CartaoSusLesao[MAX_CARTAO_LES];
            getCartaoSusLesao(l, CartaoSusLesao);
            char CartaoSusPaciente[MAX_CARTAO_LES];

            for(int i=0; i<numP; i++){
                getCartaoSusPaciente(bancoDePacientes[i], CartaoSusPaciente);
                if(strcmp(CartaoSusLesao, CartaoSusPaciente)==0){
                   vinculaLesaoPaciente(bancoDePacientes[i], l);
                }
            }
        }
        
    }
}