#include <stdio.h>

int main(int argc, char * argv[]){
    if (argc < 2) {
        printf("ERRO: Informe o diretorio com os arquivos de configuracao.\n");
        return 1; 
    }
    char* caminho_do_caso_de_teste = argv[1];

    printf("O script me disse para usar os arquivos do diretorio: %s\n", caminho_do_caso_de_teste);

    return 0;
}
