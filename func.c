#include "head.h"

void resetmap(level *place, char new[SIZE_Y][SIZE_X]){
    for(int i = 0; i < SIZE_Y; i ++){
        for(int j = 0; j < SIZE_X; j++){
            place->map[i][j] = new[i][j];
            place->mapsave[i][j] = new[i][j];
        }
    }
}

/////////////////////////////////////////
void setHero(level *place){
    int tY = place->y;
    int tX = place->x;
    place->map[tY][tX] = place->hero;
    system("say -v Alex -r 300 search drugs"); 
}
////////////////////////////////////////////////////

void refreshMapNothing(level *place){
    for(int i = 0; i < SIZE_Y; i++){
        for(int j = 0; j < SIZE_X; j++){
            place->map[i][j] = place->foundnothing[i][j];
        }
    }
}

/////////////////////////////////////////////////////
void findHero(level *place, int x, int y, int sizeX, int sizeY){
    for(int i = 0; i < sizeY; i++){
        for(int j = 0; j < sizeX; j++){
            if(place->map[i][j] == '@'){
                x = j;
                y = i;
            }
        }
    }
}
//////////////////////////////////////////////////
void refreshMap(level *place){
    for(int i = 0; i < SIZE_Y; i++){
        for(int j = 0; j < SIZE_X; j++){
            place->map[i][j] = place->mapsave[i][j];
        }
    }
}
////////////////////////////////////////////////////
void clipBomb(level *place){
    for(int i = 0; i < 4; i++){
        clear();
        usleep(300000);
        
        place->map[place->y][place->x] = 'S';
        place->map[place->y][place->x + 1] = '*';
        place->map[place->y][place->x - 1] = '*';
        place->map[place->y + 1][place->x] = '*';
        place->map[place->y - 1][place->x] = '*';
        place->map[place->y + 1][place->x - 1] = '/';
        place->map[place->y + 1][place->x + 1] = '\\';
        place->map[place->y - 1][place->x - 1] = '\\';
        place->map[place->y - 1][place->x + 1] = '/';
        
        printMap(place);
        usleep(300000);
        clear();

        place->map[place->y][place->x] = 's';
        printMap(place);
        usleep(300000);
        
        
        clear();
        usleep(300000);
        
        place->map[place->y][place->x] = 'x';
        place->map[place->y][place->x + 1] = '%';
        place->map[place->y][place->x - 1] = '%';
        place->map[place->y + 1][place->x] = '%';
        place->map[place->y - 1][place->x] = '%';
        place->map[place->y + 1][place->x - 1] = '`';
        place->map[place->y + 1][place->x + 1] = '`';
        place->map[place->y - 1][place->x - 1] = '`';
        place->map[place->y - 1][place->x + 1] = '`';
        
        printMap(place);
        usleep(300000);
        clear();

        usleep(300000);
        place->map[place->y][place->x] = '@';
        printMap(place);
        usleep(300000);

        clear();

        move(SIZE_Y/2, SIZE_X/2);
        printw("%s\n%s\n%s","Your dog found shit","---------------------------","Please take care of the dog");
        system("say -v Alex -r 300 The dog found shit Please take care of the dog");
    }
    place->result = 1;
    place->score = 0;
}
////////////////////////////////////////////////////
void clipTresure(level *place){
    for(int i = 0; i < 3; i++){
        clear();
        usleep(300000);
        place->map[place->y][place->x] = 'g';
        system("say -v Alex -r 300 dig");
        printMap(place);
        usleep(300000);
        clear();

        place->map[place->y][place->x] = '@';
        printMap(place);
        usleep(300000);
        
    }
}
////////////////////////////////////////////////////
void actionHero(level *place, char action){

    int find = 0;
    if(action == 'E' || action == 'e'){
        place->result = 1;
    }else if(action == 'g'){
        for(int i = 0; i < MAX_OBJ; i++){
            if(place->y == place->obj[i][0] && place->x == place->obj[i][1]){
                place->obj[i][0] = 0;
                place->obj[i][1] = 0;
                place->findedtres++;
                find++;
                place->score = place->findedtres * (rand() % 100);
                system("say -v Alex -r 300 you have found drugs");
                clipTresure(place);
                refreshbones(place);

            }else if((place->y == place->obj[i][0] && place->x == place->obj[i][1]) || (place->score % 2 == 0)){
                find++;
                clipBomb(place);
                system("say -v Alex -r 300 you have found some shit, and you are going to hell");
            }   
        }
        if(find == 0){
                refreshMapNothing(place);
                refresh();
                system("say -v Alex -r 300 you have found nothing try more");
                usleep(10000);
                
            }   
    }else if(action == 'w' || action == 'W'){
        if(place->map[place->y-1][place->x] != '#'){
            findHero(place, place->x, place->y, SIZE_Y, SIZE_X);
            refreshMap(place);
            place->map[place->y-1][place->x] = place->hero;
            place->y--;
            system("say -v Alex -r 350 gaf");
        }
    }else if(action == 's' || action == 'S'){
        if(place->map[place->y+1][place->x] != '#'){
            findHero(place, place->x, place->y, SIZE_Y, SIZE_X);
            refreshMap(place);
            place->map[place->y+1][place->x] = place->hero;
            place->y++;
            system("say -v Alex -r 350 gaf");
        }
    }else if(action == 'a' || action == 'A'){
        if(place->map[place->y][place->x-1] != '#'){
            findHero(place, place->x, place->y, SIZE_Y, SIZE_X);
            refreshMap(place);
            place->map[place->y][place->x-1] = place->hero;
            place->x--;
            system("say -v Alex -r 350 gaf");
        }
    }else if(action == 'd' || action == 'D'){
        if(place->map[place->y][place->x+1] != '#'){
            findHero(place, place->x, place->y, SIZE_Y, SIZE_X);
            refreshMap(place);
            place->map[place->y][place->x+1] = place->hero;
            place->x++;
            system("say -v Alex -r 350 gaf");
        }
    }

}
////////////////////////////////////////////////////
void printMap(level *place){
    for(int i = 0; i < SIZE_Y; i++){
        printw("%s\n", place->map[i]);
        refresh();
        
    }
    
}
////////////////////////////////////////////////////


