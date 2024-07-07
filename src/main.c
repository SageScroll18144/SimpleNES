#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "find_game.h"
#include "menu.h"

int main(void) {
    
    char * name_file = (char *) malloc(50 * sizeof(char));
    if(name_file == NULL){
        printf(" * Erro ao alocar memória *\n");
        exit(1);
    }

    bool flag_operation = true;
    int state = 0;
    
    while(flag_operation){
        switch (state) {
            case 0:
                if(menu_screen() != -1) state = 1;
                else flag_operation = false;
                break;
            case 1:
                const int screenWidth = 800;
                const int screenHeight = 600;
                InitWindow(screenWidth, screenHeight, "Lis of files");
                list_files(screenWidth, screenHeight, &name_file);
                printf("%s\n", name_file);
                CloseWindow();
                state = 2;
                break;
            case 2:
                char command[255];
                sprintf(command, "%s%s", "./../build/SimpleNES ../games/", name_file);
                system(command);
                printf("%s\n", name_file);
                state = 0;
                break;
        }
    }
        
    return 0;
}
