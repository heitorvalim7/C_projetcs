#include <stdio.h>


int main() {
    
    int n, i, j;
    int num = 1;
    scanf("%d", &n);

    for(i=0; i<n; i++){
        for(j=-1; j<i; j++){
            printf("%d ", num);
            num++;
        }
        printf("\n");
    }
    
    return 0; 
}