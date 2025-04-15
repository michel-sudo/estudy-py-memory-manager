#include <string.h>
#include <stdio.h>

// Função vulneravel a buffer overflow
void bufferOverflow() {
    char str[] = "Mundo";
    char buffer[3];
    
    printf("vetor antes: %s\n", str); // Saída: "Mundo"
    printf("buffer antes: %s\n", buffer); // Saída: ""
    
    strcpy(buffer, str); // É feito a cópia do conteúsdo do vetor str para o vetor buffer
    
    printf("vetor depois: %s\n", str); // Saída: "do"
    printf("buffer depois: %s\n", buffer); // Saída: "Mundo"

}

int main() {
    bufferOverflow();
    return 0;
}
