#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"
#include "passageiro.h"
#include "tripulante.h"
#include "voo.h"
#include "aeronave.h"
#include "reserva.h"
#include "fila.h"

int main() {
    Sistema *sistema = criaSistema();
    if (!sistema) {
        printf("Erro ao criar o sistema.\n");
        return 1;
    }

    sistemaRoda(sistema);    

    desalocaSistema(sistema);
    return 0;
}