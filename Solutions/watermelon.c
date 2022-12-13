#include <stdio.h>

int main() {
    int peso;

    scanf("%d", &peso);
    if(peso < 4) printf("NO\n");
    else if(peso%2==0) printf("YES\n");
    else printf("NO\n");
    return 0;
}