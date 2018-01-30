#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>

#define startx 50
#define starty 50


union REGS input,output;

char array[9][9]= {{' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ','R','N','B','K','Q','B','N','R'},{' ','P','P','P','P','P','P','P','P'},{' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ','p','p','p','p','p','p','p','p'},{' ','r','n','b','k','q','b','n','r'}};


void drawboard();
void fillpiece();
void pawnR(int a, int b);
void pawnG(int a, int b);
void kingR(int a, int b);
void kingG(int a, int b);
void queenR(int a, int b);
void queenG(int a, int b);
void knightR(int a, int b);
void knightG(int a, int b);
void bishopR(int a, int b);
void bishopG(int a, int b);
void rookR(int a, int b);
void rookG(int a, int b);
int get_key();
void getmousepos(int *button,int *x, int *y);
void intro();

main()
{


struct {
	   int lastx;
	   int lasty;
	   int newx;
	   int newy;
	   char eatenpiece;
		 } move[500];



   int gd = 0, gm,key,button,x,y,px,py,color,i=0,*counter = 0, tempx, tempy;
   char c;


    initgraph(&gd,&gm,"C:\\TC\\BGI");

     intro();

cleardevice();

   drawboard();
   fillpiece();

    input.x.ax =1;
    int86(0x33,&input,&output);
    outtextxy(500,100,"Player 1");
     while(1)
       {
	    if(kbhit())
	       {
		 key = get_key();
		 if(key==1)
		                {
			closegraph();
			break;
		                }
	       }

	    getmousepos(&button,&x,&y);

	     if(i%2==0)
		 outtextxy(500,100,"Player 1");
                       else
		 outtextxy(500,100,"Player 2");

	    if(button==1)
	      {

		    px= x/50;
		    py= y/50;
		    cleardevice();
		    drawboard();
		
		    color = getcolor();

		     if(x>500 && y > 250 && x<550 && y<300)
		              {
	    		   i--;
	      		   array[move[i].lasty][move[i].lastx]  = array[move[i].newy][move[i].newx];
			   array[move[i].newy][move[i].newx]  = move[i].eatenpiece;
  			   cleardevice();
	       		  drawboard();
	      		  fillpiece();

	  	              }



		   if(x>500&&x<550&&y>400&&y<450)
		            {
			cleardevice();
			outtextxy(50,120,"Are you sure you want to resign?,press 'y' if yes and press 'n' if no.");
			scanf("%c",&c);
			if(c=='y')
		                             {
			              cleardevice();
		                                 break;
			           }
			else
			          {
			                 cleardevice();
			                 drawboard();
			                  fillpiece();
			          }
		           }


		    if((x>startx && y>starty && x< 450&& y< 450) )
		         {     
		                if(*counter==0)
		                     {
		                         setcolor(RED);
		                         rectangle( px*50,py*50,(px+1)*50,(py+1)*50);
			                    setcolor(RED);
		                        rectangle( px*50+2,py*50+2,(px+1)*50-2,(py+1)*50-2);
			                     setcolor(RED);
		                         rectangle( px*50+4,py*50+4,(px+1)*50-4,(py+1)*50-4);
		                         if(array[py][px]==' ')
		                                     goto sidepath;

		                      *counter = 1;
		                       tempx = px;
		                       tempy = py;
		                      move[i].lastx = tempx;
		                      move[i].lasty = tempy;
		                    }


		                 else
		  	  {
                    
		     	move[i].eatenpiece = array[py][px];
				if(array[py][px]!=array[tempy][tempx])
				{
				array[py][px]= array[tempy][tempx];
				 array[tempy][tempx] = '  ';
				 }
			   	move[i].newx=px;
		   		move[i].newy =py;
		  		 i++;
				 sidepath:

		    		setcolor(GREEN);
		   		 rectangle( px*50,py*50,(px+1)*50,(py+1)*50);
				    setcolor(GREEN);
		   		 rectangle( px*50+2,py*50+2,(px+1)*50-2,(py+1)*50-2);
			    	setcolor(GREEN);
		  		  rectangle( px*50+4,py*50+4,(px+1)*50-4,(py+1)*50-4);
		    		*counter = 0;
		   	 }
		    }

		    setcolor(color);
		     delay(1000);
		    fillpiece();
		   }
	  if(i<0)
	  i=0;






       }

  char message[50];
  sprintf(message,"player %d is winner",2-i%2);
  outtextxy(200,200,message);
    getch();
   return 0;
}


void drawboard()
{
   int i,j;
   setfillstyle(SOLID_FILL,BLUE);
   bar(0,0,getmaxx(), getmaxy());

   setfillstyle(SOLID_FILL,BLACK);
   bar(startx,starty,450,450);
    setfillstyle(SOLID_FILL, WHITE);

   for(i=5;i<=15;i+=5)
   {
    setcolor(i);
    rectangle(startx-i,starty-i,startx+400+i,starty+400+i);
    }




   for(j=0;j<=3;j++)
   {
   for(i=0;i<=3;i++)
   {
   bar(startx+100*i,starty+100*j,startx+50+100*i,starty+50+100*j);
   }
   }



    for(j=0;j<=3;j++)
   {
   for(i=0;i<=3;i++)
   {
   bar(startx+50+100*i,starty+50+100*j,startx+100+100*i,starty+100+100*j);
   }
   }

   bar(500,250,550,300);
   bar(500,400,550,450);
   setcolor(RED);
   outtextxy(515,270,"UNDO");
   outtextxy(502,420,"RESIGN");

}


