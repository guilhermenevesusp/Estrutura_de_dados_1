#include "editor.h"

Lista* criar_lista(void) {
    Lista *L = (Lista*) malloc(sizeof(Lista));
    if (L != NULL) {
        L->inicio = NULL;
        L->fim = NULL;
        L->cursor = NULL;
        L->tamanho = 0;
    }
    return L;
}

void destruir_lista(Lista **L_ref) {
    if (L_ref == NULL || *L_ref == NULL) return;
    Lista *L = *L_ref;
    No *atual = L->inicio;
    while (atual != NULL) {
        No *aux = atual;
        atual = atual->prox;
        free(aux);
    }
    free(L);
    *L_ref = NULL;
}

static No* criar_no(const char *palavra) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo != NULL) {
        strncpy(novo->palavra, palavra, TAM_MAX_PALAVRA - 1);
        novo->palavra[TAM_MAX_PALAVRA - 1] = '\0';
        novo->ant = NULL;
        novo->prox = NULL;
    }
    return novo;
}

void inserir_inicio(Lista *L, const char *palavra) {
    if (L == NULL) return;
    No *novo = criar_no(palavra);
    if (novo == NULL) return;

    if (L->inicio == NULL) {
        L->inicio = novo;
        L->fim = novo;
    } else {
        novo->prox = L->inicio;
        L->inicio->ant = novo;
        L->inicio = novo;
    }
    L->cursor = novo;
    L->tamanho++;
}

void inserir_fim(Lista *L, const char *palavra) {
    if (L == NULL) return;
    No *novo = criar_no(palavra);
    if (novo == NULL) return;

    if (L->fim == NULL) {
        L->inicio = novo;
        L->fim = novo;
    } else {
        L->fim->prox = novo;
        novo->ant = L->fim;
        L->fim = novo;
    }
    L->cursor = novo;
    L->tamanho++;
}

void inserir_antes(Lista *L, const char *palavra) {
    if (L == NULL) return;
    if (L->cursor == NULL || L->cursor == L->inicio) {
        inserir_inicio(L, palavra);
        return;
    }
    No *novo = criar_no(palavra);
    if (novo == NULL) return;

    novo->prox = L->cursor;
    novo->ant = L->cursor->ant;
    L->cursor->ant->prox = novo;
    L->cursor->ant = novo;

    L->cursor = novo;
    L->tamanho++;
}

void inserir_depois(Lista *L, const char *palavra) {
    if (L == NULL) return;
    if (L->cursor == NULL || L->cursor == L->fim) {
        inserir_fim(L, palavra);
        return;
    }
    No *novo = criar_no(palavra);
    if (novo == NULL) return;

    novo->ant = L->cursor;
    novo->prox = L->cursor->prox;
    L->cursor->prox->ant = novo;
    L->cursor->prox = novo;

    L->cursor = novo;
    L->tamanho++;
}

void buscar_palavra(Lista *L, const char *palavra) {
    if (L == NULL || L->cursor == NULL) return;
    No *p = L->cursor;
    while (p != NULL) {
        if (strcmp(p->palavra, palavra) == 0) {
            L->cursor = p;
            return;
        }
        p = p->prox;
    }
}

void trocar_palavra(Lista *L, const char *nova_palavra) {
    if (L == NULL || L->cursor == NULL) return;
    strncpy(L->cursor->palavra, nova_palavra, TAM_MAX_PALAVRA - 1);
    L->cursor->palavra[TAM_MAX_PALAVRA - 1] = '\0';
}

void remover_atual(Lista *L) {
    if (L == NULL || L->cursor == NULL) return;

    No *rem = L->cursor;
    No *ant = rem->ant;
    No *prox = rem->prox;

    if (ant != NULL) {
        ant->prox = prox;
    } else {
        L->inicio = prox;
    }

    if (prox != NULL) {
        prox->ant = ant;
    } else {
        L->fim = ant;
    }

    if (ant != NULL) {
        L->cursor = ant;
    } else {
        L->cursor = L->inicio;
    }

    free(rem);
    L->tamanho--;
}

void mover_cursor(Lista *L, const char *opcao) {
    if (L == NULL) return;
    if (strcmp(opcao, "inicio") == 0) {
        L->cursor = L->inicio;
    } else if (strcmp(opcao, "fim") == 0) {
        L->cursor = L->fim;
    } else if (strcmp(opcao, "prox") == 0) {
        if (L->cursor != NULL && L->cursor->prox != NULL) {
            L->cursor = L->cursor->prox;
        }
    } else if (strcmp(opcao, "ant") == 0) {
        if (L->cursor != NULL && L->cursor->ant != NULL) {
            L->cursor = L->cursor->ant;
        }
    }
}

void listar(Lista *L, const char *opcao) {
    if (L == NULL) return;

    if (strcmp(opcao, "texto") == 0) {
        No *p = L->inicio;
        while (p != NULL) {
            printf("%s%s", p->palavra, (p->prox != NULL) ? " " : "");
            p = p->prox;
        }
        printf("\n");
    } else if (strcmp(opcao, "cursor") == 0) {
        if (L->cursor == NULL) return;

        No *inicio_janela = L->cursor;
        int i = 0;
        while (inicio_janela->ant != NULL && i < 5) {
            inicio_janela = inicio_janela->ant;
            i++;
        }

        No *fim_janela = L->cursor;
        int j = 0;
        while (fim_janela->prox != NULL && j < 5) {
            fim_janela = fim_janela->prox;
            j++;
        }

        No *p = inicio_janela;
        while (p != NULL) {
            printf("%s%s", p->palavra, (p != fim_janela) ? " " : "");
            if (p == fim_janela) break;
            p = p->prox;
        }
        printf("\n");
    } else if (strcmp(opcao, "palavra") == 0) {
        if (L->cursor != NULL) {
            printf("%s\n", L->cursor->palavra);
        }
    }
}

void estatisticas(Lista *L) {
    if (L != NULL) {
        printf("%d\n", L->tamanho);
    }
}

void carregar_arquivo(Lista *L, const char *nome_arquivo) {
    if (L == NULL) return;
    FILE *f = fopen(nome_arquivo, "r");
    if (f == NULL) return; 

    char temp[100];
    while (fscanf(f, "%99s", temp) == 1) {
        if (strcmp(temp, "FIM") == 0) break;
        inserir_fim(L, temp);
    }
    fclose(f);

    L->cursor = L->inicio;
}

void salvar_arquivo(Lista *L, const char *nome_arquivo) {
    if (L == NULL) return;
    FILE *f = fopen(nome_arquivo, "w");
    if (f == NULL) return;

    No *p = L->inicio;
    while (p != NULL) {
        fprintf(f, "%s%s", p->palavra, (p->prox != NULL) ? " " : "");
        p = p->prox;
    }
    fprintf(f, "\n");
    fclose(f);
}