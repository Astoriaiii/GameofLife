//
// Created by PC on 2022/5/18.
//

#ifndef GAMEV1_GAME_H
#define GAMEV1_GAME_H

extern int row, col;
extern int** mapInit;

//count the length of column
int countCol(char *filename);

//count the length of row
int countRow(char *filename);

//read the initialized state from file
int** readfile(char *filename);

//implement the game rules
int** game(int **map);

//write the game state to file
int writefile(char *filename);



#endif //GAMEV1_GAME_H
