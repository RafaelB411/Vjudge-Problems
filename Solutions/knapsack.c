#include <stdio.h>
#include <stdlib.h>

int max(int num1, int num2) {
    if(num1>num2) return num1;
    else return num2;
}

int knapsack(int n, int cap, int weight[2000], int value[2000], int fill[2000][2000]) {
    for(int i=0; i<n+1; i++) {
        for(int j=0; j<cap+1; j++) {
            if(i==0 || j==0) fill[i][j] = 0;
            else if(weight[i]<j+1) 
                fill[i][j] = max(fill[i-1][j], value[i]+fill[i-1][j-weight[i]]);
            else fill[i][j] = fill[i-1][j];
        }
    }
    return fill[n][cap];
}

int main() {
    int cap, nitems, weight[2000], value[2000], fill[2000][2000], solucao;

    scanf("%d %d", &cap, &nitems);
    for(int i=1; i<nitems+1; i++) {
        scanf("%d %d", &weight[i], &value[i]);
    }
    
    solucao = knapsack(nitems, cap, weight, value, fill);

    printf("%d\n", solucao);

    return 0;
}