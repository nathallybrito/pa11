#include "../include/indice.hpp"

int main() {
    char palavra[MAXPALAVRA];
    int pagina;
    Palavra *raiz = nullptr;

    while (std::cin >> palavra >> pagina) {
        raiz = inserir_palavra(raiz, palavra, pagina);
    }

    imprimir_palavras_e_paginas(raiz);

    return 0;
}
