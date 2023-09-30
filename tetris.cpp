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
    // 23.10.01 소스추가 by QoneLee
    void setX(int x) {
      this->x = x;
    }
    void setY(int y){
      this->y = y;
    }
    void setRotationCount(int r){
      this-> rotationCount = r;
    }
    void setShape(int r, int y, int x, int value){
      this->shape[r][y][x] = value;
    }
    // 23.10.01 소스추가 by QoneLee
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

// 23.10.01 소스추가 by QoneLee
// 백업용 클래스
class Backup{
  public:
    // 블록 백업
    static void updateBlock(Block *source, Block &backupBlock){
      backupBlock.setX(source->getX()); // 블록의 x좌표 백업
      backupBlock.setY(source->getY()); // 블록의 y좌표 백업
      backupBlock.setRotationCount(source->getRotationCount()); // 블록의 회전상태 변수 백업
      for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
          for(int k = 0; k < 4; k++){
            backupBlock.setShape(i,j,k, source->getShape(i,j,k)); // 블록의 모양 백업
          }
        }
      }
    }
    // 테이블 백업
    static void updateTable(vector<vector<int> > &source, vector<vector<int> > &backupTable){
      backupTable.resize(source.size(), vector<int>(source.size())); // 기존테이블의 크기만큼 2차원배열의 크기 지정
      copy(source.begin(),source.end(),backupTable.begin()); // 기존테이블 vector를 backupTable vector에 백업
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

      // 23.10.01 소스추가 by QoneLee
      // 맨 밑바닥 감지용
      for(int i = 0; i < x -1; i++){
        table[y-1][i] = 4; // 맨 밑에를 4로 지정
      }
      // 23.10.01 소스추가 by QoneLee
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
      // 23.10.01 소스추가 by QoneLee
      // 백업
      Block backupBlock; // 백업용 블록 객체
      vector<vector<int> > backupTable; // 백업용 테이블 객체
      backup::updateBlock(blockObject, backupBlock); // block backup
      backup::updateTable(table, backupTable); // table backup
      // 23.10.01 소스추가 by QoneLee

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
          // 23.10.01 소스추가 by QoneLee
          int blockValue = blockObject->getShape(blockObject->getRotationCount(),i,j); // 블록의 배열값 얻기
          if( blockValue != 2) continue; // 블록이 아니면 무시
          if( table[Y][X] == 0) { // 빈공간이면 갱신
            table[Y][X] = blockValue; 
          } else if( table[Y][X] ==1 ) { // 블록이 양옆에 닿으면 취소
            copy(backupTable.begin(), backupTable.end(), table.begin()); // table 백업
            blockObject->setX(backupBlock.getX()); // 블록 x좌표 백업
            blockObject->setY(backupBlock.getY()); // 블록 y좌표 백업
            return;
          } else if( table[Y][X] == 3 ) { // 이미 쌓여진 블록과 접촉시 
            copy(backupTable.begin(), backupTable.end(), table.begin());
            blockObject->setX(backupBlock.getX());
            blockObject->setY(backupBlock.getY());
            if( key == DOWN){ // 키가 아랫방향일 경우 블록을 쌓고 새로운 블록을 만듦
              buildBlock();
              createBlock();
            }
            return;
          } else if( table[Y][X] == 4) { // 맨 밑바닥과 접촉시 
            copy(backupTable.begin(), backupTable.end(), table.begin());
            blockObject->setX(backupBlock.getX());
            blockObject->setY(backupBlock.getY());
            if( key == DOWN){ // 키가 아랫방향일 경우 블록을 쌓고 새로운 블록을 만듦
              buildBlock();
              createBlock();
            }
            return;
          }
          // if(table[Y][X] == 0){
          //   table[Y][X] = blockObject->getShape(blockObject->getRotationCount(), i, j);
          // }
        }
      }
    }

    // 블록 회전
    void rotateBlock(){
      // 23.10.01 소스추가 by QoneLee
      // 백업
      Block backupBlock;
      vector<vector<int> > backupTable;
      backup::updateBlock(blockObject, backupBlock); // block backup
      backup::updateTable(table, backupTable); // table backup
      // 23.10.01 소스추가 by QoneLee
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

      blockObject->rotate(); // 블록을 회전
      
      //블록상태 테이블에 갱신
      for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
          int Y = j + blockObject->getY();
          int X = i + blockObject->getX();
          //23. 10.01 소스추가 by QoneLee
          int blockValue = blockObject->getShape(blockObject->getRotationCount(), i, j); // 블록 배열값
          if( table[Y][X] != 2) continue; // 블록이 아니면 무시
          if(table[Y][X] == 0){
            table[Y][X] = blockObject->getShape(blockObject->getRotationCount(), i, j);
          } else if( table[Y][X] == 1 || table[Y][X] == 3 || table[Y][X] == 4) {
            copy(backupTable.begin(), backupTable.end(), table.begin());
            blockObject->setRotationCount(backupBlock.getRotationCount());
            return;
          }
          // 23.10.01 소스추가 by QoneLee
        }
      }
    }
    // 23.09.30 소스추가 by QoneLee

    // 23.10.01 소스추가 by QoneLee
    // 블록 쌓기
    void buildBlock(){
      for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
          int Y = j + blockObject->getY();
          int X = i + blockObject->getX();
          int blockValue = blockObject->getShape(blockObject->getRotationCount(), i ,j);
          if( table[Y][X] != 2) continue;
          table[Y][X] = 3;
        }
      }
    }
    // 23. 10.01 소스추가 by QoneLee
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