void fillpiece()
{
  int p,k;
  for(p=1;p<=8;p++)
	{
	for(k=1;k<=8;k++)
	{
	  switch(array[k][p])
	  {
	    case 'K' : kingR(p,k);
    break;
	    case 'Q' : queenR(p,k);
break;
	    case 'B' : bishopR(p,k);
break;
	    case 'R' : rookR(p,k);
	 break;
	    case 'N' : knightR(p,k);
	   break;
	    case 'P' : pawnR(p,k);
	    break;
	    case 'k' : kingG(p,k);
	    break;
	    case 'q' : queenG(p,k);
	    break;
	    case 'b' : bishopG(p,k);
	    break;
	    case 'r' : rookG(p,k);
	    break;
	    case 'n' : knightG(p,k);
	    break;
	    case 'p' : pawnG(p,k);


      }
    }
	}
}

void pawnR(int a, int b)
{
setcolor(RED);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,10);
}

void pawnG(int a, int b)
{
setcolor(GREEN);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,10);
}


void queenR(int a, int b)
{
setcolor(RED);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,10);
line(startx+(a-1)*50+15,starty+25+(b-1)*50,startx+(a-1)*50+35,starty+25+(b-1)*50);
line(startx+(a-1)*50+25,starty+15+(b-1)*50,startx+(a-1)*50+25,starty+35+(b-1)*50);
line(startx+(a-1)*50+15,starty+25+(b-1)*50,startx+(a-1)*50+25,starty+35+(b-1)*50);
line(startx+(a-1)*50+25,starty+15+(b-1)*50,startx+(a-1)*50+35,starty+25+(b-1)*50);
line(startx+(a-1)*50+15,starty+25+(b-1)*50,startx+(a-1)*50+25,starty+15+(b-1)*50);
line(startx+(a-1)*50+25,starty+35+(b-1)*50,startx+(a-1)*50+35,starty+25+(b-1)*50);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,20);
}

void queenG(int a, int b)
{
setcolor(GREEN);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,10);
line(startx+(a-1)*50+15,starty+25+(b-1)*50,startx+(a-1)*50+35,starty+25+(b-1)*50);
line(startx+(a-1)*50+25,starty+15+(b-1)*50,startx+(a-1)*50+25,starty+35+(b-1)*50);
line(startx+(a-1)*50+15,starty+25+(b-1)*50,startx+(a-1)*50+25,starty+35+(b-1)*50);
line(startx+(a-1)*50+25,starty+15+(b-1)*50,startx+(a-1)*50+35,starty+25+(b-1)*50);
line(startx+(a-1)*50+15,starty+25+(b-1)*50,startx+(a-1)*50+25,starty+15+(b-1)*50);
line(startx+(a-1)*50+25,starty+35+(b-1)*50,startx+(a-1)*50+35,starty+25+(b-1)*50);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,20);
}

void kingR(int a, int b)
{
setcolor(RED);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,10);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,20);
outtextxy(startx+22+(a-1)*50,starty+22+(b-1)*50,"K");
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,22);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,12);
}

void kingG(int a, int b)
{
setcolor(GREEN);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,10);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,20);
outtextxy(startx+22+(a-1)*50,starty+22+(b-1)*50,"K");
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,22);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,12);

}

void knightR(int a, int b)
{
setcolor(RED);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,10);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,20);
outtextxy(startx+22+(a-1)*50,starty+22+(b-1)*50,"H");
}

void knightG(int a, int b)
{
setcolor(GREEN);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,10);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,20);
outtextxy(startx+22+(a-1)*50,starty+22+(b-1)*50,"H");
}


void bishopR(int a, int b)
{
setcolor(RED);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,20);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,10);
}

void bishopG(int a, int b)
{
setcolor(GREEN);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,20);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,10);
}

void rookR(int a, int b)
{
setcolor(RED);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,10);
rectangle(startx+5+(a-1)*50,starty+5+(b-1)*50,startx+45+(a-1)*50,starty+45+(b-1)*50);
}

void rookG(int a, int b)
{
setcolor(GREEN);
circle(startx+25+(a-1)*50,starty+25+(b-1)*50,10);
rectangle(startx+5+(a-1)*50,starty+5+(b-1)*50,startx+45+(a-1)*50,starty+45+(b-1)*50);
}


int get_key()
{
union REGS input,output;
input.h.ah=0;
int86(22,&input,&output);
return(output.h.ah);
}


void getmousepos(int *button,int *x, int *y)
{
 input.x.ax=3;
 int86(0x33,&input,&output);
 *button = output.x.bx;
 *x = output.x.cx;
 *y=output.x.dx;
}

void intro()
{
int i;
for(i=1;i<=getmaxx();i+=5)
{
setcolor(i/2+2);
line(i,0,i,getmaxy());
}
delay(1000);
}
