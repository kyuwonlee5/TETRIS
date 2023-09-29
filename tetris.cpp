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

// 1번 블록
const int firstBlock[4][4][4] = {
  {
    {0,0,0,0},
    {0,0,0,0},
    {2,2,2,2},
    {0,0,0,0}
  },
  {
    {0,0,2,0},
    {0,0,2,0},
    {0,0,2,0},
    {0,0,2,0}
  },
  {
    {0,0,0,0},
    {0,0,0,0},
    {2,2,2,2},
    {0,0,0,0},
  },
  {
    {0,0,2,0},
    {0,0,2,0},
    {0,0,2,0},
    {0,0,2,0}
  }
};

// 2번 블록
const int secondBlock[4][4][4] = {
  {
    {0,0,0,0},
    {0,2,2,0},
    {0,2,2,0},
    {0,0,0,0}
  },
  {
    {0,0,0,0},
    {0,2,2,0},
    {0,2,2,0},
    {0,0,0,0}
  },
  {
    {0,0,0,0},
    {0,2,2,0},
    {0,2,2,0},
    {0,0,0,0}
  },
  {
    {0,0,0,0},
    {0,2,2,0},
    {0,2,2,0},
    {0,0,0,0}
  }
};

// 23.09.30 소스추가 by QoneLee
//3번 블록
const int thirdBlock[4][4][4] = {
  {
    {0,2,0,0},
    {0,2,0,0},
    {0,2,2,0},
    {0,0,0,0}
  },
  {
    {0,0,0,0},
    {0,2,2,2},
    {0,2,0,0},
    {0,0,0,0}
  },
  {
    {0,2,2,0},
    {0,0,2,0},
    {0,0,2,0},
    {0,0,0,0}
  },
  {
    {0,0,0,0},
    {0,0,2,0},
    {2,2,2,0},
    {0,0,0,0}
  }
};

//4번 블록
const int fourthBlock[4][4][4] = {
  {
    {0,0,0,0},
    {0,2,0,0},
    {0,2,2,0},
    {0,0,2,0}
  },
  {
    {0,0,0,0},
    {0,2,2,0},
    {2,2,0,0},
    {0,0,0,0}
  },
  {
    {0,0,0,0},
    {0,2,0,0},
    {0,2,2,0},
    {0,0,2,0}
  },
  {
    {0,0,0,0},
    {0,2,2,0},
    {2,2,0,0},
    {0,0,0,0}
  }
};

// 5번 블록
const int fifthBlock[4][4][4] = {
  {
    {0,0,0,0},
    {0,2,2,2},
    {0,0,2,0},
    {0,0,0,0}
  },
  {
    {0,0,2,0},
    {0,2,2,0},
    {0,0,2,0},
    {0,0,0,0}
  },
  {
    {0,0,2,0},
    {0,2,2,2},
    {0,0,0,0},
    {0,0,0,0}
  },
  {
    {0,0,2,0},
    {0,0,2,2},
    {0,0,2,0},
    {0,0,0,0}
  }
};

// 블록의 부모클래스
class Block {
  protected:
    int shape[4][4][4]; // [로테이트][y][x]
    int x; // x좌표
    int y; // y좌표
    int rotationCount; //shape[0][y][x], shape[1][y][x], shape[2][y][x], shaoe[3][y][x]로 4가지 상태 표현
  
  public:
    int getShape(int rotationCount, int y, int x){
      return shape[rotationCount][y][x];
    }
    int getX(){
      return x;
    }
    int getY(){
      return y;
    }
    int getRotationCount(){
      return rotationCount;
    }
    void down(){
      y--;
    }
    void left(){
      x--;
    }
    void right(){
      x++;
    }
    void rotate(){
      rotationCount = (rotationCount + 1) % 4;
    }
};

//1번 블록 클래스
class firstBlock : public Block {
  public:
    firstBlock(){
      x = WIDTH / 2 - 3;
      y = 1;
      rotationCount = 0;
      for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
          for(int k = 0; k < 4; k ++){
            shape[i][j][k] = firstBlock[i][j][k];
          }
        }
      }
    }
};

//2번 블록 클래스
class secondBlock : public Block {
  public:
    secondBlock(){
      x = WIDTH / 2 - 3;
      y = 1;
      rotationCount = 0;
      for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j++){
          for(int k = 0; k < 4; k++){
            shape[i][j][k] = secondBlock[i][j][k];
          }
        }
      }
    }
};

//3번 블록 클래스
class thirdBlock : public Block {
  public:
    x = WIDTH / 2 - 3;
    y = 1;
    rotationCount = 0;
    for(int i = 0; i < 4; i++){
      for(int j = 0; j < 4; j++){
        for(int k = 0; k < 4; k++){
          shape[i][j][k] = thirdBlock[i][j][k];
        }
      }
    }
};

//4번 블록클래스
class fourthBlock : public Block {
  public:
    x = WIDTH / 2 - 3;
    y = 1;
    rotationCount = 0;
    for(int i = 0; i < 4; i++){
      for(int j = 0; j < 4; j++){
        for(int k = 0; k < 4; k++){
          shape[i][j][k] = fourthBlock[i][j][k];
        }
      }
    }
};

