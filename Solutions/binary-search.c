#include <stdio.h>
#include <stdlib.h>

int Search(int* array, int tam, int key) {
    int l = 0, r = tam-1;
    while(l <= r) {
        int m = (l+r)/2;
        if(key == array[m]) {
            while(array[m] == array[m-1]) m = m-1;
            return m;
        }
        else if(key > array[m]) {
            l = m+1;
        }
        else if(key < array[m]) {
            r = m-1;
        }
    }
    return -1;
}

int main() {
    long long int tam, query, index, key;
    int *array = NULL;

    scanf("%lld %lld", &tam, &query);

    array = (int*) malloc(tam * sizeof(long long int));
    if(array == NULL) { printf("Problema na alocacao\n"); exit(-1); }

    for(int i=0; i<tam; i++)
        scanf("%lld", &array[i]);

    for(int i=0; i<query; i++) {
        scanf("%lld", &key);
        index = Search(array, tam, key);
        printf("%lld\n", index);
    }

    free(array);

    return 0;
}