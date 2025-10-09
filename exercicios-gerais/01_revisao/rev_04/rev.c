#include <stdio.h>
#include <math.h>

int main(){
    int i=0;
    int decNumber;
    int octNumber=0;
    
    scanf("%d", &decNumber);
    
    for(i=0; decNumber > 0 != 0; i++){ 
        octNumber += (decNumber % 8) * pow(10, i);
        decNumber = decNumber / 8;
    }
    
    printf("%d", octNumber);

    return 0;
}