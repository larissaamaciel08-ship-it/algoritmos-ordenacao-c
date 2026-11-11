#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

// ========================================== // ESTRUTURAS AUXILIARES (BUCKET SORT) //
========================================== 
typedef struct Node {
  int data;
  struct Node* next; 
} Node;

// ========================================== // PROTÓTIPOS DAS FUNÇÕES //
========================================== 
  void copiarVetor(int *origem, int *destino, int n);
void troca(int *a, int *b); 

// Categoria O(n^2) void bubbleSort(int *arr, int n); 
void insertionSort(int *arr, int n); 
void selectionSort(int *arr, int n); 

// Categoria O(n log n) void merge(int *arr, int l, int m, int r);
void mergeSort(int *arr, int l, int r);
int partition(int *arr, int low, int high); 
void quickSort(int *arr, int low, int high); 
void heapify(int *arr, int n, int i);
void heapSort(int *arr, int n);

// Categoria Lineares Não-Comparativos void countingSort(int *arr, int n); 
void countingSortForRadix(int *arr, int n, int exp);
void radixSort(int *arr, int n); 
void bucketSort(int *arr, int n); 

// ========================================== 
// FUNÇÃO PRINCIPAL (MAIN) 
// ========================================== 
int main(){
  int qtd; 

  printf("Digite a qtd de numeros que deseja gerar: "); 
  scanf("%i", &qtd); 
  if(qtd <= 0){ 
      printf("\nNumero invalido\n"); 
      return 1; 
              } 

// Alocamos apenas 2 vetores no total para eficiência 
int *vetor_original = (int *) malloc(qtd * sizeof(int));
int *vetor_teste = (int *) malloc(qtd * sizeof(int)); 

if (vetor_original == NULL || vetor_teste == NULL){ 
  printf("Erro na alocacao!"); 
  return 1; 
}

// Inicializando a seed - Pode alterar para srand(42); se quiser resultados sempre idênticos 
srand(time(NULL)); 

// Gera os números aleatórios e preenche APENAS o vetor original
for(int i = 0; i < qtd; i++){ vetor_original[i] = rand() % 1000001; 
                            }

clock_t inicio, fim; 

// ========================================== // 1. TESTES: CATEGORIA O(n^2) // ==========================================

// BUBBLE SORT 
copiarVetor(vetor_original, vetor_teste, qtd); 
inicio = clock(); 
bubbleSort(vetor_teste, qtd); 
fim = clock();
double tempo_bubble = (double)(fim - inicio) / CLOCKS_PER_SEC;

// INSERTION SORT

copiarVetor(vetor_original, vetor_teste, qtd); 
inicio = clock(); insertionSort(vetor_teste, qtd);
fim = clock(); 
double tempo_insertion = (double)(fim - inicio) / CLOCKS_PER_SEC;

// SELECTION SORT 
copiarVetor(vetor_original, vetor_teste, qtd); 
inicio = clock(); selectionSort(vetor_teste, qtd); 
fim = clock();
double tempo_selection = (double)(fim - inicio) / CLOCKS_PER_SEC; 

// ========================================== // 2. TESTES: CATEGORIA O(n log n) // ========================================== 

// MERGE SORT 
copiarVetor(vetor_original, vetor_teste, qtd);
inicio = clock();
mergeSort(vetor_teste, 0, qtd - 1); 
fim = clock(); 
double tempo_merge = (double)(fim - inicio) / CLOCKS_PER_SEC; 

// QUICK SORT
copiarVetor(vetor_original, vetor_teste, qtd);
inicio = clock();
quickSort(vetor_teste, 0, qtd - 1);
fim = clock();
double tempo_quick = (double)(fim - inicio) / CLOCKS_PER_SEC; 

// HEAP SORT 
copiarVetor(vetor_original, vetor_teste, qtd); 
inicio = clock();
heapSort(vetor_teste, qtd);
fim = clock();
double tempo_heap = (double)(fim - inicio) / CLOCKS_PER_SEC;

// ========================================== // 3. TESTES: CATEGORIA LINEARES // ==========================================

// COUNTING SORT 
copiarVetor(vetor_original, vetor_teste, qtd); 
inicio = clock();
countingSort(vetor_teste, qtd);
fim = clock();
double tempo_counting = (double)(fim - inicio) / CLOCKS_PER_SEC;

// RADIX SORT 
copiarVetor(vetor_original, vetor_teste, qtd); 
inicio = clock(); 
radixSort(vetor_teste, qtd);
fim = clock();
double tempo_radix = (double)(fim - inicio) / CLOCKS_PER_SEC;

// BUCKET SORT
copiarVetor(vetor_original, vetor_teste, qtd); 
inicio = clock(); 
bucketSort(vetor_teste, qtd);
fim = clock();
double tempo_bucket = (double)(fim - inicio) / CLOCKS_PER_SEC; 

// ========================================== // EXIBIÇÃO DOS RESULTADOS // ========================================== 

printf("\n========================================\n"); 
printf(" COMPARATIVO DE TEMPO DE EXECUCAO\n"); 

printf("========================================\n");
printf("Tamanho N: %d\n\n", qtd);

printf("--- Algoritmos O(n^2) ---\n"); 
printf("Bubble Sort: %.6f segundos\n", tempo_bubble);
printf("Insertion Sort: %.6f segundos\n", tempo_insertion);
printf("Selection Sort: %.6f segundos\n\n", tempo_selection);

printf("--- Algoritmos O(n log n) ---\n"); 
printf("Merge Sort: %.6f segundos\n", tempo_merge);
printf("Quick Sort: %.6f segundos\n", tempo_quick); 
printf("Heap Sort: %.6f segundos\n\n", tempo_heap); 

printf("--- Algoritmos Lineares ---\n");
printf("Counting Sort: %.6f segundos\n", tempo_counting); 
printf("Radix Sort: %.6f segundos\n", tempo_radix); 
printf("Bucket Sort: %.6f segundos\n");

printf("========================================\n");

// Limpeza de memória 
free(vetor_original); 
free(vetor_teste);
  
  return 0; 
} 

