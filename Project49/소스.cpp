#include <iostream>
#include <algorithm>
#include <vector>
//#include <termios.h>
//#include <unistd.h>
#include <fcntl.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>

using namespace std;
//■


/*
int getch() {
    termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);        // 라인버퍼/에코 비활성
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 원복
    return ch;
}
*/

class Player;

class Map;


class Map {
private:
    static const int ROWS = 25;
    static const int COLS = 25;
    int map1[ROWS][COLS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1},
    {1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
    {1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,0,1},
    {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1},
    {1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,1},
    {1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1},
    {1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
    {1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

public:
    Map() {}

    int getMapInfo(int r, int c) {
        if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return 1;
        return map1[r][c];
    }

    bool inBoard(int r, int c) {
        return 0 < r && r < ROWS - 1 && 0 < c && c < COLS - 1;
    }

    bool isWall(int r, int c) {
        return inBoard(r, c) && getMapInfo(r, c) == 1;
    }

    void drawMap(Player p);

};

class Monster
{
private:
    int xy = 0;
public:

    Monster() {}
    Monster(int _xy)
    {
        xy = _xy;
    }
};


class Player
{
private:

    int life = 3;
    int row = 5;
    int col = 2;
    int score = 0;
public:

    Player() {};
    Player(int _life, int _row, int _col, int _score)
    {
        life = _life;
        row = _row;
        col = _col;
        score = _score;
    };

    int getRow() {
        return row;
    };
    int getCol() {
        return col;
    };

    void tryMove(Map m, int dr, int dc) {
        int nr = row + dr, nc = col + dc;
        if (!m.inBoard(nr, nc) || m.isWall(nr, nc)) return;
        COORD pos = { short(col),short(row) };
        //커서 이동
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);


        cout << " ";
        row = nr; col = nc;


        pos = { short(col),short(row) };
        //커서 이동
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

        cout << "○";

    };


    int Break()
    {
        return 0;
    };


    void Score()
    {
        Map m;
        if (m.inBoard(col, row) == '.')
        {
            score += 1;
            cout << "score : " << score;
        }

    }

};



void Map::drawMap(Player p) {
    //system("cls");
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (p.getRow() == i && p.getCol() == j) {
                cout << "☆";
                continue;
            }
            if (getMapInfo(i, j) == 1) {
                cout << "#";
            }
            else {
                cout << '.';
            }
        }
        cout << '\n';
    }
}


void getNewMove(Player& P, Map m)
{
    int ch = _getch();

    if (ch == 224) {
        int ch2 = _getch();
        switch (ch2) {
        case 72: P.tryMove(m, -1, 0); break;
        case 80: P.tryMove(m, +1, 0); break;
        case 77: P.tryMove(m, 0, +1); break;
        case 75: P.tryMove(m, 0, -1); break;

        }
    }

    else {
        ch = tolower(ch);
        if (ch == 'q') {
            cout << "게임 종료\n";
            P.Break();
        }
        else if (ch == 'w') {
            while (!m.isWall(P.getRow() - 1, P.getCol()) && !_kbhit()) {
                P.tryMove(m, -1, 0);
                Sleep(75);
            }
        }
        else if (ch == 's') {
            while (!m.isWall(P.getRow() + 1, P.getCol()) && !_kbhit()) {
                P.tryMove(m, +1, 0);
                Sleep(75);
            }
        }

        else if (ch == 'a') {

            while (!m.isWall(P.getRow(), P.getCol() - 1) && !_kbhit()) {
                P.tryMove(m, 0, -1);
                Sleep(75);
            }

        }
        else if (ch == 'd') {
            while (!m.isWall(P.getRow(), P.getCol() + 1) && !_kbhit()) {
                P.tryMove(m, 0, +1);
                Sleep(75);
            }

        }
    }
}



int main() {
    Player p;
    Monster m;
    Map map;
    map.drawMap(p);
    while (1)
    {

        getNewMove(p, map);
        p.Score();
    }

}

