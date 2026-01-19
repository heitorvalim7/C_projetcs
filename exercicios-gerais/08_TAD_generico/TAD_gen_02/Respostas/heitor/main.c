#include "gerenciadorpacotes.h"
#include "pacote.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    tGerenciador* geren = CriaGerenciador();
    int n=0;
    while(n!=3){
        printf("\n");
        printf("Escolha uma opcao:\n");
        printf("        (1) Cadastrar um novo pacote\n");
        printf("        (2) Imprimir um pacote especifico\n");
        printf("        (3) Imprimir todos os pacotes e sair");
        scanf("%d", &n);
        if(n == 1){
            int tipo, numElem;
            printf("Digite o tipo (0-char, 1-int) e o numero de elementos do pacote/mensagem:\n");
            scanf("%d %d", &tipo, &numElem);
            if(tipo == 0){
                tPacote* pac = CriaPacote(CHAR, numElem);
                LePacote(pac);
                AdicionaPacoteNoGerenciador(geren, pac);
            } else if(tipo == 1){
                tPacote* pac = CriaPacote(INT, numElem);
                LePacote(pac);
                AdicionaPacoteNoGerenciador(geren, pac);
            }
        }
        if(n == 2){
            int idx;
            scanf("%d", &idx);
            ImprimirPacoteNoIndice(geren, idx);
        }
        if(n == 3){
            ImprimirTodosPacotes(geren);
        }
    } 
    DestroiGerenciador(geren);
    return 0;
}