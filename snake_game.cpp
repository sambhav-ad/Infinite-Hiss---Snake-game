#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver; //Depicts whether the game has terminated or not.
const int width = 32;
const int height = 16;
//Coordinates of snake's position are (x, y)
//Coordinates of food's position are (fruitX, fruitY)
//Score depicts score of the player
int x, y, fruitX, fruitY, score;
//x and y coordinate of the tail in pairs
int tailX[100], tailY[100];
int nTail = 0;
//For directions
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;//Current direction of the snake
string username;

void Setup()
{   
    cout<<"ENTER PLAYER NAME: ";
    cin>>username;
    cout<<username<<endl;
    gameOver = false;
    dir = STOP;//Snake doesn't move by default
    //Snake starts at center
    x = width / 2;
    y = height / 2;
    //Food is at random position
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
void Draw()
{
    system("cls");//Clear the screen
    //Top boundary
    for (int i = 0; i < width+2; i++)
        cout << "-";
    cout << endl;
    //Side walls and empty spaces
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "|";
            //Head of snake
            if (i == y && j == x)
                cout << "O";
            //Print the food
            else if (i == fruitY && j == fruitX)
                cout << "x";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
                 
 
            if (j == width - 1)
                cout << "|";
        }
        cout << endl;
    }
    //Bottom boundary
    for (int i = 0; i < width+2; i++)
        cout << "-";
    cout << endl;
    cout << "Score:" << score << endl;
}
void Input()
{
    if (_kbhit()) //If the keyboard key is pressed or not
    {
        switch (_getch())//Gives the ASCII value of pressed key
        {
        //Directions
        //      w
        //  a       s
        //      d
        
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'e': //Terminates game as requested by player
            gameOver = true;
            break;
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)//moves the snake acc to directions given
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    //If user hits the walls, gameover
    if (x > width || x < 0 || y > height || y < 0)
      gameOver = true;
    //If we hit any tail segment with the head, gameover
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
 
    //If snakes eat the food
    if (x == fruitX && y == fruitY)
    {   //score also depends on length of snake 'ooooooooooO'
        score += 50 + nTail*20;
        //Again food sets to new random location
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(100); //To reduce the speed
    }
    cout<<"OOPS! "<<username<<", GAMEOVER"<<endl;
    cout<<"Your score: "<<score<<endl;
    cout<<"Try harder next time '-'"<<endl;
    return 0;
}