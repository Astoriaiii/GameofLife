//
// Created by PC on 2022/5/18.
//
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

//implement the game rules
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
            if (i-1>=0 && i+1<=row-1 && j-1>=0 && j+1<=col-1){
                flag =(mapInit[i - 1][j - 1] + mapInit[i - 1][j] + mapInit[i - 1][j + 1] + mapInit[i][j - 1] +
                       mapInit[i][j + 1] + mapInit[i + 1][j - 1] + mapInit[i + 1][j] + mapInit[i + 1][j + 1]);
            }
            //printf("flag:%d\n", flag);
            //printf("5");
            if (mapInit[i][j] == 1){
                switch(flag){
                    case 0:{
                        map[i][j] = 0;
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
                        map[i][j] = mapInit[i][j];
                        break;
                    }
                    case 4:{
                        map[i][j] = 0;
                        break;
                    }
                    case 5:{
                        map[i][j] = 0;
                        break;
                    }
                    case 6:{
                        map[i][j] = 0;
                        break;
                    }
                    case 7:{
                        map[i][j] = 0;
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
