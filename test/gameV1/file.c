//
// Created by PC on 2022/5/18.
//
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

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
