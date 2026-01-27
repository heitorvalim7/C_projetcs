#include "estabelecimento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    tEstabelecimento *e = CriaEstabelecimento();
    LeEstabelecimento(e);
    ImprimeProdutosEmFaltaEstabelecimento(e);
    DestroiEstabelecimento(e);
}