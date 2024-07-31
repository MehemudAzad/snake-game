#include "iGraphics.h"
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>


#define screenWidth 600
#define screenHeight 600
#define pixel  15
#define length 10


FILE *names,*scores;

int len=0;

int pause;

int num=1,val=1;

int sec, minu, hr;

int up=0,down=0,left=0,right=1;

char str [100], name [100];

char score[10], h_s[10];

int window = 10,speed = 50, highscore;

int static points=-1;
int count=0;
int i, j;
int Field[screenHeight][screenWidth];
int x, y;
int Gy;
int Head, Tail=1,a, b;
int c,d;
int toggle=0;


void check_highscore(){
    if(points>=highscore)
    {
        highscore = points;
		scores=fopen("scores.txt", "w");

		fprintf(scores,"%d\n",highscore);

		fclose(scores);

		names=fopen("names.txt","w");

		fprintf(names,"%s", str);

		fclose(names);
	}
}


void get_score()
{
    //reading
	scores=fopen("scores.txt", "r");
	names=fopen("names.txt","r");
    //getting
	fscanf(names,"%s", &str);
	fscanf(scores,"%d", &highscore);
	//closing
	fclose(names);
	fclose(scores);
}


void timer()
{
    sec++;
    if(sec==60)
    {
        minu++;
        sec=0;
    }
    if(minu==60)
    {
        hr++;
        minu=0;
        sec=0;
    }
    //count++;
}

void food (){
        a = 30 + rand()%(screenWidth-50);
        b = 30 + rand()%(screenHeight-50);
        //PlaySound("hissing.wav", NULL, SND_LOOP || ASYNCH);

        if(count%5==0 && count!=0)
            points += 5;
        else
            points++;

      if(Field[b][a] ==0){
            Field[b][a] = -1;
      }
}


void snake_initialization(){
    PlaySound("snake.wav", NULL, SND_LOOP|| ASYNCH);
    count =0;
    x = screenHeight/2; y = screenWidth/2; Gy = y; Head = 1*length; Tail = 1, points =-1, speed= 50;
    food();
    for(i=0;i<screenHeight;i++){
    for(j=0;j<screenWidth;j++){
        Field[i][j] = 0;
    }
   }
    	for(i=Tail-1;i<Head; i++){
        Gy++;;
        Field[x][Gy-Head] = i+1;
    }
}

void gameover(){
    if((x > 180 && y >screenHeight-12) || (x<420 && y<12)||(y>180 && x<12)||(x>screenWidth-12&& y<420)){
                iPauseTimer(0);
                PlaySound("crash.wav", NULL, SND_LOOP || ASYNCH);
                check_highscore();
                speed = 60;
                count =0;
                window =0;
    }

}

void snake_movement(){
    if ( up==1 ) {
		y+=10;
        if(y>screenHeight-10 && x<190){
            x = screenWidth-190+x;
            y = 10;
        }
        gameover();
        Head++;
        Tail++;
        Field[x][y] = Head;

	}
	else if ( down==1 ) {
        y-=10;
          if(x>420 && y<10){
            x = x -420;
            y = screenHeight-10;
        }
        gameover();

        Head++;
        Tail++;
        Field[x][y] = Head;
	}
	else if ( right==1 ) {
		x+=10;
		  if(x>screenWidth-10 & y>screenHeight-180){
            x = 10;
            y = y-410;
        }
        gameover();

        Head++;
        Tail++;
        Field[x][y] = Head;
	}
	else if ( left==1 ) {
		x-=10;
        if(x<10 & y<190){
            x = screenHeight-10;
            y = 410 +y;
        }

        gameover();
        Head++;
        Tail++;
        Field[x][y] = Head;
	}
}

/*void speed_increase(){
    //speed increase
    if(speed > 40){
       if (count % 3 == 0 && count != 0 )
		{
			count = count + 1;
			speed = speed - .0001;
			iSetTimer(speed, snake_movement);
		}
    }
}*/

