#include <stdio.h>
#include "calculadora.h"

float adicao(float n1, float n2){
    return n1+n2;
}
float subtracao(float n1, float n2){
    return n1-n2;
}
float multiplica(float n1, float n2){
    return n1*n2;
}
float divide(float n1, float n2){
    return n1/n2;
}

int main(){
    char op;
    float n1, n2, resultado;
    CalculatoraCallback calcula;
    while(1){
        scanf("%c\n", &op);
        switch (op) {
            case 'a': 
               calcula = adicao;
               break;
            case 's':
                calcula = subtracao;
                break;
            case 'm':
                calcula = multiplica;
                break;
            case 'd': 
                calcula=divide;
                break;
            case 'f':
                return 0;
        }
        scanf("%f %f", &n1, &n2);
        resultado = Calcular(n1, n2, calcula);
        switch (op) {
            case 'a': 
                printf("%.2f + %.2f = %.2f\n", n1, n2, resultado);
               break;
            case 's':
                printf("%.2f - %.2f = %.2f\n", n1, n2, resultado);
                break;
            case 'm':
                printf("%.2f x %.2f = %.2f\n", n1, n2, resultado);
                break;
            case 'd': 
                printf("%.2f / %.2f = %.2f\n", n1, n2, resultado);
                break;
        }
    }
    return 0;
}