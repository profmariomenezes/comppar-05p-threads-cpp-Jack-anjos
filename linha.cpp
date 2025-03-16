#include <iostream>
#include <chrono>
#include <functional>

const int thread_count = 4;
const int M=500, N=500, X=500;


void linha(int** matriz_a, int** matriz_b, int** matriz_c){
  for(int i=0; i<M; i++){
    for(int j=0; j<X; j++){
      matriz_c[i][j]=0;
      for(int k=0; k<N;k++){
        matriz_c[i][j] += matriz_a[i][k] * matriz_b[k][j];
      }
    }
  }
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
  linha(matriz_a, matriz_b, matriz_c);
  auto fim = std::chrono::high_resolution_clock::now(); 
  //percorrerMatriz(matriz_c, M, X);
  int tempo_decorrido = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio).count(); // Converte para milissegundos
  std::cout << "\nTempo de execução percorrendo por linha: " << tempo_decorrido << " ms" << std::endl;
}