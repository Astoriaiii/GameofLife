#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "game.h"


int row=0;
int col=0;
int ** mapInit;
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 640;
const char* WINDOW_TITLE = "GameofLife";



int main(int argc, char *argv[]) {
    int i, j;
    char str[10];
    SDL_Window *window = NULL;
    SDL_Surface *surface = NULL;
    SDL_Renderer *renderer;

    char filename[20];
    strcpy(filename, argv[1]);
    //col = countCol(filename);
    //row = countRow(filename);
    //int unit = 640 / row;


    if (argc != 2) {
        printf("Error! Please input again!");
        exit(0);
    }

    //decide play mode
    char mode[5];
    printf("please choose the initialize mode you want.\n");
    printf("(If by CLICKING, then choose A. If by READING FILE, then directly choose B):");
    scanf("%s", mode);
    //printf("%s", mode);
    if ((strcmp(mode, "A") != 0) && (strcmp(mode, "a") != 0) && (strcmp(mode, "B") != 0) && (strcmp(mode, "b") != 0)) {
        printf("Error! wrong input for play mode!");
        exit(0);
    }
    //into mode A
    if ((strcmp(mode, "A") == 0) || (strcmp(mode, "a") == 0)) {
        printf("Please input the size of the game\n");
        printf("(Only 1 integer, which represent the length of the square):");
        char size[5];
        scanf("%s", size);
        char tmp[5];
        row = atoi(size);
        itoa(row, tmp, 10);
        if (strcmp(size, tmp) != 0) {
            printf("Error! Please input a integer!");
            exit(0);
        }
        if(row<=0){
            printf("Error! Please input a positive integer!");
            exit(0);
        }
        //printf("%d", row);
        int unit = 640 / row;

        //malloc storage for mapInit
        mapInit = (int **) malloc(sizeof(int *) * row);
        for (i = 0; i < row; i++) {
            mapInit[i] = (int *) malloc(sizeof(int) * row);
        }

        for (i = 0; i < row; i++) {
            for (j = 0; j < row; j++) {
                mapInit[i][j] = 0;
            }
        }

        //printf("\n1");

        //create SDL window
        SDL_Init(SDL_INIT_VIDEO);
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("Error! SDL unable to initialize! %s", SDL_GetError());
            return -1;
        }

        window = SDL_CreateWindow("GameofLife",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  WINDOW_WIDTH, WINDOW_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Error! Unable to get window!");
            return -1;
        }
        SDL_ShowWindow(window);
        surface = SDL_GetWindowSurface(window);
        if (surface == NULL) {
            printf("Error! Unable to get surface!");
            return -1;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);


        SDL_Event event;
        while (SDL_WaitEvent(&event)) {
            switch (event.type) {
                //draw rectangle
                default: {
                    for (i = 0; i < row; i++) {
                        for (j = 0; j < row; j++) {
                            SDL_Rect rect = {j * unit, i * unit, unit, unit};
                            SDL_SetRenderDrawColor(renderer, 105, 105, 105, SDL_ALPHA_OPAQUE);
                            SDL_RenderDrawRect(renderer, &rect);
                        }
                    }
                    SDL_RenderPresent(renderer);
                    break;
                }
                //realize click initialize
                case SDL_MOUSEBUTTONUP: {
                    int x = 0, y = 0;
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        x = event.motion.x;
                        y = event.motion.y;
                        int a = y / unit;
                        int b = x / unit;
                        if (mapInit[a][b] == 0) {
                            mapInit[a][b] = 1;
                        } else {
                            mapInit[a][b] = 0;
                        }
                        for (i = 0; i < row; i++) {
                            for (j = 0; j < row; j++) {
                                SDL_Rect rect = {j * unit, i * unit, unit, unit};
                                //SDL_RenderDrawRect(renderer, &rect);
                                if (mapInit[i][j] == 1) {
                                    SDL_SetRenderDrawColor(renderer, 105, 105, 105, SDL_ALPHA_OPAQUE);
                                    SDL_RenderDrawRect(renderer, &rect);
                                    //SDL_RenderClear(renderer);
                                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                                    SDL_RenderFillRect(renderer, &rect);
                                }
                                SDL_SetRenderDrawColor(renderer, 105, 105, 105, SDL_ALPHA_OPAQUE);
                                SDL_RenderDrawRect(renderer, &rect);
                                //printf("%d",mapInit[i][j]);
                            }
                            //printf("\n");
                        }
                        SDL_RenderPresent(renderer);
                        //writefile(filename);
                        break;
                    }
                }
                //click to close window
                case SDL_QUIT: {
                    SDL_Quit();
                    break;
                }
            }
        }
        printf("Initialize successfully! Now please restart and move to mode B. Thank you for your corporation!");
        writefile(filename);
        //exit(0);
    }
    /*for (i = 0; i < row; i++) {
        for (j = 0; j < row; j++) {
            printf("%d", mapInit[i][j]);
        }
        printf("\n");
    }
    writefile(filename);*/



    if ((strcmp(mode, "B") == 0) || (strcmp(mode, "b") == 0)) {
        col = countCol(filename);
        row = countRow(filename);
        int unit = 640 / row;
        printf("Please input the rounds you want to play \n (if you input negative integer, the game will evolves till it is stable):");
        scanf("%s", str);
        int round = atoi(str);
        char strtmp[5];
        itoa(round, strtmp, 10);
        if (strcmp(str, strtmp) != 0) {
            printf("Error! Please input a integer!");
        }

        //Initialze map from file
        mapInit = readfile(filename);
        SDL_Init(SDL_INIT_VIDEO);
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("Error! SDL unable to initialize! %s", SDL_GetError());
            return -1;
        }

        //create window
        window = SDL_CreateWindow("GameofLife",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  WINDOW_WIDTH, WINDOW_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Error! Unable to get window!");
            return -1;
        }
        SDL_ShowWindow(window);
        surface = SDL_GetWindowSurface(window);
        if (surface == NULL) {
            printf("Error! Unable to get surface!");
            return -1;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        //printf("%d\n", round);

        SDL_Event event;
        //run game till stable
        if (round < 0) {
            while (SDL_WaitEvent(&event)) {
                switch (event.type) {
                    default: {
                        int **map;
                        map = (int **) malloc(sizeof(int *) * (row + 1));
                        for (i = 0; i < row + 1; i++) {
                            map[i] = (int *) malloc(sizeof(int) * (col + 1));
                        }//printf("1");
                        for (i = 0; i < row; i++) {
                            for (j = 0; j < row; j++) {
                                map[i][j] = mapInit[i][j];
                            }
                        }
                        mapInit = game(mapInit);
                        int same = 0;
                        for (i = 0; i < row; i++) {
                            for (j = 0; j < row; j++) {
                                if (map[i][j] == mapInit[i][j]) {
                                    same += 1;
                                }
                            }
                        }
                        if (same == row * row) {
                            printf("The game reaches stable and will end if you click.\n");
                            //SDL_RenderPresent(renderer);
                            //break;
                        }
                        for (i = 0; i < row; i++) {
                            for (j = 0; j < row; j++) {
                                SDL_Rect rect = {j * unit, i * unit, unit, unit};
                                //SDL_RenderDrawRect(renderer, &rect);
                                if (mapInit[i][j] == 1) {
                                    SDL_SetRenderDrawColor(renderer, 105, 105, 105, SDL_ALPHA_OPAQUE);
                                    SDL_RenderDrawRect(renderer, &rect);
                                    //SDL_RenderClear(renderer);
                                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                                    SDL_RenderFillRect(renderer, &rect);
                                }
                                else{
                                    SDL_SetRenderDrawColor(renderer, 105, 105, 105, SDL_ALPHA_OPAQUE);
                                    SDL_RenderDrawRect(renderer, &rect);
                                    //SDL_RenderClear(renderer);
                                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                                    SDL_RenderFillRect(renderer, &rect);
                                }
                                SDL_SetRenderDrawColor(renderer, 105, 105, 105, SDL_ALPHA_OPAQUE);
                                SDL_RenderDrawRect(renderer, &rect);
                            }
                        }
                        SDL_RenderPresent(renderer);
                        //SDL_RenderClear(renderer);

                        /*for (i = 0; i < row; i++) {
                            for (j = 0; j < col; j++) {
                                printf("%d", mapInit[i][j]);
                            }
                            printf("\n");
                        }*/

                        /*int same = 0;
                        for (i = 0; i < row; i++) {
                            for (j = 0; j < row; j++) {
                                if (map[i][j] == mapInit[i][j]) {
                                    same += 1;
                                }
                            }
                        }
                        if (same == row * row) {
                            printf("The game reaches stable and will end if you click.\n");
                            //SDL_RenderPresent(renderer);
                            //break;
                        }*/
                        break;
                    }
                    case SDL_QUIT:
                        SDL_Quit();
                        break;
                }
            }
        }
        //run game from customer input
        else {
            while (SDL_WaitEvent(&event)) {
                switch (event.type) {
                    default: {
                        while (round) {
                            mapInit = game(mapInit);
                            for (i = 0; i < row; i++) {
                                for (j = 0; j < row; j++) {
                                    SDL_Rect rect = {j * unit, i * unit, unit, unit};
                                    //SDL_RenderDrawRect(renderer, &rect);
                                    if (mapInit[i][j] == 1) {
                                        SDL_SetRenderDrawColor(renderer, 105, 105, 105, SDL_ALPHA_OPAQUE);
                                        SDL_RenderDrawRect(renderer, &rect);
                                        //SDL_RenderClear(renderer);
                                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                                        SDL_RenderFillRect(renderer, &rect);
                                    }
                                    else{
                                        SDL_SetRenderDrawColor(renderer, 105, 105, 105, SDL_ALPHA_OPAQUE);
                                        SDL_RenderDrawRect(renderer, &rect);
                                        //SDL_RenderClear(renderer);
                                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                                        SDL_RenderFillRect(renderer, &rect);
                                    }
                                    SDL_SetRenderDrawColor(renderer, 105, 105, 105, SDL_ALPHA_OPAQUE);
                                    SDL_RenderDrawRect(renderer, &rect);
                                }
                            }
                            SDL_RenderPresent(renderer);
                            //SDL_UpdateWindowSurface(window);

                            round--;
                            if (round == 0) {
                                break;
                            }
                        }
                        break;
                    }
                    case SDL_QUIT:
                        SDL_Quit();
                        break;
                }

            }
        }
        //show the result of game by 0 and 1
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                printf("%d", mapInit[i][j]);
            }
            printf("\n");
        }
        writefile(filename);
        free(mapInit);
        /*SDL_DestroyRenderer(renderer);
        SDL_FreeSurface(surface);
        SDL_DestroyWindow(window);*/
    }

    /*SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);*/
    return 0;

}