#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TAMANHO_STR 8
#define MAX_TAMANHO_LISTA 100

typedef struct {
    char data[MAX_TAMANHO_STR + 1];
    int prox;
} Node;

typedef struct {
    Node nodes[MAX_TAMANHO_LISTA];
    int head;
    int size;
} StaticList;


void init_list(StaticList *list) {
    list->head = -1;
    list->size = 0;
}

int insert_list(StaticList *list, const char *str) {
    if (list->size >= MAX_TAMANHO_LISTA) return 0;

    int index = list->size;
    strcpy(list->nodes[index].data, str);
    list->nodes[index].prox = list->head;
    list->head = index;
    list->size++;
    return 1;
}

int string_to_int(const char *str) {
    int soma = 0;
    while (*str) {
        soma += (int)(*str);
        str++;
    }
    return soma;
}

int simple_hash(const char *str, int M) {
    int x = string_to_int(str);
    return (5 * x) % M;
}

void gera_string_aleatoria(char *str) {
    int i;
    for (i = 0; i < MAX_TAMANHO_STR; i++) {
        str[i] = 'a' + rand() % 26;
    }
    str[MAX_TAMANHO_STR] = '\0';
}

void varios_testes(FILE *fout, int M, int num_strings) {
    int total_colisoes = 0;
    double total_tempo = 0;

    int i;
    for (i = 0; i < 10; i++) {
        StaticList *hash_table = (StaticList *)malloc(M * sizeof(StaticList));
        int j;
        for (j = 0; j < M; j++) init_list(&hash_table[j]);

        int collisions = 0;
        char str[MAX_TAMANHO_STR + 1];

        clock_t start = clock();
        for (j = 0; j < num_strings; j++) {
            gera_string_aleatoria(str);
            int hash = simple_hash(str, M);
            if (hash_table[hash].size > 0)
                collisions++;
            insert_list(&hash_table[hash], str);
        }
        clock_t end = clock();
        double exec_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        total_colisoes += collisions;
        total_tempo += exec_time;

        free(hash_table);
    }

    double media_colisoes = total_colisoes / 10.0;
    double media_tempo = total_tempo / 10.0;

    printf(">>> M = %d | N = %d | Média de colisões: %.2f | Média de tempo: %.6f s\n",
           M, num_strings, media_colisoes, media_tempo);

    if (fout)
        fprintf(fout, "%d,%d,%.2f,%.6f\n", M, num_strings, media_colisoes, media_tempo);
}

int main() {
    srand(time(NULL));

    int M_valores[] = {31, 79, 151};
    int N_valores[] = {100, 1000, 10000};

    FILE *fout = fopen("resultados.csv", "w");
    if (!fout) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return 1;
    }

    fprintf(fout, "M,N,Media_Colisoes,Media_Tempo\n");

    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("=== Testando M = %d com %d strings ===\n", M_valores[i], N_valores[j]);
            varios_testes(fout, M_valores[i], N_valores[j]);
        }
    }

    fclose(fout);
    printf("\nResultados salvos em 'resultados.csv'\n");
    return 0;
}
//Alunos: 
//João Guilherme Camarota 202201638
//Yuri Cassiano Matsuoka 202302595