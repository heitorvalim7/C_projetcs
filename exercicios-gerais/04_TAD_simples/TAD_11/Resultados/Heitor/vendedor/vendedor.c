#include "vendedor.h"
#include <string.h>
#include <stdio.h>

tVendedor RegistraVendedor(char nome[50], float salario, float prct_comissao){
    tVendedor v;
    strcpy(v.nome, nome);
    v.salario = salario;
    v.prct_comissao = prct_comissao;
    v.valor_vendido = 0;
    return v;
}
int VerificaNomeVendedor(tVendedor vendedor, char nome[50]){
    if(strcmp(vendedor.nome, nome)==0){
        return 1;
    }
    return 0;
}
tVendedor ContabilizaVenda(tVendedor vendedor, float valor){
    vendedor.valor_vendido += valor;
    return vendedor;
}
float GetSalario(tVendedor vendedor){
    return vendedor.salario;
}
float GetComissao(tVendedor vendedor){
    return vendedor.prct_comissao * vendedor.valor_vendido;
}
float GetTotalVendido(tVendedor vendedor){
    return vendedor.valor_vendido;
}
float GetTotalRecebido(tVendedor vendedor){
    float total;
    float comissao, salario, valor;
    salario = GetSalario(vendedor);
    comissao = GetComissao(vendedor);

    total = salario + (comissao);

    return total;
}
void ImprimeRelatorioVendedor(tVendedor vendedor){
    printf("    %s > Total vendido: R$%.2f\n", vendedor.nome, vendedor.valor_vendido);
    printf("        Total recebido: R$%.2f\n", GetTotalRecebido(vendedor));
}
