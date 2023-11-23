#include <iostream>
#include <cstring>

#define MAXPALAVRA 10

struct Pagina {
    int pagina_num;
    Pagina *esq;
    Pagina *dir;
    int altura;
};

struct Palavra {
    char palavra[MAXPALAVRA];
    Palavra *esq;
    Palavra *dir;
    int altura;
    Pagina *paginas;
};

int max(int a, int b);

int altura_pag(Pagina *p);

int altura_pal(Palavra *p);

int get_balance_pag(Pagina *p);


int get_balance_pal(Palavra *p);

Pagina *criar_pagina(int pagina_num);

Palavra *criar_palavra(const char *palavra, int pagina_num);

Pagina *rot_esq_pag(Pagina *y);

Pagina *rot_dir_pag(Pagina *x);

Pagina *inserir_pagina(Pagina *pagina_raiz, int pagina_num);

void imprimir_paginas(Pagina *pagina_raiz);

Palavra *inserir_palavra(Palavra *raiz, const char *palavra, int pagina_num);

void atualizar_altura(Palavra *node);

Palavra *balancear(Palavra *node, const char *palavra);


void imprimir_palavras_e_paginas(Palavra *raiz);