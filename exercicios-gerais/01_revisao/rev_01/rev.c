#include <stdio.h>
#include <math.h>

float calculateDistance(float x1, float y1, float x2, float y2){

    float distance;

    distance = pow(x2-x1, 2) + pow(y2-y1, 2);
    distance = sqrt(distance);

    return distance;
}

int main(){
    float x1, y1, r1;
    float x2, y2, r2;
    float distancia;
    float somaRaios;

    scanf("%f %f %f\n", &x1, &y1, &r1);
    scanf("%f %f %f", &x2, &y2, &r2);

    somaRaios = r1 + r2;
    distancia=calculateDistance(x1, y1, x2, y2);

    if(distancia <= somaRaios){
        printf("ACERTOU");
    }
    else printf("ERROU");

    return 0;
}