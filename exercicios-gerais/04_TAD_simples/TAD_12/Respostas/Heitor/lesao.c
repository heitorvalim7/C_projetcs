#include <stdio.h>
#include "lesao.h"
#include <string.h>

Lesao criaLesao(char *cartaoSus, char *id, char *diagnostico, char *regiao, int malignidade){
    Lesao l;
    strcpy(l.cartaoSus, cartaoSus);
    strcpy(l.id, id);
    strcpy(l.diagnostico, diagnostico);
    strcpy(l.regiao, regiao);
    l.malignidade = malignidade;

    return l;
}

Lesao lerLesao(){
    Lesao l;
    scanf("%[^\n]\n", l.cartaoSus);
    scanf("%[^\n]\n", l.id);
    scanf("%[^\n]\n", l.diagnostico);
    scanf("%[^\n]\n", l.regiao);
    scanf("%d", &l.malignidade);
}

void getCartaoSusLesao(Lesao l, char *cartaoSus){
    strcpy(cartaoSus, l.cartaoSus);
}

int verificaCirurgicaLesao(Lesao l){
    if (l.malignidade > 50){
        return 1;
    }
    return 0;
}

void imprimeIdLesao(Lesao l){
    printf("%d", l.id);
}
