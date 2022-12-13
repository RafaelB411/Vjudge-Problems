#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool prime(int number) {
    for(int div=2; div<number; div++) {
        if(number%div==0) return false;
    }
    return true;
}

void ring(int start, int circle[16], int n, int index, bool visit[17]) {
    circle[index] = start;
    visit[start] = true;
    if(index==n-1 && prime(1+circle[n-1])) {
        for(int i=0; i<n; i++) {
            printf("%d", circle[i]);
            if(i<n-1) printf(" ");
            else printf("\n");
        }
    }
    else {
        for(int k=1; k<n+1; k++) {
            if(prime(start+k) && !visit[k]) {
                    ring(k, circle, n, index+1, visit);
                    visit[k] = false;
            }
        }
    }
}


int main() {
    int qnt, cases = 1, circle[16];
    bool visit[17];

    while(scanf("%d", &qnt)!=EOF) {
        for(int i=0; i<17; i++) {
            visit[i] = false;
        }
        if(cases!=1) printf("\n");
        printf("Case %d:\n", cases);
        ring(1, circle, qnt, 0, visit);
        cases++;
    }

    return 0;
}