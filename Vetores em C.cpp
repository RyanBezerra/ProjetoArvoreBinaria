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