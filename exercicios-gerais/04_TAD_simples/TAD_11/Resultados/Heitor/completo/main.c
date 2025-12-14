#include <stdio.h>
#include "loja.h"
#include "vendedor.h"

int main(){
    int totalLojas;
    int cadastradasLojas=0;
    tLoja lojas[1000];

    scanf("%d\n", &totalLojas);

    while(1){
        int opcao;
        scanf("%d\n", &opcao);
        if(opcao == 0) return 0;

        if(opcao == 1 && cadastradasLojas < totalLojas){
            int id;
            float aluguel;

            scanf("%d %f\n", &id, &aluguel);

            lojas[cadastradasLojas] = AbreLoja(id, aluguel);
            cadastradasLojas++;
        }
        if(opcao == 2){
            char nome[50];
            float salario;
            float comissao;
            int id;
            scanf("%s %f %f\n", nome, &salario, &comissao);
            tVendedor v = RegistraVendedor(nome, salario, comissao);
            scanf("%d\n", &id);

            for(int i = 0; i<cadastradasLojas; i++){
                if(VerificaIdLoja(lojas[i], id) && lojas[i].totalVendedores<10){
                    lojas[i] = ContrataVendedor(lojas[i], v);
                }
            }
        }
        if(opcao == 3){
            char nome[50];
            int id;
            float valor;

            scanf("%d %s %f\n", &id, nome, &valor);

            for(int i = 0; i<cadastradasLojas; i++){
                if(VerificaIdLoja(lojas[i], id)){
                    lojas[i] = RegistraVenda(lojas[i], nome, valor);
                }
            }
        }
        if(opcao == 4){
            
            for(int i = 0; i<cadastradasLojas; i++){
                lojas[i] = CalculaLucro(lojas[i]);
                ImprimeRelatorioLoja(lojas[i]);
            }
        }
    }
    return 0;
} 