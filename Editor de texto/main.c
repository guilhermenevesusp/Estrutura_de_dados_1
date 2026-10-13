#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "editor.h"

int main(void) {
    Lista *L = criar_lista();

    carregar_arquivo(L, "texto.txt");

    char cmd[20];
    char arg[50];

    // 2. Loop principal de comandos
    while (scanf("%s %s", cmd, arg) == 2) {
        if (strcmp(cmd, "I") == 0) {
            inserir_inicio(L, arg);
        } else if (strcmp(cmd, "F") == 0) {
            inserir_fim(L, arg);
        } else if (strcmp(cmd, "A") == 0) {
            inserir_antes(L, arg);
        } else if (strcmp(cmd, "D") == 0) {
            inserir_depois(L, arg);
        } else if (strcmp(cmd, "P") == 0) {
            buscar_palavra(L, arg);
        } else if (strcmp(cmd, "T") == 0) {
            trocar_palavra(L, arg);
        } else if (strcmp(cmd, "R") == 0 && strcmp(arg, "atual") == 0) {
            remover_atual(L);
        } else if (strcmp(cmd, "G") == 0) {
            mover_cursor(L, arg);
        } else if (strcmp(cmd, "L") == 0) {
            listar(L, arg);
        } else if (strcmp(cmd, "S") == 0 && strcmp(arg, "texto") == 0) {
            estatisticas(L);
        } else if (strcmp(cmd, "X") == 0 && strcmp(arg, "editor") == 0) {
            salvar_arquivo(L, "texto-ed.txt");
            break;
        }
    }

    destruir_lista(&L);
    return 0;
}