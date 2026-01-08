#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"
#include "passageiro.h"
#include "tripulante.h"
#include "voo.h"
#include "aeronave.h"
#include "reserva.h"
#include "fila.h"

int main() {
    Sistema *sistema = criaSistema();
    if (!sistema) {
        printf("Erro ao criar o sistema.\n");
        return 1;
    }

    char comando;



    while (scanf(" %c", &comando) == 1 && comando != 'F') {

        if (comando == 'P') {
            sistemaAdicionaPassageiro(sistema);
        }else if (comando == 'T') {
            sistemaAdicionaTripulante(sistema);
        }else if (comando == 'A') {
            sistemaAdicionaAeronave(sistema);
        } else if (comando == 'V') {
            sistemaAdicionaVoo(sistema);    
        } else if (comando == 'R') {
            sistemaAdicionaReserva(sistema);
        } else if (comando == 'E') {

            char acao[100];
            scanf(" %[^\n]", acao); 

            if (strcmp(acao, "PROCESSA RESERVAS") == 0) {
                
                processaReservasNaFila(sistemaGetFila(sistema), sistema, sistema);

            } else if (strcmp(acao, "CONSULTA RESERVAS") == 0) {

                printf("================================\n");
                printf("===== Consulta Reservas ========\n");
                printf("================================\n");
                imprimeFila(sistemaGetFila(sistema));
                printf("================================\n"); 

            } else if (strcmp(acao, "RELATORIO") == 0) {

                sistemaImprimeRelatorio(sistema); 

            } else if (strcmp(acao, "PASSAGEIROS") == 0) {

                sistemaImprimeBancoPassageiros(sistema); 

            } else if (strcmp(acao, "TRIPULANTES") == 0) {

                sistemaImprimeBancoTripulantes(sistema); 

            } else if(strcmp(acao, "RANKING PASSAGEIROS") == 0) {

                sistemaImprimeRankingPassageiros(sistema, sistemaQntdPassageiros(sistema));  
            
            } else if(strcmp(acao, "RANKING TRIPULANTES") == 0) {

                sistemaImprimeRankingTripulantes(sistema);  
            
            }
        }
    }    

    desalocaSistema(sistema);
    return 0;
}