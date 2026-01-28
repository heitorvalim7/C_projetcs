#include "estabelecimento.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    tEstabelecimento *e = CriaEstabelecimento();
    LeEstabelecimento(e);
    ImprimeRelatorioEstabelecimento(e);
    DestroiEstabelecimento(e);

    return 0;
}