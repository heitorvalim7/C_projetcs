#include "banco.h"
#include "conta.h"
#include "agencia.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    tBanco *b = CriaBanco();
    LeBanco(b);

    char op;
    while(scanf(" %c", &op)==1){
        if(op == 'A'){
            tAgencia *a = CriaAgencia();
            LeAgencia(a);
            AdicionaAgencia(b, a);
        }
        else if(op == 'C'){
            int numAg;
            tConta *c = CriaConta();
            LeConta(c);
            scanf("%d", &numAg);
            InsereContaBanco(b, numAg, c);
        }
        else if(op == 'F'){
            ImprimeRelatorioBanco(b);
            DestroiBanco(b);
            break;
        }
    }

    return 0;

}