#include "calculadora.h"
#include <stdio.h>

float Calcular(float num1, float num2, CalculatoraCallback operacao){
    float resultado = operacao(num1, num2);
    return resultado;
}