#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <time.h>
using namespace std;

int ground=29;
int side=118;
int playerPos=ground-1;
int plx=6;
int hobs=rand()%ground+10;
int powerJump=15;
int nrDeVieti=3;
int score=0;
int dellay=25;


void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        coord
    );
}

void drawLine(char a,int x1,int y1,int x2,int y2)
{
    int d;
    bool finish=false;

    while(!finish)
    {
        if(a=='x' || a=='X')
        {
            if(x1-x2>0)
                x1--;
            if(x2-x1>0)
                x1++;
        }

        if(a=='y' || a=='Y')
        {
            if(y1-y2>0)
                y1--;
            if(y2-y1>0)
                y1++;
        }
        gotoxy(x1,y1);

        cout<<"#";

        if((a=='x' || a=='X') && x1==x2)
            finish=true;
        if((a=='y' || a=='Y') && y1==y2)
            finish=true;

        //getch();

    }

}

void drawEmptyLine(char a,int x1,int y1,int x2,int y2)
{
    int d;
    bool finish=false;

    while(!finish)
    {
        if(a=='x' || a=='X')
        {
            if(x1-x2>0)
                x1--;
            if(x2-x1>0)
                x1++;
        }

        if(a=='y' || a=='Y')
        {
            if(y1-y2>0)
                y1--;
            if(y2-y1>0)
                y1++;
        }
        gotoxy(x1,y1);

        cout<<" ";

        if((a=='x' || a=='X') && x1==x2)
            finish=true;
        if((a=='y' || a=='Y') && y1==y2)
            finish=true;

        //getch();

    }

}

void createCanvas(int width,int height)
{
    drawLine('y',0,0,0,height);
    drawLine('x',0,height,width,height);
    drawLine('y',width,height,width,0);
    drawLine('x',width,0,0,0);

}

int randomnumber()
{

    srand( time(NULL) );
    int randomNumber = rand();

    return randomNumber;
}

int obstacol(int x)
{
    if(x==0)
    {
        hobs=randomnumber()%(ground-20)+20;
    }

    drawLine('y',x,ground,x,hobs);
    drawEmptyLine('y',x+1,ground,x+1,1);

    return hobs;

}

void showPlayer(int playerPos)
{
    gotoxy(plx,playerPos);
    cout<<"#";
}

int checkForJump()
{
    if( GetAsyncKeyState( 'W' ) & 0x1 )
        return true;
    else
        return false;
}

void setup(int i)
{
    //Creater canvas
    createCanvas(side,ground);
    gotoxy(ground-5,4);
    drawLine('x',side-3,ground + 2,side-3-i,ground + 2);
    gotoxy(2,ground+2);
    cout<<"Score:"<<score;

}

int main()
{   //Declaratii
    int playerJump=false;int goUp=true;
    int obspos=side-2;int hobs;
    bool finish=false;
    int again=true;

getch();
for(int i=1;i<=nrDeVieti && again==true;i++)
{
    setup(nrDeVieti+1-i);
    while(!finish)
    {
        obspos--;//Move obstacol
        obstacol(obspos);
        hobs=obstacol(obspos);
        if(obspos==0)//Reset obstacol
            obspos=side-2;




        if(checkForJump()==true)//Check for jump
            playerJump=true;

        if(playerJump==true && goUp==true)
        {
            playerPos--;
            if(playerPos<=powerJump)
                goUp=false;
        }

        if(goUp==false)
        {

            playerPos++;
            if(playerPos>=ground-1)
                {
                    goUp=true;
                    playerJump=false;
                }

        }

        if(playerPos<ground-1 && goUp==true)
        {
            gotoxy(plx,playerPos+1);
            cout<<" ";
        }
        //if(goUp==false)
        {
            gotoxy(plx,playerPos-1);
            cout<<" ";
        }

        showPlayer(playerPos);//Show Player

        if(obspos==plx && playerPos>=hobs)
            finish=true;

        if(obspos==plx && playerPos<hobs)
            {
                score++;
                gotoxy(2,ground+2);
                cout<<"Score:"<<score;
            }









        Sleep(dellay);
    }


    if(finish==true && i!=nrDeVieti)
    {
        system("cls");
        score=0;
        gotoxy(side/2 -5,ground/2);
        cout<<"Lose"<<endl;
        gotoxy(side/2 -24,ground/2+1);
        cout<<"Press R to Restart      "<<"Press Q to Quit";

        char dec=' ';

        while(dec==' ')
        {
        dec=getch();
        if(dec=='r')
            finish=false;
        else if(dec=='q')
            again=false;
        else
            dec=' ';
        }

        system("cls");
    }
}

    //gotoxy(0,ground+1);
    return 0;
}



















