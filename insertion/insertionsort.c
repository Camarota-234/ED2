#include <stdio.h>
#include <stdlib.h>

void insertionsort(int vetor[], int n) {
    int i;
    for (i= 1; i < n; i++) {
        int a = vetor[i];
        int j;
        for(j = i - 1; j >= 0 && vetor[j] > a; j--)
        {
            vetor[j + 1] = vetor[j];
            vetor[j] = a;
        }
    }
}


int main() {
    //int n = 10;
    //int i;
    //int vetor[n] = {3, 0, 1, 8, 7, 2, 5, 4, 9, 6};

    //for (i = 0; i < n; i++) {
    //    scanf("%d", &vetor[i]);
    //}

    int n, i;

    printf("tamanho do vetor: ");
    scanf("%d", &n);
    printf("\n");
    int vetor[n];

    printf("\nDigite os valores:");

    for (i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }

    insertionsort(vetor, n);

     printf("\nVetor ordenado: ");

    for (i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }

    return 0;
}