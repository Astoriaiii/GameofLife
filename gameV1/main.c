#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>


int row=0;
int col=0;
int ** mapInit;
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 640;
const char* WINDOW_TITLE = "GameofLife";


int countCol(char *filename){
    FILE* fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Fail to open file.");
    }
    //printf("1");
    while (fgetc(fp) !='\n'){
        col++;
    }
    //printf("1");
    fclose(fp);
    //printf("1");
    //printf("%d", col);
    return col;
}

int countRow(char *filename){
    FILE* fp = fopen(filename,"r");
    if (fp == NULL){
        printf("Fail to open file.");
    }
    char c;
    while ((c =fgetc(fp))!=EOF){
        if(c=='\n'){
            row++;
        }
    }
    fclose(fp);
    //printf("%d", row);
    return row;
}

int** readfile(char *filename){
//    printf("1");
    int i, j;
//    printf("2");
    mapInit = (int**)malloc(sizeof(int*) * row);
    for (i=0; i<col; i++){
        mapInit[i] = (int*)malloc(sizeof(int) * col);
    }
//    printf("3");

    //assign storage allocation for map
    FILE *fp = fopen(filename,"r");
    if(fp == NULL){
        printf("fail to read file.\n");
        exit(0);
    }
//    printf("4");
    printf("row: %d, column: %d\n", row, col);
    for (i=0; i<row; i++){
        for (j=0; j<col; j++){
//            printf("5");
//            printf("6");
//            printf("\n000%d000\n", mapInit[i][j]);
            mapInit[i][j] = (int)(fgetc(fp)-'0');
//            printf("1");
        }
        fgetc(fp);
        //fscanf(fp,"\n");
    }
    /*for (i=0; i<row; i++){
        for (j=0; j<col; j++){
//            printf("1");
            printf("%d", mapInit[i][j]);
        }
        //fscanf(fp,"\n");
        printf("\n");
    }*/
    fclose(fp);
//    printf(mapInit);
    return mapInit;
}

int** game(int **map){
    int i, j;
    int flag;
    //assign storage allocation for map
    map = (int**)malloc(sizeof(int*) * (row+1));
    for (i=0; i<row+1; i++){
        map[i] = (int*)malloc(sizeof(int) * (col+1));
    }//printf("1");
    for (i=0; i<row; i++){
        //printf("2");
        for (j=0; j<col; j++){
            //printf("3");
            //printf("4");
            //int flag;

            if (i == 0 && j == 0){
                flag = mapInit[i][j+1] + mapInit[i+1][j] + mapInit[i+1][j+1];
            }
            if (i == row-1 && j == 0){
                flag = mapInit[i][j+1] + mapInit[i-1][j] + mapInit[i-1][j+1];
            }
            if (i == 0 && j == col-1){
                flag = mapInit[i][j-1] + mapInit[i+1][j] + mapInit[i+1][j-1];
            }
            if (i == row-1 && j == col-1){
                flag = mapInit[i][j-1] + mapInit[i-1][j] + mapInit[i-1][j-1];
            }
            if (j == 0 && i>=1 && i+1<=row-1){
                flag = mapInit[i-1][j] + mapInit[i+1][j] + mapInit[i][j+1] + mapInit[i-1][j+1] + mapInit[i+1][j+1];
            }
            if (j == col-1 && i>=1 && i<=row-2){
                flag = mapInit[i-1][j] + mapInit[i+1][j] + mapInit[i][j-1] + mapInit[i-1][j-1] + mapInit[i+1][j-1];
            }
            if (i == 0 && j-1>=0 && j+1<=col-1){
                flag = mapInit[i][j+1] + mapInit[i][j-1] + mapInit[i+1][j] + mapInit[i+1][j+1] + mapInit[i+1][j-1];
            }
            if (i == row-1 && j-1>=0 && j+1<=col-1){
                flag = mapInit[i][j+1] + mapInit[i][j-1] + mapInit[i-1][j] + mapInit[i-1][j-1] + mapInit[i-1][j+1];
            }
            if (i-1>=0 && i+1<=row-1 && j-1>=0 && j-1<=col-1){
                flag =(mapInit[i - 1][j - 1] + mapInit[i - 1][j] + mapInit[i - 1][j + 1] + mapInit[i][j - 1] +
                           mapInit[i][j + 1] + mapInit[i + 1][j - 1] + mapInit[i + 1][j] + mapInit[i + 1][j + 1]);
            }
            printf("%d\n", flag);
            //printf("5");
            if (mapInit[i][j] == 1){
                switch(flag){
                    case 0:{
                        map[i][j] = mapInit[i][j];
                        break;
                    }
                    case 1:{
                        map[i][j] = 0;
                        break;
                    }
                    case 2:{
                        map[i][j] = mapInit[i][j];
                        break;
                    }
                    case 3:{
                        map[i][j] = 1;
                        break;
                    }
                    case 4:{
                        map[i][j] = mapInit[i][j];
                        break;
                    }
                    case 5:{
                        map[i][j] = mapInit[i][j];
                        break;
                    }
                    case 6:{
                        map[i][j] = mapInit[i][j];
                        break;
                    }
                    case 7:{
                        map[i][j] = mapInit[i][j];
                        break;
                    }
                    case 8:{
                        map[i][j] = 0;
                        break;
                    }
                }
            }
            //printf("6");
            else{
                //printf("7");
                if (flag == 3){
                    map[i][j] = 1;
                }
                else{
                    map[i][j] = 0;
                }
                //printf("8");
            }
            //printf("9");
        }
        //printf("1");
    }
    return map;
}

int writefile(char *filename){
    //int **a;
    int i, j;
    FILE *fp = fopen(filename,"w");
    if (fp == NULL){
        printf("fail to open file");
        return -1;
    }
    for (i=0; i<row; i++){
        for (j=0; j<col; j++){
            fprintf(fp, "%d", mapInit[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    return 0;
}

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
    surface = SDL_GetWindowSurface(window);
    if(surface == NULL){
        printf("Error! Unable to get surface!");
        return -1;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    //SDL_RenderClear(renderer);
    for (i=0; i<row; i++){
        for (j=0; j<row; j++){
            SDL_Rect rect = {j*unit, i*unit, unit, unit};
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);

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
    printf("%d\n", round);


    if(round < 0){
        while(1){
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
        }
    }
    else{
        if (round != 0){
            while(1){
                mapInit = game(mapInit);
                round --;
                if(round == 0){
                    break;
                }
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
    return 0;


}