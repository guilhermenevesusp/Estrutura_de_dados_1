#ifndef EDITOR_H
#define EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM_MAX_PALAVRA 13 

typedef struct _no {
    char palavra[TAM_MAX_PALAVRA];
    struct _no *ant;
    struct _no *prox;
} No;

typedef struct _lista {
    No *inicio;
    No *fim;
    No *cursor;
    int tamanho;
} Lista;

Lista* criar_lista(void);
void destruir_lista(Lista **L_ref);

void inserir_inicio(Lista *L, const char *palavra);
void inserir_fim(Lista *L, const char *palavra);
void inserir_antes(Lista *L, const char *palavra);
void inserir_depois(Lista *L, const char *palavra);

void buscar_palavra(Lista *L, const char *palavra);
void trocar_palavra(Lista *L, const char *nova_palavra);
void remover_atual(Lista *L);

void mover_cursor(Lista *L, const char *opcao);
void listar(Lista *L, const char *opcao);
void estatisticas(Lista *L);

void carregar_arquivo(Lista *L, const char *nome_arquivo);
void salvar_arquivo(Lista *L, const char *nome_arquivo);

#endif 