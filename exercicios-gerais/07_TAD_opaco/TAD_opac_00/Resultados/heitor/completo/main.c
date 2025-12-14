#include <stdio.h>
#include <stdlib.h>
#include "circulo.h"

int main(){
    float x1, y1, r, x2, y2;
    tCirculo c;
    tPonto p;

    scanf("%f %f %f %f %f", &x1, &y1, &r, &x2, &y2);

    c = Circulo_Cria(x1, y1, r);
    p = Pto_Cria(x2, y2);
    printf("%d", Circulo_Interior(c, p));
    Pto_Apaga(p);
    Circulo_Apaga(c);
}