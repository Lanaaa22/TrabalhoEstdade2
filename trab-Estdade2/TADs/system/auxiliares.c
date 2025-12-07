#include "auxiliares.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Função para limpar tela para Windows, Linux ou MacOS
void LimpaTela() {
    #ifdef _WIN32
        system("cls"); // Para Windows
    #else
        system("clear"); // Para Linux e macOS
    #endif
}
