#include "head.h"

char map1[SIZE_Y][SIZE_X] ={"#######################",
                            "#.....................#",
                            "#.........#.......#...#",
                            "#.....................#",
                            "#..#...........#......#",
                            "#.....................#",
                            "#........#.......#....#",
                            "#...#........#...#....#",
                            "#...#........#........#",
                            "#######################"
};

char map2[SIZE_Y][SIZE_X] = {
                "#######################",
                "#................#....#",
                "#.........#...........#",
                "#.....#...#.........#.#",
                "#..#......#....#......#",
                "#.....................#",
                "#.....#..#.......#....#",
                "#...#........#...#....#",
                "#..###.......#.....#..#",
                "#######################"
};

char map3[SIZE_Y][SIZE_X] = {
                "#######################",
                "#.........#......#....#",
                "#..#......#...........#",
                "#..##.....#.........#.#",
                "#.........#...........#",
                "#.....................#",
                "#........#............#",
                "#................#....#",
                "#............#........#",
                "#######################"
};


int main(){
    char ch = ' ';
    char choice = ' ';
    initscr();
    level world = {
            .bones = "bbbbbbbbbbbbbbbbbbbb",
            .map ={         "#######################",
                            "#.....................#",
                            "#.........#.......#...#",
                            "#.....................#",
                            "#..#...........#......#",
                            "#.....................#",
                            "#........#.......#....#",
                            "#...#........#...#....#",
                            "#...#........#........#",
                            "#######################"
            },
            .mapsave = {    "#######################",
                            "#.....................#",
                            "#.........#.......#...#",
                            "#.....................#",
                            "#..#...........#......#",
                            "#.....................#",
                            "#........#.......#....#",
                            "#...#........#...#....#",
                            "#...#........#........#",
                            "#######################"
            },
            .subbones = "bbbbbbbbbbbbbbbbbbbb",
            .score = 11,
            .result = 0,
            .x = 11,
            .findedtres = 0,
            .y = 5,
            .hero = '@',
            .foundnothing ={
                        "#######################",
                        "#---------------------#",
                        "#---|||||||||||||||---#",
                        "#-|||||||||||||||||||-#",
                        "#-|YOU.FOUND.NOTHING|-#",
                        "#-|||||||||||||||||||-#",
                        "#---|||||||||||||||---#",
                        "#-----|||||||||||-----#",
                        "#---------------------#",
                        "#######################"
                            }
            };
    while((choice != '1') || (choice != '2') || (choice != '3') || (choice != 'q')){
        system("say -v Alex -r 200 hi lets search drugs");
        system("say -v Alex -r 350 gaf gaf gaf");
        printw("%s", "\n\t(1)First level\n\t(2)Second level\n\t(3)Third level\n\n\t(q)Quit");
        refresh();
        choice = getch();

        if(choice == '1'){
            resetmap(&world, map1);
            system("say -v -r 200 Alex first level");
            break;
        }else if(choice == '2'){
            resetmap(&world, map2);
            system("say -v -r 200 Alex second level");
            break;
        }else if(choice == '3'){
            resetmap(&world, map3);
            system("say -v -r 200 Alex third level");
            break;
        }else if(choice == 'q'){
            ch = 'q';
            system("say -v -r 200 Alex bye");
            break;
        }
    }

    clear();
    endwin();

    setHero(&world);
    
    spawntresure(&world);
    initscr();
    while(ch != 'q'){
        if((world.bones[0] != 'b' )|| (world.result == 1)){
            clear();
            move(SIZE_Y/2, SIZE_X/2);
            if(world.score != 0){
                world.score = world.findedtres * (rand() % 100);
            }
            printw("!!!GAME OVER!!!\n\t      your score : %d", world.score);
            refresh();
            usleep(400000);
            break;
        }
        curs_set(0);
        clear();
        printMap(&world);
        printw("\n%s\n",world.bones);
        minusbone(&world);
        isobjnear(&world);
        ch = getch();
        actionHero(&world, ch);
    }
    usleep(1000000);
    endwin();
}


