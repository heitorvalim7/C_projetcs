#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

int main(){
    int total;
    tAluno **a;
    scanf("%d", &total);
    a = (tAluno**)calloc(total, sizeof(tAluno*));
    for(int i = 0; i<total; i++){
        a[i] = CriaAluno();
        LeAluno(a[i]);
    }
    for(int i = 0; i<total-1; i++){
        for(int j = i+1; j<total; j++){
            if(ComparaMatricula(a[i], a[j])==1){
               tAluno *aux = a[i];
                a[i] = a[j];
                a[j] = aux;
            }
        }
    }
    for(int i = 0; i<total; i++){
        if(VerificaAprovacao(a[i])){
            ImprimeAluno(a[i]);
        }
    }
    for(int i = 0; i<total; i++){
        ApagaAluno(a[i]);
    }
    free(a);
}