void spawntresure(level *place){
    int randX, randY;

    for(int i = 0; i < MAX_OBJ; i++){
        randY = 1 + rand() % (SIZE_Y - 1);
        randX = 1 + rand() % (SIZE_X - 1);
        if(randY == 0 || randX == 0){
            spawntresure(place);
        }
        place->obj[i][0] = randY;
        place->obj[i][1] = randX;
    }

}

void isobjnear(level* place){
    
    for(int i = 0; i < RADIUS; i++){
        for(int h = 0; h < MAX_OBJ; h++){
            if((place->y == place->obj[h][0]) && (place->x == place->obj[h][1])){
                printw("%c", '\n');
                for(int j = 0; j < RADIUS; j++){
                    printw("%s", " bark");
                }
                break;
            }
            if((place->y + i == place->obj[h][0]) && (place->x == place->obj[h][1])){
                printw("%c", '\n');
                for(int j = 0; j < i; j ++){
                    printw("%s", " bark");
                    
                }
                break;
            }else if((place->y == place->obj[h][0]) && (place->x + i == place->obj[h][1])){
                printw("%c", '\n');
                for(int j = 0; j < i; j ++){
                     printw("%s", " bark");
                }
                break;
            }else if((place->y - i == place->obj[h][0]) && (place->x == place->obj[h][1])){
                printw("%c", '\n');
                for(int j = 0; j < i; j ++){
                    printw("%s", " bark");
                 }
                 break;
            }
             else if((place->y == place->obj[h][0]) && (place->x - i == place->obj[h][1])){
                printw("%c", '\n');
                for(int j = 0; j < i; j ++){
                     printw("%s", " bark");
                }
                break;
            }else if((place->y + i == place->obj[h][0]) && (place->x + i == place->obj[h][1])){
                printw("%c", '\n');
                for(int j = 0; j < i; j ++){
                     printw("%s", " bark");
                }break;
            }else if((place->y - i == place->obj[h][0]) && (place->x - i == place->obj[h][1])){
                printw("%c", '\n');
                for(int j = 0; j < i; j ++){
                     printw("%s", " bark");
                }break;
            }else if((place->y - i == place->obj[h][0]) && (place->x + i == place->obj[h][1])){
                printw("%c", '\n');
                for(int j = 0; j < i; j ++){
                     printw("%s", " bark");
                }
                break;
            }else if((place->y + i == place->obj[h][0]) && (place->x - i == place->obj[h][1])){
                printw("%c", '\n');
                for(int j = 0; j < i; j ++){
                     printw("%s", " bark");
                }
                break;
            }
            

        }

    }
        
       
    
}
void minusbone(level *place){
    int i = 0;
    while(place->bones[i] == 'b'){
        i++;
    }
    place->bones[i - 1] = '-';
}
void refreshbones(level *place){
    int i = 0; 
    while(place->subbones[i] != '\0'){
        place->bones[i] = place->subbones[i];
        i++;
    }
}