// ========================================== // IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES // ========================================== 

void copiarVetor(int *origem, int *destino, int n) {
  for(int i = 0; i < n; i++){
    destino[i] = origem[i];
  }
} 

void troca(int *a, int *b) { 
  int temp = *a; 
  *a = *b;
  *b = temp; 
}

// ========================================== // IMPLEMENTAÇÃO DOS ALGORITMOS O(n^2) // ==========================================

void bubbleSort(int *arr, int n) {
  for(int i = 0; i < n - 1; i++){ 
    for(int j = 0; j < n - 1 - i; j++){
      if(arr[j] > arr[j + 1]){
        troca(&arr[j], &arr[j + 1]); 
      } 
    }
  }
} 

void insertionSort(int *arr, int n) {
  for(int i = 1; i < n; i++){
    int chave = arr[i];
    int j = i - 1;
    while(j >= 0 && arr[j] > chave){ 
      arr[j + 1] = arr[j];
      j--; 
    } 
    arr[j + 1] = chave;
  }
} 

void selectionSort(int *arr, int n) {
  for(int i = 0; i < n - 1; i++){ 
    int min_idx = i;
    for(int j = i + 1; j < n; j++){
      if(arr[j] < arr[min_idx]){
        min_idx = j;
      } 
    } 
    if(min_idx != i){
      troca(&arr[i], &arr[min_idx]);
    } 
  }
} 

// ========================================== // IMPLEMENTAÇÃO DOS ALGORITMOS O(n log n) // ========================================== 

