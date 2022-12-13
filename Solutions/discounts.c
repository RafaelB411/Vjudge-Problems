#include <stdio.h>
#include <stdlib.h>

int Partition(int* A, int l, int r) {
    int p = A[l], i = l, j = r+1, swap;

    do{
        do{
            i++;
        } while(A[i]<p && i<r);

        do{
            j--;
        } while(A[j]>p);

        swap = A[i];
        A[i] = A[j];
        A[j] = swap;
    } while(i < j);

    swap = A[i];
    A[i] = A[j];
    A[j] = swap;

    swap = A[l];
    A[l] = A[j];
    A[j] = swap;

    return j;
}

void Quicksort(int* A, int l, int r) {
    if(l<r) {
        int s = Partition(A, l, r);
        Quicksort(A, l, s-1);
        Quicksort(A, s+1, r);
    }
}

int main() {
    long long int numBars, numCoupons, discount, sum = 0, money;
    int *prices = NULL;

    scanf("%lld", &numBars);

    prices = (int*) malloc(numBars * sizeof(long long int));
    if(prices == NULL) { printf("Problema na alocacao\n"); exit(-1); }

    for(int i=0; i<numBars; i++) {
        scanf("%lld", &prices[i]);
        sum += prices[i];
    }

    scanf("%lld", &numCoupons);

    Quicksort(prices, 0, numBars-1);

    for(int i=0; i<numCoupons; i++) {
        scanf("%lld", &discount);
        int index = numBars-discount;
        money = sum-prices[index];
        printf("%lld\n", money);
    }

    free(prices);

    return 0;
}