#include <iostream>
#include <deque>
#include <time.h>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
using namespace std;

void setup(){

    initscr();// initscr()函数将终端屏幕初始化为curses 模式
    clear();
    noecho(); //禁止字符出现在终端上
    cbreak();//可以禁止行缓冲
    curs_set(0);//这个函数用来设制光标是否可见


}

class cPlayer{
public:
    int x, y;
    cPlayer(int width){
        x = width / 2;
        y = 0;
    }
};

class cLane{
private:
    deque<bool> cars;
    bool right;
public:
    cLane(int width){
        for (int i = 0; i < width; i++){
            cars.push_front(true);
        }
        
        right = rand() % 2;
     }

    void Move(){
        
        if (right){
            if ((rand() % 10) == 1 || (rand() % 10) == 3 ||(rand() % 10) == 5 || (rand() % 10) == 7 ||(rand() % 10) == 9){
                
                cars.push_front(true);
            } else {
                cars.push_front(false);
            }
            
            cars.pop_back();
            
        } else {
            if ((rand() % 10) == 1 || (rand() % 10) == 3 ||(rand() % 10) == 5 || (rand() % 10) == 7 ||(rand() % 10) == 9){
                
                cars.push_back(true);
            } else {
                cars.push_back(false);
            }
            
            cars.pop_front();
        }

    }

    bool CheckPos(int pos){
        return cars[pos];
    }
    
    void changeDirection(){
        right = !right;
    }
};


class cGame{
private:
    bool quit;
    int numberOfLanes;
    int width;
    int score;
    cPlayer * player;
    vector<cLane* > map;
public:
    cGame(int w = 20, int h = 10){
        numberOfLanes = h;
        width = w;
        quit = false;
        for (int i = 0; i < numberOfLanes; i++){
            map.push_back(new cLane(width));
        }
        player = new cPlayer(width);
    }
    
    ~cGame(){
        delete player;
        for (int i = 0; i < map.size(); i++)
        {
            cLane * current = map.back();
            map.pop_back();
            delete current;
        }
    }
    void Draw(){
        clear();

        for (int i = 0; i < numberOfLanes; i++){
            for (int j = 0; j < width; j++){
                if (i == 0 && (j == 0 || j == width - 1)){
                    mvprintw(i, j,"S");
                }
                
                if (i == numberOfLanes - 1 && (j == 0 || j == width - 1)){
                    mvprintw(i, j,"F");
                }
                
                if (map[i] -> CheckPos(j) && i != 0 && i != numberOfLanes -1){
                    mvprintw(i, j,"#");
                } else if (player -> x == j && player -> y == i){
                    mvprintw(i, j,"V");
                }
            }
        }
        
        mvprintw(numberOfLanes,0 , "Score: %d", score);


    }


    void Input(){
        
        keypad(stdscr, TRUE);
        halfdelay(5);

        char c = getch();


        if (c == 'a'){
            player -> x--;
        }

        if (c == 'd'){
            player -> x++;
        }

        if (c == 'w'){
            player -> y--;
        }

        if (c == 's'){
            player -> y++;
        }

        if (c == 'q'){
            quit = true;
        }

    }

    void Logic(){

        for (int i = 1; i < numberOfLanes - 1; i++){
            if ((rand() % 10) == 1 || (rand() % 10) == 3 ||(rand() % 10) == 5 || (rand() % 10) == 7 ||(rand() % 10) == 9){
                map[i] -> Move();
            }
            
            if (map [i] -> CheckPos(player -> x) && player -> y == i){
                
                quit = true;
            }
        }
        
        if (player -> y == numberOfLanes - 1){
            
            score++;
            player -> y =0;
            cout << "\x07";
            map[rand () % numberOfLanes ] -> changeDirection();
        }
        
        
        

    }

    void Run(){
        while(!quit){
            Input();
            Draw();
            Logic();
        }

    }
};

int main() {
    setup();
    srand(time(0));
    int weight = 30;
    int height = 5;
    cGame game = {weight, height};
    game.Run();
    cout << endl;
    
    cout <<"you lose" << endl;
    system( "read -n 1 -s -p \"Press any key to continue...\"" );
    getch();
    endwin();

    return 0;
}
