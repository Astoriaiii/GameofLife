#include <stdio.h>
#include <stdlib.h>
int row=0;
int col=0;
int ** mapInit;

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

int main() {
    //countCol("game.txt");
    col = countCol("games.txt");
    row = countRow("games.txt");
    mapInit = readfile("games.txt");



    mapInit = game(mapInit);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d", mapInit[i][j]);
        }
        printf("\n");
    }
    
    free(mapInit);
    return 0;


}