#include <stdio.h>
#include "tDepartamento.h"

int main(){

    int n;

    scanf("%d", &n);
    tDepartamento departamentos[n];

    int i = 0;

    while(i<n){ 
        char nome[100];
        char diretor[100];
        char curso1[100], curso2[100], curso3[100];
        int m1, m2, m3;
        scanf("%s\n", nome);
        scanf("%s\n", diretor);
        scanf("%s\n", curso1);
        scanf("%s\n", curso2);
        scanf("%s\n", curso3);
        scanf("%d %d %d", &m1, &m2, &m3);

        if(m1 < 0 || m2<0 || m3<0){
            printf("\nDigite um departamento com médias válidas");
        }
        else{
            departamentos[i]=CriaDepartamento( curso1, curso2, curso3, nome, m1,  m2,  m3,  diretor );
            i++;
        }
    }
    OrdenaDepartamentosPorMedia(departamentos, n);
    for(i=0; i<n; i++){
        ImprimeAtributosDepartamento(departamentos[i]);
    }
}