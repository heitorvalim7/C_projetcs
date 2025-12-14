#include "livro.h"
#include <stdio.h>

tLivros lerLivro(){
    tLivros l;
    scanf("%s\n", l.titulo);
    scanf("%s\n", l.autor);
    scanf("%d", &l.anoPublicacao);

    return l;
}
void imprimeLivro(tLivros livro){
    printf("Titulo: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Ano de Publicacao: %d\n", livro.anoPublicacao);
}