void iDraw() {
	iClear();

	if (window == 10){
        iShowBMP(0,0, "homemenu.bmp");

        // for NEW GAME
        iSetColor(255, 255, 255);
        iShowBMP2(20,470,"box.bmp", 0);
        iText(35, 490, " New Game ", GLUT_BITMAP_TIMES_ROMAN_24);


        // for CONTROLS
        iSetColor(255, 255, 255);
        iShowBMP2(20,370,"box.bmp", 0);
        iText(35, 390, " CONTROLS ", GLUT_BITMAP_TIMES_ROMAN_24);


        // for QUIT

        iSetColor(255,255, 255);
        iShowBMP2(20,270,"box.bmp", 0);
        iText(35, 290, " ABOUT ", GLUT_BITMAP_TIMES_ROMAN_24);


        // for HALLOFFAME
        iSetColor(0, 150, 255);
        iShowBMP2(20,170,"box.bmp", 0);
        iText(35, 190, "HOFAME", GLUT_BITMAP_TIMES_ROMAN_24);


        // for highscore
        iSetColor(255, 0 , 0);
        iShowBMP2(20,70,"box.bmp", 0);
        iText(35, 90, " QUIT ", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if(window == 0){

            if(points > highscore){
                iShowBMP(0, 0, "gameover.bmp");
                iText(600, 10, "Press 'r' to go back");
                highscore = points;

                sprintf(h_s, "%.3d", points);
                iSetColor(0, 255, 250);
                iText(200, 200, "!!!!New HIGHSCORE : ", GLUT_BITMAP_HELVETICA_18);
                iSetColor(255, 0, 0);
                iText(270, 100, "press 'enter' to play again", GLUT_BITMAP_HELVETICA_12);
                iText(400, 200, h_s, GLUT_BITMAP_TIMES_ROMAN_24);
            }else{
                iShowBMP(0, 0, "gameover.bmp");
                iText(600, 10, "Press 'r' to go back");
                sprintf(h_s, "%.3d", points);
                iSetColor(0, 255, 250);
                iText(200, 200,"YOUR SCORE : ", GLUT_BITMAP_HELVETICA_18);
                iSetColor(255, 0, 0);
                iText(270, 100, "press 'enter' to play again", GLUT_BITMAP_HELVETICA_12);
                iText(400, 200, h_s, GLUT_BITMAP_TIMES_ROMAN_24);
            }
	}

    if(window == 1){
            get_score();
            for(i=0;i<screenHeight;i++){
            for(j=0;j<screenWidth;j++){
            if(Field[i][j]>Tail){
                iSetColor(255,255,255);
                iFilledRectangle(i,j,pixel,pixel);
            }
            if(Field[i][j] < Tail){
                Field[i][j] = 0;
            }
        }
    }

    //displaying food
    if(count %5 ==0 && count!=0)
    iShowBMP2(a,b,"star.bmp",0);
    else
    iShowBMP2(a,b,"ball1.bmp",0);

    //collision with food
    if ((x+pixel>a && x<a+30) && (y+pixel> b && y<b+30))
		{
			food ();
			count++;
			Tail-=5;
			PlaySound("hissing.wav", NULL, SND_LOOP || ASYNCH);
		}

    //coloring the  head
    iSetColor(255,0,0);
    iFilledRectangle(x,y,pixel,pixel);
	//creating  the box
	iSetColor(20, 200, 200);
	iSetColor(20, 200, 200);
	iRectangle(0,0,screenWidth-10, screenHeight-10);
	iSetColor(20, 200, 200);
	iRectangle(10,10,screenWidth-20, screenHeight-20);
	//filled rectangles
	iSetColor(20, 200, 200);
	iFilledRectangle(screenWidth-420,screenHeight-10,screenWidth-180,10);
	iSetColor(20, 200, 200);
	iFilledRectangle(0,0,screenWidth-180,10);
	iSetColor(20, 200, 200);
	iFilledRectangle(0,screenHeight-420,10,screenHeight-180);
	iSetColor(20, 200, 200);
	iFilledRectangle(0,0,screenWidth-180,10);
	iSetColor(20, 200, 200);
	iFilledRectangle(screenWidth-10,0,10,screenHeight-180);
	//game name
	iSetColor(0, 0, 255);
	iText(40, 40, "HOW 2 SNEK",GLUT_BITMAP_TIMES_ROMAN_10);


	//showing score and highscore dynamically
	iSetColor(255, 0, 0);
	iText(20, screenHeight-30, "SCORE:          HIGHSCORE:");
	sprintf(score, "%.3d", points);
	sprintf(h_s, "%.3d", highscore);
	iSetColor(255,255,255);
    iText(73, screenHeight-30, score,  GLUT_BITMAP_9_BY_15);
    iText(230, screenHeight-30, h_s,  GLUT_BITMAP_9_BY_15);
    }

    //control page
    if (window == 2)
    {
        iShowBMP(0, 0, "how2play.bmp");
        iSetColor(0,0,0);
        iText(20, 20, "Press 'r' to go back");
    }

    //about page
    if (window == 3)
    {
        iShowBMP(0, 0, "about.bmp");
        iText(20, 20, "Press 'r' to go back");
    }

    // High Score
    if (window == 4)
    {
        get_score();
        iSetColor(0,255,200);
        iText(180, 450, "Highest Scores :", GLUT_BITMAP_TIMES_ROMAN_24);
        sprintf(h_s, "%d", highscore);
        iSetColor(0,255,200);
        iText(30, 10, "Press 'r' to go back");
        iText(180, 400, str, GLUT_BITMAP_TIMES_ROMAN_24);
        iText(350, 400, h_s, GLUT_BITMAP_TIMES_ROMAN_24);
    }

    //Enter name and gamemode
    if(window ==5)
	{
		iText(200,350,"Please Enter your name.",GLUT_BITMAP_HELVETICA_18);
		iRectangle(160,260,300,50);
		iText(180,280,name);
	}
	//display for paused
    if (pause==1)
		{
		    iSetColor(0,255,0);
			iText (150, 280, "Paused", GLUT_BITMAP_TIMES_ROMAN_24);
			iText (130, 255, "Press Keys To Continue",GLUT_BITMAP_HELVETICA_18);
		}

}


void iMouseMove(int mx, int my) {

}


void iMouse(int button, int state, int mx, int my) {
    if(window==10){
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		if(mx >= 30 && mx <= 180 && my >= 370 && my <= 430 )
		{
			window=2;
		}
		if(mx >= 30 && mx <= 180 && my >= 270 && my <= 330 )
		{
			window=3;
		}
		if(mx >= 30 && mx <= 180 && my >= 170 && my <= 230 )
		{
			window=4;
		}
		if(mx >= 30 && mx <= 180 && my >= 470 && my <= 530 )
		{
			window=5;
		}
		if(mx >= 30 && mx <= 180 && my >= 70 && my <= 130 )
		{
			exit (0);
		}
	}
    }


	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}



void iKeyboard(unsigned char key)
{

	if (window == 5)
	{
		if(key == '\r')
		{
			strcpy(str, name);
			for(i = 0; i < len; i++)
				name[i] = 0;

			window=1;
			len = 0;
			//PlaySound("snake.wav", NULL, SND_LOOP);
            snake_initialization();
		}
		else
		{
			name[len] = key;
			printf("%c", name[len]);
			len++;
		}
	}else if(window==0){
        if(key =='\r'){
            window = 5;
            snake_initialization();
        }
        if(key == 'r'){
            window =10;
        }
	}
	else
	{
		if(window == 1){
            if(key == 'p')
		{
			iPauseTimer(0);

			pause=1;
		}
		}
		if(key == 'r')
		{
			window = 10;
			//PlaySound("snake.wav", NULL, SND_LOOP);
		}
	}
}


void iSpecialKeyboard(unsigned char key) {
if(key== GLUT_KEY_UP)
	{
		if (left==1)
		{

			up=1;
			down=left=right=0;
			iResumeTimer (0);
			pause = 0;
		}
		else if (right==1)
		{
			up=1;
			down=left=right=0;
			iResumeTimer (0);
			pause = 0;
		}
	}
	if(key== GLUT_KEY_DOWN)
	{
		if (left==1)
		{
			down=1;
			up=left=right=0;
			iResumeTimer (0);
            pause = 0;
		}
		else if (right==1)
		{
			down=1;
			up=left=right=0;
			iResumeTimer (0);
            pause = 0;
		}
	}
	if(key== GLUT_KEY_LEFT)
	{
		if (up==1)
		{
			left=1;
			up=down=right=0;
			iResumeTimer (0);
            pause = 0;
		}
		else if (down==1)
		{
			left=1;
			up=down=right=0;
			iResumeTimer (0);
            pause = 0;
		}
	}
	if(key== GLUT_KEY_RIGHT)
	{
		if (up==1)
		{
			right=1;
			up=down=left=0;
			iResumeTimer (0);
			pause = 0;

		}
		else if (down==1)
		{
			right=1;
			up=down=left=0;
			iResumeTimer (0);
            pause = 0;
		}
	}
	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
}



int main() {
	srand(time(NULL));
	//PlaySound("snake.wav", NULL, SND_LOOP);
    snake_initialization();
	iSetTimer(speed, snake_movement);
	//iSetTimer(1000, timer);
	iPauseTimer (0);
	iInitialize(screenWidth, screenHeight, "HOW 2 SNEK");
	return 0;
}
