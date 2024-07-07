#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int menu_screen(void){
    // Inicializa a janela
    const int screenWidth = 614;
    const int screenHeight = 642;
    InitWindow(screenWidth, screenHeight, "Emulator SNES");

    // Carrega a textura do cartucho (substitua "snes.png" pelo caminho real)
    Texture2D cartucho = LoadTexture("../imgs/snes.png");

    SetTargetFPS(60);

    // Configurações de texto
    const char *text = "SELECT GAME";
    const int fontSize = 32;
    const int textWidth = MeasureText(text, fontSize); // Mede a largura do texto
    const int textHeight = fontSize;

    // Posição inicial do texto no centro da tela
    Vector2 textPosition = {(screenWidth - textWidth) / 2, (screenHeight - textHeight) / 2};

    // Variáveis para controlar a animação de clique
    bool isClicking = false;
    int clickFrames = 0;
    const int maxClickFrames = 30; // Número máximo de frames para a animação de clique

    // Variáveis para controlar a caixa retangular
    Rectangle boxRect = { screenWidth / 2 - cartucho.width / 2 - 10, screenHeight / 2 - cartucho.height / 2 - 10, cartucho.width + 20, cartucho.height + 20 };
    bool drawBox = false;

    // Variáveis para armazenar a posição do mouse
    Vector2 mousePosition = {0, 0};
    bool mouseClicked = false;

    bool working = true;

    // Loop principal do jogo
    while (!WindowShouldClose() && working) {
        // Processa entrada
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Verifica se o mouse está dentro da área do cartucho
            mousePosition = GetMousePosition();
            if ((abs(textPosition.x - mousePosition.x) < 300) && abs(textPosition.y - mousePosition.y) < 30)  {
                drawBox = true;
                mouseClicked = true;
                isClicking = true;
                clickFrames = 0;
                printf("Mouse clicado na posição: (%.0f, %.0f)\n", mousePosition.x, mousePosition.y);
            } else {
                mouseClicked = false;
            }
        }

        if (isClicking) {
            clickFrames++;
            if (clickFrames > maxClickFrames)
            {
                isClicking = false;
            }
        }

        // Desenha
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenha a caixa retangular translúcida ao redor do cartucho
        if (drawBox) {
            DrawRectangleRec(boxRect, Fade(SKYBLUE, 0.5f));
        }

        // Desenha o cartucho no centro da tela
        DrawTexture(cartucho, screenWidth / 2 - cartucho.width / 2, screenHeight / 2 - cartucho.height / 2, WHITE);

        // Desenha o texto no centro da tela
        if (!isClicking) {
            DrawText(text, textPosition.x, textPosition.y, fontSize, BLACK);
        }
        else {
            // Animação de clique (exemplo simples: muda a cor do texto)
            Color textColor = (clickFrames % 2 == 0) ? RED : BLACK;
            DrawText(text, textPosition.x, textPosition.y, fontSize, textColor);
        }

        // Desenha a posição do mouse quando clicado
        if (mouseClicked) {
            char mousePosText[50];
            sprintf(mousePosText, "Mouse: (%.0f, %.0f)", mousePosition.x, mousePosition.y);
            DrawText(mousePosText, 10, 10, 20, RED);

            working = false;
        }

        EndDrawing();
    }

    // Descarrega recursos
    UnloadTexture(cartucho);

    CloseWindow();

    if(working == true) return -1;
    else return 1;
}
