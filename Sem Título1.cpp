#include <stdio.h>

int main() {
    int varint;
    scanf("%d", &varint);
    printf("Endereco de varint: %p", &varint);
    return 0;
}


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
}

#include <stdio.h>

int main() {
    char* string = "   Teste ";
    
    // Loop para ignorar espaços em branco no início da string
    for ( ; *string == ' '; string++);
    
    // Imprimir os caracteres após os espaços em branco
    while (*string != '\0') {
        putchar(*string);
        string++;
    }
    
    return 0;
}