// MERGE SORT 
void merge(int *arr, int l, int m, int r) { 
  int n1 = m - l + 1; 
  int n2 = r - m; 
  
  int *L = (int *)malloc(n1 * sizeof(int)); 
  int *R = (int *)malloc(n2 * sizeof(int)); 
  
  for(int i = 0; i < n1; i++) L[i] = arr[l + i]; 
  for(int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
  
  int i = 0, j = 0, k = l; 
  while(i < n1 && j < n2) {
    if(L[i] <= R[j]) { 
      arr[k] = L[i]; 
      i++;
    } else {
      arr[k] = R[j];
      j++; 
    } 
    k++; 
  }
  
  while(i < n1) { arr[k] = L[i]; i++; k++; }
  while(j < n2) { arr[k] = R[j]; j++; k++; } 
  
  free(L); 
  free(R);
} 

void mergeSort(int *arr, int l, int r) {
  if(l < r) { 
    int m = l + (r - l) / 2; 
    mergeSort(arr, l, m); 
    mergeSort(arr, m + 1, r); 
    merge(arr, l, m, r); 
  } 
} 

// QUICK SORT 
int partition(int *arr, int low, int high) { 
  int pivot = arr[high]; 
  int i = (low - 1);
  
  for(int j = low; j <= high - 1; j++) { 
    if(arr[j] < pivot) {
      i++;
      troca(&arr[i], &arr[j]);
    }
  } 
  troca(&arr[i + 1], &arr[high]);
  return (i + 1); 
}

void quickSort(int *arr, int low, int high) { 
  if(low < high) {
    int pi = partition(arr, low, high); 
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  } 
}

// HEAP SORT 
void heapify(int *arr, int n, int i) {
  int largest = i; 
  int l = 2 * i + 1; 
  int r = 2 * i + 2; 
  
  if(l < n && arr[l] > arr[largest]) largest = l; 
  
  if(r < n && arr[r] > arr[largest]) largest = r;
  
  if(largest != i) { troca(&arr[i], &arr[largest]); heapify(arr, n, largest);
  }   
}

void heapSort(int *arr, int n) {
  for(int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i); 
  
  for(int i = n - 1; i > 0; i--) {
    troca(&arr[0], &arr[i]);
    heapify(arr, i, 0);
  } 
}

// ========================================== // IMPLEMENTAÇÃO DOS ALGORITMOS LINEARES // ==========================================

// COUNTING SORT 
void countingSort(int *arr, int n) {
  if (n <= 0) return; 
  int max = arr[0];
  for (int i = 1; i < n; i++) {
    if (arr[i] > max) max = arr[i]; 
  }
  
  int *count = (int *)calloc((max + 1), sizeof(int));
  int *output = (int *)malloc(n * sizeof(int));
  
  for (int i = 0; i < n; i++) count[arr[i]]++;
  for (int i = 1; i <= max; i++) count[i] += count[i - 1];
  for (int i = n - 1; i >= 0; i--) { output[count[arr[i]] - 1] = arr[i]; count[arr[i]]--;
                                   }
                                    for (int i = 0; i < n; i++) arr[i] = output[i];
 
  free(count); 
  free(output); 
}

// Sub-rotina Counting Sort para o Radix Sort
void countingSortForRadix(int *arr, int n, int exp) {
  int *output = (int *)malloc(n * sizeof(int));
  int count[10] = {0};
  
  for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
  for (int i = 1; i < 10; i++) count[i] += count[i - 1];
  for (int i = n - 1; i >= 0; i--) { output[count[(arr[i] / exp) % 10] - 1] = arr[i]; 
                                    count[(arr[i] / exp) % 10]--;
                                   }
  for (int i = 0; i < n; i++) arr[i] = output[i]; 
  
  free(output);
}

// RADIX SORT
void radixSort(int *arr, int n) {
  if (n <= 0) return; 
  int max = arr[0]; 
  for (int i = 1; i < n; i++) {
    if (arr[i] > max) max = arr[i];
  }
  
  for (int exp = 1; max / exp > 0; exp *= 10) { 
    countingSortForRadix(arr, n, exp);
  }
}

// BUCKET SORT (Com listas encadeadas)
void bucketSort(int *arr, int n) { 
  if (n <= 0) return;
  
  int max = arr[0]; 
  for (int i = 1; i < n; i++) { 
    if (arr[i] > max) max = arr[i]; 
  }
  if (max == 0) return;
  
  Node** buckets = (Node**)calloc(n, sizeof(Node*));
  
  for (int i = 0; i < n; i++) { 
    int bi = (int)(((long long)arr[i] * n) / (max + 1));
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = arr[i];
    newNode->next = NULL; 
    
    if (buckets[bi] == NULL || buckets[bi]->data >= arr[i]) {
      newNode->next = buckets[bi]; 
      buckets[bi] = newNode;
    } else { 
      Node* current = buckets[bi]; 
      while (current->next != NULL && current->next->data < arr[i]) { 
        current = current->next; 
      }
      newNode->next = current->next;
      current->next = newNode; 
    } 
  } 
  
  int idx = 0;
  for (int i = 0; i < n; i++) { 
    Node* current = buckets[i];
    while (current != NULL) {
      arr[idx++] = current->data;
      Node* temp = current; 
      current = current->next; 
      free(temp);
    } 
  } 
  
  free(buckets); 
}
