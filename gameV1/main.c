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
    int i,j;
    char str[10];
    SDL_Window *window = NULL;
    SDL_Surface *surface = NULL;
    SDL_Renderer *renderer;

    char filename[20];
    strcpy(filename, argv[1]);
    col = countCol(filename);
    row = countRow(filename);
    int unit = 640 / row;


    /*SDL_Init(SDL_INIT_VIDEO);
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error! SDL unable to initialize! %s", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("GameofLife",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window ==NULL){
        printf("Error! Unable to get window!");
        return -1;
    }
    surface = SDL_GetWindowSurface(window);
    if(surface == NULL){
        printf("Error! Unable to get surface!");
        return -1;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);*/
    //SDL_ShowWindow(window);
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    //SDL_RenderClear(renderer);
    /*for (i=0; i<row; i++){
        for (j=0; j<row; j++){
            SDL_Rect rect = {j*unit, i*unit, unit, unit};
            SDL_RenderDrawRect(renderer, &rect);
        }
    }*/
    //SDL_RenderPresent(renderer);

    if (argc !=2){
        printf("Error! Please input again!");
        exit(0);
    }
    printf("Please input the rounds you want to play \n (if you input negative integer, the game will evolves till it is stable):");
    scanf("%s", str);
    int round = atoi(str);
    char strtmp[5];
    itoa(round,strtmp,10);
    if(strcmp(str,strtmp) != 0){
        printf("Error! Please input a integer!");
    }

    //initialize the game
    /*char filename[20];
    strcpy(filename, argv[1]);
    col = countCol(filename);
    row = countRow(filename);*/
    mapInit = readfile(filename);
    SDL_Init(SDL_INIT_VIDEO);
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error! SDL unable to initialize! %s", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("GameofLife",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window ==NULL){
        printf("Error! Unable to get window!");
        return -1;
    }
    SDL_ShowWindow(window);
    surface = SDL_GetWindowSurface(window);
    if(surface == NULL){
        printf("Error! Unable to get surface!");
        return -1;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);
    printf("%d\n", round);

    SDL_Event event;
    if(round < 0){
        while(SDL_WaitEvent(&event)){
            switch (event.type) {
                default:{
                    int **map;
                    map = (int**)malloc(sizeof(int*) * (row+1));
                    for (i=0; i<row+1; i++){
                        map[i] = (int*)malloc(sizeof(int) * (col+1));
                    }//printf("1");
                    for(i=0; i<row; i++){
                        for(j=0; j<row; j++){
                            map[i][j] = mapInit[i][j];
                        }
                    }
                    mapInit = game(mapInit);
                    for (i=0; i<row; i++){
                        for (j=0; j<row; j++){
                            SDL_Rect rect = {j*unit, i*unit, unit, unit};
                            //SDL_RenderDrawRect(renderer, &rect);
                            if(mapInit[i][j] == 1){
                                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                                SDL_RenderDrawRect(renderer, &rect);
                                SDL_RenderFillRect(renderer, &rect);
                            }
                            SDL_SetRenderDrawColor(renderer,0, 0, 0, SDL_ALPHA_OPAQUE);
                            SDL_RenderDrawRect(renderer, &rect);
                        }
                    }
                    SDL_RenderPresent(renderer);
                    int same = 0;
                    for(i=0; i<row; i++){
                        for(j=0; j<col; j++){
                            if(map[i][j] == mapInit[i][j]){
                                same += 1;
                            }
                        }
                    }
                    if (same == row * col){
                        printf("The game reaches stable and will end.");
                        break;
                    }
                    break;
                }
                case SDL_QUIT:
                    SDL_Quit();
                    break;
            }

        }
    }
    else {
        while (SDL_WaitEvent(&event)){
            switch (event.type) {
                default:{
                    while(round){
                        mapInit = game(mapInit);
                        for (i=0; i<row; i++){
                            for (j=0; j<row; j++){
                                SDL_Rect rect = {j*unit, i*unit, unit, unit};
                                //SDL_RenderDrawRect(renderer, &rect);
                                if(mapInit[i][j] == 1){
                                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                                    SDL_RenderDrawRect(renderer, &rect);
                                    SDL_RenderFillRect(renderer, &rect);
                                }
                                SDL_SetRenderDrawColor(renderer,0, 0, 0, SDL_ALPHA_OPAQUE);
                                SDL_RenderDrawRect(renderer, &rect);
                            }
                        }
                        SDL_RenderPresent(renderer);
                        round --;
                        if(round == 0){
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

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%d", mapInit[i][j]);
        }
        printf("\n");
    }
    writefile(filename);
    free(mapInit);

    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    return 0;


}