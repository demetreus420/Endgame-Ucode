
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define MAX_OBJ 2 //максимальное кол-во объектов(бомб и сокровищь)
#define SIZE_X 24 //Размер карты по длине
#define SIZE_Y 10 //Размер карты по высоте
#define RADIUS 4 //Радус радара



typedef struct MyLevel{
    int x, y;
    char hero;//<--герй              //структура уровня
    char map[SIZE_Y][SIZE_X];
    char mapsave[SIZE_Y][SIZE_X];
    int obj[MAX_OBJ][2];
    int findedtres; //собранные сокровища
    int result;
    int score;
    char subbones[21];
    char bones[21];
    char foundnothing[SIZE_Y][SIZE_X];
    
    
}level;

void resetmap(level *place, char new[SIZE_Y][SIZE_X]);
void setHero(level *place);
void refreshMapNothing(level *place);
void findHero(level *place, int x, int y, int sizeX, int sizeY);
void refreshMap(level *place);
void clipBomb(level *place);
void clipTresure(level *place);
void actionHero(level *place, char action);
void printMap(level *place);
void spawntresure(level *place);
void isobjnear(level* place);
void minusbone(level *place);
void refreshbones(level *place);


