#include <iostream>
#include <chrono>
#include <functional>

const int thread_count = 4;
const int M=500, N=500, X=500;
const int blockSize=500;

void bloco(int** matriz_a, int** matriz_b, int** matriz_c) {
    for (int i = 0; i < M; i += blockSize)
        for (int j = 0; j < X; j += blockSize)
            for (int k = 0; k < N; k += blockSize)

                // Multiplicação dos blocos
                for (int iInner = i; iInner < i + blockSize && iInner < M; iInner++)
                    for (int jInner = j; jInner < j + blockSize && jInner < X; jInner++)
                        for (int kInner = k; kInner < k + blockSize && kInner < N; kInner++)
                            matriz_c[iInner][jInner] += matriz_a[iInner][kInner] * matriz_b[kInner][jInner];
}



int** criaMatriz(int linhas, int colunas){
  int** matriz = new int*[linhas];

  for (int i=0; i< linhas; i++){
    matriz[i] = new int[colunas];
  }
  return matriz;
}

void preencherMatriz(int** matriz, int linhas, int colunas, int seed){
  srand(seed);
  for(int i=0; i<linhas;i++){
    for(int j=0; j<colunas;j++){
      matriz[i][j] = rand()%100;
    }
  }
}

void percorrerMatriz(int** matriz, int linha, int coluna){ // printa a matriz
  for(int i=0;i<linha;i++){
    printf("\n");
    for(int j=0; j<coluna;j++){
        printf("%i ", matriz[i][j]);
    }
  }
}
int main(){
  // cria matrizes
  int** matriz_a = criaMatriz(M, N);
  int** matriz_b = criaMatriz(N, X);
  int** matriz_c = criaMatriz(M, X);

  // preenche duas primeiras matrizes
  preencherMatriz(matriz_a, M, N, 1);
  preencherMatriz(matriz_b, N, X, 2);
  auto inicio = std::chrono::high_resolution_clock::now(); 
  bloco(matriz_a, matriz_b, matriz_c);
  auto fim = std::chrono::high_resolution_clock::now(); 
  //percorrerMatriz(matriz_c, M, X);
  int tempo_decorrido = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio).count(); // Converte para milissegundos
  std::cout << "\nTempo de execução percorrendo por bloco: " << tempo_decorrido << " ms" << std::endl;
}