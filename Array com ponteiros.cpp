#include <iostream>

int main() {
    // Tamanho do array
    int tamanho = 5;

    // Alocar um array de inteiros
    int *array = new int[tamanho];

    // Imprimir os endereços dos ponteiros
    for (int i = 0; i < tamanho; i++) {
        std::cout << "Endereco de array[" << i << "] = " << &array[i] << std::endl;
    }

    // Liberar a memória alocada para o array
    delete[] array;

    return 0;
