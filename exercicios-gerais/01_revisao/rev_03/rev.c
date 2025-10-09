#include <stdio.h>
#define TAM 1000

int main(){
    int n;
    int i;
    int books[TAM];
    int book;
    
    scanf("%d", &n);

    for(i=0; i<TAM; i++){
        books[i]=0;
    }

    for(i=0; i<n; i++){
        scanf("%d", &book);
        books[book]++;
    }

    for(i=0; i<TAM; i++){
        if(books[i]==1){
            printf("%d ", i);
        }
    }
   
    return 0;
}
