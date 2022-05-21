#include <stdio.h>
#include "../gameV1/file.c"
#include "../gameV1/game.c"
#include "../gameV1/game.h"


int passed = 0;

void testCountCol(char *filename){
    int col = countCol("test1.txt");
    if (col ==  5){
        printf("-----------------------------\\n");
        printf("countCol() test passed.");
        printf("-----------------------------\\n");
        passed++;
    }
    else{
        printf("-----------------------------\\n");
        printf("countCol() test failed.");
        printf("-----------------------------\\n");
    }
}

void testCountRow(char *filename){
    int row = countRow("test1.txt");
    if (row ==  5){
        printf("-----------------------------\\n");
        printf("countRow() test passed.");
        printf("-----------------------------\\n");
        passed++;
    }
    else{
        printf("-----------------------------\\n");
        printf("countRow() test failed.");
        printf("-----------------------------\\n");
    }
}

void testReadfile(char *filename){
    int i,j;
    int **mapInit = readfile("test1.text");
    for (i=0; i<5; i++){
        for(j=0; j<5; j++){
            if (mapInit[i][j] == 0){
                printf("-----------------------------\\n");
                printf("readfile() test passed.");
                printf("-----------------------------\\n");
                passed++;
            }
            else{
                printf("-----------------------------\\n");
                printf("readfile() test failed.");
                printf("-----------------------------\\n");
            }
        }
    }
}

void testWritefile(char *filename){
    int i,j;
    int **map={{0,0,0,0,0},{0,0,0,0,0},
               {0,0,0,0,0},{0,0,0,0,0},
               {0,0,0,0,0}};
    writefile("text2.txt");
    int **mapInit = readfile("text2.txt");
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            if (map[i][j] == mapInit[i][j]){
                printf("-----------------------------\\n");
                printf("writefile() test passed.");
                printf("-----------------------------\\n");
                passed ++;
            }
            else{
                printf("-----------------------------\\n");
                printf("writefile() test failed.");
                printf("-----------------------------\\n");
            }
        }
    }
}

void testGame(){
    int i,j;
    int **map={{0,0,0,0,0},{0,0,1,0,0},{1,0,1,0,0},{0,1,1,0,0},{0,0,0,0,0}};
    int **mapTest = {{0,0,0,0,0},{0,1,0,0,0},{0,0,1,1,0},{0,1,1,0,0},{0,0,0,0,0}};
    int **mapInit = game(map);
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            if (mapInit[i][j] = mapTest[i][j]){
                printf("-----------------------------\\n");
                printf("writefile() test passed.");
                printf("-----------------------------\\n");
                passed ++;
            }
            else{
                printf("-----------------------------\\n");
                printf("writefile() test failed.");
                printf("-----------------------------\\n");
            }
        }
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
    printf(passed);
    return 0;
}
