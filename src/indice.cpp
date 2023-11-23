#include "../include/indice.hpp"

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura_pag(Pagina *p) {
    if (p == nullptr)
        return 0;
    return p->altura;
}

int altura_pal(Palavra *p) {
    if (p == nullptr)
        return 0;
    return p->altura;
}

int get_balance_pag(Pagina *p) {
    if (p == nullptr)
        return 0;
    return altura_pag(p->esq) - altura_pag(p->dir);
}

int get_balance_pal(Palavra *p) {
    if (p == nullptr)
        return 0;
    return altura_pal(p->esq) - altura_pal(p->dir);
}

Pagina *criar_pagina(int pagina_num) {
    Pagina *nova_pagina = new Pagina();
    nova_pagina->pagina_num = pagina_num;
    nova_pagina->esq = nullptr;
    nova_pagina->dir = nullptr;
    nova_pagina->altura = 1;
    return nova_pagina;
}

Palavra *criar_palavra(const char *palavra, int pagina_num) {
    Palavra *nova_palavra = new Palavra();
    strcpy(nova_palavra->palavra, palavra);
    nova_palavra->esq = nullptr;
    nova_palavra->dir = nullptr;
    nova_palavra->altura = 1;
    nova_palavra->paginas = criar_pagina(pagina_num);
    return nova_palavra;
}


Pagina *inserir_pagina(Pagina *pagina_raiz, int pagina_num) {
    if (pagina_raiz == nullptr)
        return criar_pagina(pagina_num);

    if (pagina_num < pagina_raiz->pagina_num)
        pagina_raiz->esq = inserir_pagina(pagina_raiz->esq, pagina_num);
    else if (pagina_num > pagina_raiz->pagina_num)
        pagina_raiz->dir = inserir_pagina(pagina_raiz->dir, pagina_num);
    else // Não permitir páginas duplicadas
        return pagina_raiz;

    pagina_raiz->altura = 1 + max(altura_pag(pagina_raiz->esq), altura_pag(pagina_raiz->dir));

    int balance = get_balance_pag(pagina_raiz);

    if (balance > 1 && pagina_num < pagina_raiz->esq->pagina_num)
        return rot_dir_pag(pagina_raiz);

    if (balance < -1 && pagina_num > pagina_raiz->dir->pagina_num)
        return rot_esq_pag(pagina_raiz);

    if (balance > 1 && pagina_num > pagina_raiz->esq->pagina_num) {
        pagina_raiz->esq = rot_esq_pag(pagina_raiz->esq);
        return rot_dir_pag(pagina_raiz);
    }

    if (balance < -1 && pagina_num < pagina_raiz->dir->pagina_num) {
        pagina_raiz->dir = rot_dir_pag(pagina_raiz->dir);
        return rot_esq_pag(pagina_raiz);
    }

    return pagina_raiz;
}

void imprimir_paginas(Pagina *pagina_raiz) {
    if (pagina_raiz != nullptr) {
        imprimir_paginas(pagina_raiz->esq);
        std::cout << pagina_raiz->pagina_num << " ";
        imprimir_paginas(pagina_raiz->dir);
    }
}

Palavra *inserir_palavra(Palavra *raiz, const char *palavra, int pagina_num) {
    if (raiz == nullptr)
        return criar_palavra(palavra, pagina_num);

    if (strcmp(palavra, raiz->palavra) < 0)
        raiz->esq = inserir_palavra(raiz->esq, palavra, pagina_num);
    else if (strcmp(palavra, raiz->palavra) > 0)
        raiz->dir = inserir_palavra(raiz->dir, palavra, pagina_num);
    else {
        raiz->paginas = inserir_pagina(raiz->paginas, pagina_num);
        return raiz;
    }

    atualizar_altura(raiz);
    return balancear(raiz, palavra);
}

void atualizar_altura(Palavra *node) {
    if (node == nullptr) return;
    node->altura = 1 + max(altura_pal(node->esq), altura_pal(node->dir));
}

Palavra *rot_esq_pag(Palavra *y) {
    Palavra *x = y->dir;
    Palavra *T2 = x->esq;

    x->esq = y;
    y->dir = T2;

    atualizar_altura(y);
    atualizar_altura(x);

    return x;
}

Palavra *rot_dir_pag(Palavra *x) {
    Palavra *y = x->esq;
    Palavra *T2 = y->dir;

    y->dir = x;
    x->esq = T2;

    atualizar_altura(x);
    atualizar_altura(y);

    return y;
}

Palavra *balancear(Palavra *node, const char *palavra) {
    int balance = get_balance_pal(node);

    if (balance > 1 && strcmp(palavra, node->esq->palavra) < 0)
        return rot_dir_pag(node);

    if (balance < -1 && strcmp(palavra, node->dir->palavra) > 0)
        return rot_esq_pag(node);

    if (balance > 1 && strcmp(palavra, node->esq->palavra) > 0) {
        node->esq = rot_esq_pag(node->esq);
        return rot_dir_pag(node);
    }

    if (balance < -1 && strcmp(palavra, node->dir->palavra) < 0) {
        node->dir = rot_dir_pag(node->dir);
        return rot_esq_pag(node);
    }

    return node;
}


void imprimir_palavras_e_paginas(Palavra *raiz) {
    if (raiz != nullptr) {
        imprimir_palavras_e_paginas(raiz->esq);
        std::cout << raiz->palavra << ": ";
        imprimir_paginas(raiz->paginas);
        std::cout << std::endl;
        imprimir_palavras_e_paginas(raiz->dir);
    }
}
