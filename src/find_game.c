#include "find_game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool was_clicked;

void list_files(const int screenWidth, const int screenHeight, char ** name_file) {
    // Paleta de cores inspirada em Zelda
    Color backgroundColor = (Color){ 34, 139, 34, 255 }; // Verde escuro
    Color textColor = (Color){ 245, 245, 220, 255 };     // Bege
    Color highlightColor = (Color){ 210, 180, 140, 255 }; // Marrom claro

    // Lista de arquivos
    char *files[MAX_FILES];
    int fileCount = 0;

    was_clicked = false;

    // Abre o diretório
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("../games")) != NULL) {
        // Lê os arquivos do diretório
        while ((ent = readdir(dir)) != NULL && fileCount < MAX_FILES) {
            int isDuplicate = 0;
            // Verifica se o arquivo já foi adicionado
            for (int i = 0; i < fileCount; i++) {
                if (strcmp(files[i], ent->d_name) == 0) {
                    isDuplicate = 1;
                    break;
                }
            }
            // Adiciona o arquivo se não for duplicado
            if (!isDuplicate) {
                files[fileCount] = strdup(ent->d_name);
                fileCount++;
            }
        }
        closedir(dir);
    } else {
        // Erro ao abrir o diretório
        printf("Erro ao abrir o diretório\n");
        return;
    }

    SetTargetFPS(60); // Define o FPS alvo

    while (!WindowShouldClose() && !was_clicked) {
        BeginDrawing();
        ClearBackground(backgroundColor);

        // Centraliza e desenha a lista de arquivos
        int startY = (screenHeight - fileCount * 20) / 2;
        for (int i = 0; i < fileCount; i++) {
            int textWidth = MeasureText(files[i], 20);
            int startX = (screenWidth - textWidth) / 2;

            // Detecta clique no nome do arquivo
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, (Rectangle){ startX, startY + 20 * i, textWidth, 20 })) {
                DrawText(files[i], startX, startY + 20 * i, 20, highlightColor);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    printf("Arquivo clicado: %s\n", files[i]);
                    strcpy((*name_file), files[i]);
                    was_clicked = true;
                }
            } else {
                DrawText(files[i], startX, startY + 20 * i, 20, textColor);
            }
        }

        EndDrawing();
    }

    // Libera a memória alocada para os nomes dos arquivos
    for (int i = 0; i < fileCount; i++) {
        free(files[i]);
    }
}
