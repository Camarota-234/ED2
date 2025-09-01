#include <stdio.h>
#include <stdlib.h>


void shellsort(int vetor[], int n) {

    int i, j, valor;
    int gap = 1;
    while(gap < n) {
        gap = 3*gap+1;
    }
    while(gap> 1) {

        gap /=3;

        for(i = gap; i < n; i++) {
            valor = vetor[i];
            j = i - gap;
            while(j >= 0 && valor < vetor[j]) {
                vetor[j + gap] = vetor[j];
                j-= gap;
            }
            vetor[j + gap] = valor;
        }
        for(i = 0; i < n; i++) {
            printf("%d ", vetor[i]);
    
        } printf("\n");

    }

}




void main() {

    int n = 10;
    int i;
    int vetor[10] = {3, 0, 1, 8, 7, 2, 5, 4, 9, 6};
    
    for(i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    } printf("\n");
    
    shellsort(vetor, n);

    for(i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    return 0;
}

//João Guilherme Camarota 202201638
//Arthur Paro 202201607