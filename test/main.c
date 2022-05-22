#include <stdio.h>
#include "gameV1/file.c"
#include "gameV1/game.c"
#include "gameV1/game.h"


int passed = 0;
int row=0;
int col=0;
int ** mapInit;


void testCountCol(char *filename){
    col = countCol("test1.txt");
    if (col ==  5){
        printf("-----------------------------");
        printf("countCol() test passed.");
        printf("-----------------------------\n");
        passed++;
    }
    else{
        printf("-----------------------------");
        printf("countCol() test failed.");
        printf("-----------------------------\n");
    }
}

void testCountRow(char *filename){
    row = countRow("test1.txt");
    //printf("%d", row);
    if (row ==  5){
        printf("-----------------------------");
        printf("countRow() test passed.");
        printf("-----------------------------\n");
        passed++;
    }
    else{
        printf("-----------------------------");
        printf("countRow() test failed.");
        printf("-----------------------------\n");
    }
}

void testReadfile(char *filename){
    int i,j;
    int a;
    mapInit = readfile("test1.txt");
    for (i=0; i<5; i++){
        for(j=0; j<5; j++){
            if (mapInit[i][j] == 0){
                a = 1;
            }
            else{
               a = 0;
            }
        }
    }
    if (a==1){
        printf("-----------------------------");
        printf("readfile() test passed.");
        printf("-----------------------------\n");
        passed++;
    }
    else{
        printf("-----------------------------");
        printf("readfile() test failed.");
        printf("-----------------------------\n");
    }
}

void testWritefile(char *filename){
    int i,j;
    int a;
    int **map = (int**)malloc(sizeof(int*) * 5);
    for (i=0; i<5; i++){
        map[i] = (int*)malloc(sizeof(int) * 5);
    }
    for (i=0; i<5; i++){
        for(j=0; j<5; j++){
            map[i][j] = 0;
        }
    }
    writefile("test2.txt");
    mapInit = (int**)malloc(sizeof(int*) * 5);
    for (i=0; i<5; i++){
        mapInit[i] = (int*)malloc(sizeof(int) * 5);
    }
    mapInit = readfile("test2.txt");
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            if (map[i][j] == mapInit[i][j]){
                a = 1;
            }
            else{
                a = 0;
            }
        }
    }
    if(a == 1){
        printf("-----------------------------");
        printf("writefile() test passed.");
        printf("-----------------------------\n");
        passed ++;
    }
    else{
        printf("-----------------------------");
        printf("writefile() test failed.");
        printf("-----------------------------\n");
    }

}

void testGame(){
    int i,j;
    int a;
    int **map = (int**)malloc(sizeof(int*) * 5);
    for (i=0; i<5; i++){
        map[i] = (int*)malloc(sizeof(int) * 5);
    }
    map = readfile("test3.txt");
    int **mapTest = (int**)malloc(sizeof(int*) * 5);
    for (i=0; i<5; i++){
        map[i] = (int*)malloc(sizeof(int) * 5);
    }
    mapTest = readfile("test4.txt");
    mapInit = (int**)malloc(sizeof(int*) * 5);
    for (i=0; i<5; i++){
        mapInit[i] = (int*)malloc(sizeof(int) * 5);
    }
    mapInit = game(map);
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            if (mapInit[i][j] == mapTest[i][j]){
               a = 1;
            }
            else{
                a = 0;
            }
        }
    }
    if(a == 1){
        printf("-----------------------------");
        printf("game() test passed.");
        printf("-----------------------------\n");
        passed ++;
    }
    else{
        printf("-----------------------------");
        printf("game() test failed.");
        printf("-----------------------------\n");
    }
}


int main() {
    testCountCol("test1.txt");
    printf("\n");
    testCountRow("test1.txt");
    printf("\n");
    testReadfile("test1.txt");
    printf("\n");
    testWritefile("test2.txt");
    printf("\n");
    testGame();
    printf("\n");
    printf("The test number which have already passed is %d\n", passed);
    if (passed == 5){
        printf("All test passed");
    }
    return 0;
}
