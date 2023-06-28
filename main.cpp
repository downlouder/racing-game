#include <iostream>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = {' ', '+', '+', ' ',
                  '+', '+', '+', '+',
                  ' ', '+', '+', ' ',
                  '+', '+', '+', '+'};

int carPos = WIN_WIDTH / 2;
int score = 0;

void gotoXY(int x, int y)
{
  CursorPosition.X = x;
  CursorPosition.Y = y;
  SetConsoleCursorPosition(console, CursorPosition);
}

void setCursor(bool visible, DWORD size)
{
  if (size == 0)
    size = 20;

  CONSOLE_CURSOR_INFO lpCursor;
  lpCursor.bVisible = visible;
  lpCursor.dwSize = size;
  SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder()
{
  for (int i = 0; i < SCREEN_HEIGHT; i++)
  {
    for (int j = 0; j < 17; j++)
    {
      gotoXY(0 + j, i);
      cout << "+";
      gotoXY(WIN_WIDTH - j, i);
      cout << "+";
    }
  }
  for (int i = 0; i < SCREEN_HEIGHT; i++)
  {
    gotoXY(SCREEN_WIDTH, i);
    cout << "+";
  }
}

void genEnemy(int ind)
{
  enemyX[ind] = 17 + rand() % (33);
}

void drawEnemy(int ind)
{
  if (enemyFlag[ind] == true)
  {
    gotoXY(enemyX[ind], enemyY[ind]);
    cout << "****";
    gotoXY(enemyX[ind], enemyY[ind] + 1);
    cout << " ** ";
    gotoXY(enemyX[ind], enemyY[ind] + 2);
    cout << "****";
    gotoXY(enemyX[ind], enemyY[ind] + 3);
    cout << " ** ";
  }
}

void eraseEnemy(int ind)
{
  if (enemyFlag[ind] == true)
  {
    gotoXY(enemyX[ind], enemyY[ind]);
    cout << "    ";
    gotoXY(enemyX[ind], enemyY[ind] + 1);
    cout << "    ";
    gotoXY(enemyX[ind], enemyY[ind] + 2);
    cout << "    ";
    gotoXY(enemyX[ind], enemyY[ind] + 3);
    cout << "    ";
  }
}

void resetEnemy(int ind)
{
  eraseEnemy(ind);
  enemyY[ind] = 1;
  genEnemy(ind);
}

void drawCar()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      gotoXY(j + carPos, i + 22);
      cout << car[i][j];
    }
  }
}

void eraseCar()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      gotoXY(j + carPos, i + 22);
      cout << " ";
    }
  }
}

int collision()
{
  if (enemyY[0] + 4 >= 23)
  {
    if (enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9)
    {
      return 1;
    }
  }
  return 0;
}

void gameOver()
{
  system("cls");
  cout << endl;
  cout << "\t\t-------------------------" << endl;
  cout << "\t\t--------Game Over--------" << endl;
  cout << "\t\t-------------------------" << endl;
  cout << "\t\t Press any key to go back to menu.";
  getch();
}

void updateScore()
{
  gotoXY(WIN_WIDTH + 7, 5);
  cout << "Score: " << score << endl;
}

void instructions()
{
  system("cls");
  cout << "Instructions";
  cout << "\n--------------";
  cout << "\n Avoid Cars by moving left or right.";
  cout << "\n\n Press 'a' to move left";
  cout << "\n Press 'd' to move right";
  cout << "\n Press 'escape' to exit";
  cout << "\n\n Press any key to go back to menu";
  getch();
}

void play()
{
  carPos = -1 + WIN_WIDTH / 2;
  score = 0;
  enemyFlag[0] = 1;
  enemyFlag[1] = 0;
  enemyY[0] = enemyY[1] = 0;

  system("cls");
  drawBorder();
  updateScore();
  genEnemy(0);
  genEnemy(1);

  gotoXY(WIN_WIDTH + 7, 2);
  cout << "Car Game";
  gotoXY(WIN_WIDTH + 6, 4);
  cout << "----------";
  gotoXY(WIN_WIDTH + 6, 6);
  cout << "----------";
  gotoXY(WIN_WIDTH + 7, 12);
  cout << "Control ";
  gotoXY(WIN_WIDTH + 7, 13);
  cout << "---------- ";
  gotoXY(WIN_WIDTH + 2, 14);
  cout << " A key - Left";
  gotoXY(WIN_WIDTH + 2, 15);
  cout << " D key - Right";
  
  	gotoXY(18, 5);cout<<"Press any key to start";
	getch();
	gotoXY(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch=='D' ){
				if( carPos < 50 )
					carPos += 4;
			} 
			if(ch==27){
				break;
			}
		} 
		
		drawCar(); 
		drawEnemy(0); 
		drawEnemy(1); 
		if( collision() == 1  ){
			gameOver();
			return;
		} 
		Sleep(50);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);   
		
		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;
		
		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;
		
		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;
		 
		if( enemyY[0] > SCREEN_HEIGHT-4 ){
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 ){
			resetEnemy(1);
			score++;
			updateScore();
		}
	}
}

int main()
{
	setCursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("cls");
		gotoXY(10,5); cout<<" -------------------------- "; 
		gotoXY(10,6); cout<<" |        Car Game        | "; 
		gotoXY(10,7); cout<<" --------------------------";
		gotoXY(10,9); cout<<"1. Start Game";
		gotoXY(10,10); cout<<"2. Instructions";	 
		gotoXY(10,11); cout<<"3. Quit";
		gotoXY(10,13); cout<<"Select option: ";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	}while(1);
	
	return 0;
}