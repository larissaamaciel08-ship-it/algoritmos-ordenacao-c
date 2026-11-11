#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // Necessário para medir o tempo

int main(){
    int qtd;

    printf("Digite a qtd de numeros que deseja gerar: ");
    scanf("%i", &qtd);
    if(qtd <= 0){
        printf("\nNumero invalido\n");
        return 1;
    }

    // Alocamos três vetores para testar os três algoritmos com os MESMOS números
    int *numeros_bubble = (int *) malloc(qtd * sizeof(int));
    int *numeros_insertion = (int *) malloc(qtd * sizeof(int));
    int *numeros_selection = (int *) malloc(qtd * sizeof(int));

    if (numeros_bubble == NULL || numeros_insertion == NULL || numeros_selection == NULL){
        printf("Erro na alocacao!");
        return 1;
    }

    // Inicializando a seed
    srand(time(NULL));

    // 1. Gera os números aleatórios e preenche todos os vetores com os mesmos valores
    for(int i = 0; i < qtd; i++){
        int val = rand() % 1000001;
        numeros_bubble[i] = val;
        numeros_insertion[i] = val;
        numeros_selection[i] = val;
    }

    // Exibe os números gerados (desordenados)
    // Dica: Se 'qtd' for muito alto (ex: 50.000+), comente esta exibição para não poluir o console.
    printf("\n--- Numeros Gerados (Desordenados) ---\n");
    for(int i = 0; i < qtd; i++){
        printf("%d ", numeros_bubble[i]);
    }
    printf("\n");

    // ==========================================
    // 2. ORDENAÇÃO USANDO BUBBLE SORT
    // ==========================================
    clock_t inicio_bubble = clock();

    for(int i = 0; i < qtd - 1; i++){
        for(int j = 0; j < qtd - 1 - i; j++){
            if(numeros_bubble[j] > numeros_bubble[j + 1]){
                int temp = numeros_bubble[j];
                numeros_bubble[j] = numeros_bubble[j + 1];
                numeros_bubble[j + 1] = temp;
            }
        }
    }

    clock_t fim_bubble = clock();
    double tempo_bubble = (double)(fim_bubble - inicio_bubble) / CLOCKS_PER_SEC;


    // ==========================================
    // 3. ORDENAÇÃO USANDO INSERTION SORT
    // ==========================================
    clock_t inicio_insertion = clock();

    for(int i = 1; i < qtd; i++){
        int chave = numeros_insertion[i];
        int j = i - 1;

        while(j >= 0 && numeros_insertion[j] > chave){
            numeros_insertion[j + 1] = numeros_insertion[j];
            j--;
        }
        numeros_insertion[j + 1] = chave;
    }

    clock_t fim_insertion = clock();
    double tempo_insertion = (double)(fim_insertion - inicio_insertion) / CLOCKS_PER_SEC;


    // ==========================================
    // 4. ORDENAÇÃO USANDO SELECTION SORT
    // ==========================================
    clock_t inicio_selection = clock();

    for(int i = 0; i < qtd - 1; i++){
        int min_idx = i;
        for(int j = i + 1; j < qtd; j++){
            if(numeros_selection[j] < numeros_selection[min_idx]){
                min_idx = j;
            }
        }
        if(min_idx != i){
            int temp = numeros_selection[i];
            numeros_selection[i] = numeros_selection[min_idx];
            numeros_selection[min_idx] = temp;
        }
    }

    clock_t fim_selection = clock();
    double tempo_selection = (double)(fim_selection - inicio_selection) / CLOCKS_PER_SEC;


    // ==========================================
    // 5. EXIBIÇÃO DOS RESULTADOS E TEMPOS
    // ==========================================
    printf("\n--- Numeros Ordenados (Bubble Sort) ---\n");
    for(int i = 0; i < qtd; i++){
        printf("%d ", numeros_bubble[i]);
    }

    printf("\n\n--- Numeros Ordenados (Insertion Sort) ---\n");
    for(int i = 0; i < qtd; i++){
        printf("%d ", numeros_insertion[i]);
    }

    printf("\n\n--- Numeros Ordenados (Selection Sort) ---\n");
    for(int i = 0; i < qtd; i++){
        printf("%d ", numeros_selection[i]);
    }
    printf("\n");

    // Comparativo de tempos
    printf("\n========================================\n");
    printf("   COMPARATIVO DE TEMPO DE EXECUCAO\n");
    printf("========================================\n");
    printf("Tempo (Bubble Sort):    %.6f segundos\n", tempo_bubble);
    printf("Tempo (Insertion Sort): %.6f segundos\n", tempo_insertion);
    printf("Tempo (Selection Sort): %.6f segundos\n", tempo_selection);
    printf("========================================\n");

    // Libera a memória alocada para os três vetores
    free(numeros_bubble);
    free(numeros_insertion);
    free(numeros_selection);

    return 0;
}
