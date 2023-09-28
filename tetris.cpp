/*
  테트리스 가로 : 20
  테트리스 세로 : 30
*/

#include <iostream>
#include <vector>
/* 23.09.28 소스추가*/
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
/* 23.09.28 소스추가*/

using namespace std;

const int WIDTH = 20; // 가로 
const int HEIGHT = 30; // 세로
// 23.09.28 소스 추가 by Qone
const int LEFT = 75; // ←
const int RIGHT = 77; // →
const int UP = 72; // ↑
const int DOWN = 80; // ↓
// 23.09.28 소스 추가 by Qone

// 23.09.28 소스 추가 by Qone
// 커서 숨기기 = 0 / 보이기 = 1
void CursorView(char show){
  Handle hConsole;
  CONSOLE_CURSOR_INFO ConsoleCursor;

  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  ConsoleCursor.bVisible = show;
  ConsoleCursor.dwSize = 1;

  SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

// 콘솔 커서 위치 이동
void gotoxy(int x, int y){
  COORD pos = {x,y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class MainMenu {
  public :
    MainMenu(){
      cout << "\n\n\n\n";
      cout << "\t\t"; cout << "@@@@@@@@@@@@  @@@@@@@@@   @@@@@@@@@@@  @@@@@@@@   @   @@@@@@@@@@@\n";
      cout << "\t\t"; cout << "      @       @                @       @      @   @   @          \n";
      cout << "\t\t"; cout << "      @       @                @       @      @   @   @          \n";
      cout << "\t\t"; cout << "      @       @@@@@@@@@        @       @     @    @   @@@@@@@@@@@\n";
      cout << "\t\t"; cout << "      @       @                @       @ @ @      @             @\n";
      cout << "\t\t"; cout << "      @       @                @       @     @    @             @\n";
      cout << "\t\t"; cout << "      @       @@@@@@@@@        @       @      @   @   @@@@@@@@@@@\n\n\n\n\n";
      cout << "\t\t"; cout << "                게임을 시작하려면 아무키나 누르세요.\n\n\n\n\n\n\n";
      cout << "\t\t"; cout << "                   TetrisGame1.0 By QoneLee\n";
      getchar(); // 사용자가 입력한 char를 아스키코드값으로 받아오는 함수
    }
};
class GameTable{
  private:
    int x; // 가로
    int y; // 세로
    vector<vector<int> > table; // 게임판 만들기 0 = " ", 1 = "▦"
  public:
    GameTable(int x, int y){ // 게임판 뼈대
      this -> x = x;
      this -> y = y;
      for(int i = 0; i < y; i++){
        vector<int> temp;
        for(int j = 0; j < x; j++){
          temp.push_back(0);
        }
        table.push_back(temp);
      }

      // 가장자리 뼈대 색칠
      for(int i = 0; i < x; i++){
        table[0][i] = 1;
        table[y-1][i] = 1;
      }
      for(int i = 1; i < y-1; i++){
        table[i][0] = 1;
        table[i][x-1] = 1;
      }
    }
    
    // 게임판 그리는 함수
    void DrawGameTable(){
      for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
          if(table[i][j] == 1) {
            cout << "▦";
          } else {
            cout << " ";
          }
        }
        cout << "\n";
      }

    }
};

int main(){
  system("mode con cols=100 lines=40 | title 테트리스 게임"); // 콘솔창 크기 및 제목 설정
  GameTable gt(WIDTH, HEIGHT);
  MainMenu();
  gt.DrawGameTable();
  getchar(); 
}