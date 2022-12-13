#include <stdio.h>

int main() {
    long long int n, m, a, fact1, fact2;

    scanf("%lld %lld %lld", &n, &m, &a);
    if(n%a!=0) fact1 = n/a+1;
    else fact1 = n/a;
    if(m%a!=0) fact2 = m/a+1;
    else fact2 = m/a;
    printf("%lld\n", fact1*fact2);

    return 0;
}