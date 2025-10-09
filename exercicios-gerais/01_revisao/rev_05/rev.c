#include <stdio.h>
#define size 1000

int main(){
    int n, m;
    int i, j;
    int x1, y1;
    int x2, y2;
    int xa, ya;
    char dire[5];
    char b=0;
    char a;
    int flag = 0;

    scanf("%d %d", &n, &m);
    int map[n][m];

    for(i=0; i<n; i++){
        for(j=0; j<m; j++){
            scanf("%d ", &map[i][j]);
        }
        scanf("\n");
    }
    
    scanf("%d %d\n", &x1, &y1);
    scanf("%d %d\n", &x2, &y2);

    x1--;
    y1--;
    x2--;
    y2--;

    scanf("%s", dire);

    xa = x1;
    ya = y1;

    map[xa][ya] = 1;

    printf("(%d,%d) ", xa+1, ya+1);

    while(1){

        for(b=0; b<4; b++){
            a = dire[b];

            switch (a){
                case 'B':
                    if(map[xa+1][ya] == 0 && xa+1 < n){
                        map[xa][ya]= 1;
                        xa += 1;
                        flag = 1;
                    }
    
                    break;
                case 'C':
                    if(map[xa-1][ya] == 0 && xa-1 >= 0){
                        map[xa][ya]= 1;
                        xa -= 1;
                        flag = 1;
                    }
                    
                    break;
                case 'D':
                    if(map[xa][ya+1] == 0 && ya+1 < m){
                        map[xa][ya]= 1;
                        ya += 1;
                        flag = 1;
                    }
                   
                    break;
                case 'E':
                    if(map[xa][ya-1] == 0 && ya-1 >= 0){
                        map[xa][ya]= 1;
                        ya -= 1;
                        flag = 1;
                    }
                    
                    break;
            }

            if(flag){
                break;
            }
            
        }
        if(flag){
            printf("(%d,%d) ", xa+1, ya+1);
        }
        else break;

        if (x2 == xa && y2 == ya){
            break;
        }
        flag = 0;
    }
    printf("\n");
    
    return 0;
}