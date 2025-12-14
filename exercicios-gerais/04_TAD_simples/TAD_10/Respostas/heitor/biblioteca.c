#include "biblioteca.h"
#include <stdio.h>
#include <string.h>

tBiblioteca inicializarBiblioteca(){
    tBiblioteca b;
    return b;
}

tBiblioteca adicionarLivroNaBiblioteca(tBiblioteca biblioteca, tLivros livro){
    biblioteca.livros[biblioteca.tamanho] = livro;
    biblioteca.tamanho++;
    return biblioteca;
}

tBiblioteca removerLivroDaBiblioteca(tBiblioteca biblioteca, char *titulo){
    for(int i = 0; i<biblioteca.tamanho; i++)
        if(verificaTituloDoLivroNaBiblioteca(biblioteca.livros[i], titulo)){
            for(int j = 0; j<biblioteca.tamanho - i; j++){
                biblioteca.livros[j+i] = biblioteca.livros[j+i+1];
            }
            
        }
    
}
int verificaTituloDoLivroNaBiblioteca(tLivros livro, char* titulo){
    if(strcmp(titulo, livro.titulo)==0){
        return 1;
    }
    return 0;
}

