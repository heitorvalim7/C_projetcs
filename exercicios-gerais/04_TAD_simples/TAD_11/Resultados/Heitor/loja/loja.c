#include "loja.h"
#include <stdio.h>

tLoja AbreLoja(int id, float aluguel){
    tLoja l;
    l.aluguel = aluguel;
    l.id = id;
    l.lucro = 0;
    l.totalVendedores = 0;
    return l;
}

int VerificaIdLoja(tLoja loja, int id){
    if(loja.id == id){
        return 1;
    }
    return 0;
}
tLoja ContrataVendedor(tLoja loja, tVendedor vendedor){
    loja.vendedores[loja.totalVendedores] = vendedor;
    loja.totalVendedores++;
    loja=CalculaLucro(loja);
    return loja;
}
tLoja RegistraVenda(tLoja loja, char nome[50], float valor){
    for(int i = 0; i<loja.totalVendedores; i++){
        if(VerificaNomeVendedor(loja.vendedores[i], nome)){
            loja.vendedores[i]=ContabilizaVenda(loja.vendedores[i], valor);
            break;
        }
    }
    loja=CalculaLucro(loja);

    return loja;
}
tLoja CalculaLucro(tLoja loja){
    float total_vendido=0;
    float total_recebidos=0;
    for(int i =0; i<loja.totalVendedores; i++){
        total_vendido += GetTotalVendido(loja.vendedores[i]);
    }
    for(int i = 0; i<loja.totalVendedores; i++){
        total_recebidos += GetTotalRecebido(loja.vendedores[i]);
    }
    loja.lucro = total_vendido - total_recebidos - loja.aluguel;
    return loja;
}
void ImprimeRelatorioLoja(tLoja loja){
    loja=CalculaLucro(loja);
    printf("Loja %d: Lucro total: R$ %.2f\n", loja.id, loja.lucro);
    for(int i = 0; i<loja.totalVendedores; i++){
        ImprimeRelatorioVendedor(loja.vendedores[i]);
    }
}