//5번 블록 클래스
class fifthBlock : public Block{
  public:
    x = WIDTH / 2 - 3;
    y = 1;
    rotationCount = 0;
    for(int i = 0; i < 4; i++){
      for(int j = 0; j < 4; j++){
        for(int k = 0; k < 4; k++){
          shape[i][j][k] = fifthBlock[i][j][k];
        }
      }
    }
};
// 23.09.30 소스추가 by QoneLee

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

// 테트리스 게임테이블 크래스
class GameTable{
  private:
    int x; // 가로
    int y; // 세로
    vector<vector<int> > table; // 게임판 만들기 0 = " ", 1 = "▦"
    // 23.09.30 소스추가 by QoneLee
    Block *blockObject; // 포인터를 사용하여 callByValue 가 아닌 callByReference
    // 23.09.30 소스추가 by QoneLee
  public:
    GameTable(int x, int y){ // 게임판 뼈대
    // 23.09.30 소스추가 by QoneLee
      blockObject = nullptr;
    // 23.09.30 소스추가 by QoneLee
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
          } else if(table[i][j] == 2) {
            cout << "▦";
          } else {
            cout << " ";
          }
        }
        cout << "\n";
      }
    }

    // 23.09.30 소스추가 by QoneLee
    // 블럭생성
    void createBlock(){
      srand(time(NULL));
      int select = srand % 5 + 1; // 1 ~ 5 block
      if(select == 1) {
        blockObject = new firstBlock();
      } else if(select  == 2){
        blockObject = new secondBlock();
      } else if(select == 3) {
        blockObject = new thirdBlock();
      } else if(select == 4) {
        blockObject = new fourthBlock();
      } else if(select == 5) {
        blockObject = new fifthBlock();
      }

      for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++){
          int Y = j + blockObject->getY();
          int X = i + blockObject->getX();
          // 블록객체를 테이블로 업데이트
          table[Y][X] = blockObject->getShape(blockObject->getRotationCount(), i, j);
        }
      }
    }

    //블록 이동
    void moveBlock(){
      // 테이블에서 블록지우기
      for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
          int Y = j + blockObject->getY();
          int X = i + blockObject->getX();
          if(table[Y][X] == 2) { // 블록끼리 일치하면
            table[Y][X] = 0;  // 테이블에서 삭제
          }
        }
      }

      // 인자값에 따른 블록이동
      if(key == DOWN){
        blockObject->down();
      } else if(key == LEFT) {
        blockObject->left();
      } else if(key == RIGHT){
        blockObject->right();
      }

      //블록상태 테이블에 갱신
      for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
          int Y = j + blockObject->getY();
          int X = i + blockObject->getX();
          if(table[Y][X] == 0){
            table[Y][X] = blockObject->getShape(blockObject->getRotationCount(), i, j);
          }
        }
      }
    }

    // 블록 회전
    void rotateBlock(){
      blockObject->rotate();
      // 테이블에서 블록지우기
      for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
          int Y = j + blockObject->getY();
          int X = i + blockObject->getX();
          if(table[Y][X] == 2) { // 블록끼리 일치하면
            table[Y][X] = 0;  // 테이블에서 삭제
          }
        }
      }

      //블록상태 테이블에 갱신
      for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
          int Y = j + blockObject->getY();
          int X = i + blockObject->getX();
          if(table[Y][X] == 0){
            table[Y][X] = blockObject->getShape(blockObject->getRotationCount(), i, j);
          }
        }
      }
    }
    // 23.09.30 소스추가 by QoneLee
};

// 23.09.30 소스추가 by QoneLee
// 게임 시작 클래스
class GamePlay{
  private:
    GameTable *gt;
  
  public:
    GamePlay(){
      gt = new GameTable(WIDTH, HEIGHT);
      gt->createBlock();
      gt->DrawGameTable();
      while (true)
      {
        int nSelect;
        if(_kbhit()) {
          nSelect = _getch();
          if(nSelect == 224){
            nSelect = _getch();
            switch (nSelect)
            {
            case UP: 
              gt->rotateBlock();
              gotoxy(0,0);
              gt->DrawGameTable();
              break;
            case DOWN:
              gt->moveBlock(DOWN);
              gotoxy(0,0);
              gt->DrawGameTable();
              break;
            case LEFT:
              gt->moveBlock(LEFT);
              gotoxy(0,0);
              gt->DrawGameTable();
              break;
            case RIGHT:
              gt->moveBlock(RIGHT);
              gotoxy(0,0);
              gt->DrawGameTable();
              break;
            default:
              break;
            }
          }
        }
      }
      
    }
    ~GamePlay(){
      delete gt;
      cout << "Good Bye~ See you Next time! :D";
    }
};
// 23.09.30 소스추가 by QoneLee

int main(){
  CursorView(false);
  system("mode con cols=100 lines=40 | title 테트리스 게임"); // 콘솔창 크기 및 제목 설정
  GameTable gt(WIDTH, HEIGHT);
  MainMenu();
  GamePlay();
  getchar(); 
}