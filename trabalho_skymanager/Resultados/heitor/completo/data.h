#ifndef _DATA_H_
#define _DATA_H_

typedef struct Data Data;

/* Cria uma Data validada. Retorna NULL se inválida. */
Data *criaData(int dia, int mes, int ano);

/* Lê uma data do stdin no formato: dia mes ano (3 inteiros) */
Data *leData();

/* Imprime no formato dd/mm/aaaa */
void imprimeData(void *dado);

/* Desaloca (compatível com callbacks genéricos) */
void desalocaData(Data *d);

/* Getters */
int getDia(Data *d);
int getMes(Data *d);
int getAno(Data *d);

/* Valida uma data; 1 = válida, 0 = inválida */
int validaData( Data *d);
/* Verifica se o ano é bissexto */
int ehBissexto(int ano);

/* Compara duas datas: retorna <0 se a<b, 0 se igual, >0 se a>b */
int comparaData( Data *a, Data *b);

/* Calcula a idade em anos entre duas datas */
int calculaIdade(Data *dataNascimento, Data *dataAtual);


#endif // _DATA_H_
