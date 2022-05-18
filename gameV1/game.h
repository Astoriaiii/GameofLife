//
// Created by PC on 2022/5/18.
//

#ifndef GAMEV1_GAME_H
#define GAMEV1_GAME_H

extern int row, col;
extern int** mapInit;

int countCol(char *filename);

int countRow(char *filename);

int** readfile(char *filename);

int** game(int **map);

int writefile(char *filename);



#endif //GAMEV1_GAME_H
