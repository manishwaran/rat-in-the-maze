#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
int move[8][2]={0,1,1,1,1,0,1,-1,0,-1,-1,-1,-1,0,-1,1};
int grid[12][12],x,y,r1,r2,c1,c2,dis[200],maxx,maxy,midx,midy,mark[25][25],stack[150][3],top;
char *msg;
void setpage();
void manish();
void wall();
void wall1();
int get1(int range);
int shortdistance();
void fun();
int tracer();
void show();
void main()
{
	clrscr();
	int gd=DETECT,gm,co,c;
	initgraph(&gd,&gm,"..\\bgi");
	maxx=getmaxx();
	maxy=getmaxy();
	midx=maxx/2;
	midy=maxy/2;
	manish();
	do
	{
		cleardevice();
		setpage();
		settextstyle(4,0,4);
		setcolor(4);
		outtextxy(midx-textwidth("YOUR WISH !")/2+40,18,"YOUR WISH !");
		settextstyle(3,0,2);setcolor(5);
		outtextxy(40,80,"1 - FINDING SHORTEST");
		outtextxy(midx+40,80,":");
		outtextxy(40,140,"2 - RAT IN A MAZE");
		outtextxy(midx+40,140,":");
		outtextxy(40,200,"3 - EXIT");
		outtextxy(midx+40,200,":");
		outtextxy(40,260,"YOUR CHOICE PLEASE");
		outtextxy(midx+40,260,":");
		c=get1(3);
		sprintf(msg,"%d",c);
		setcolor(3);
		outtextxy(midx+60,260,msg);
		delay(1000);
		switch(c)
		{
			case 1:
				wall();
				show();
				fun();
				show();
				shortdistance();
				break;
			case 2:
				cleardevice();
				wall1();
				show();
				fun();
				tracer();
				break;
			case 3:
				goto x;
		}
		cleardevice();
		setpage();
		settextstyle(3,0,4);
		setcolor(13);
		outtextxy(midx-textwidth("TO CONTINUE PRESS 1 :")/2,190,"TO CONTINUE PRESS 1 :");
		co=get1(1000);
		sprintf(msg,"%d",co);
		setcolor(3);
		outtextxy(510,190,msg);
		delay(1000);
   }while(co==1);
		x:
		cleardevice();
		setpage();
		settextstyle(4,0,8);
		setcolor(14);
		outtextxy(midx-textwidth("THANK YOU")/2,180,"THANK YOU");
		getch();
}

void show()
{
	clrscr();
	cleardevice();
	setbkcolor(BLACK);
	setcolor(4);
	int x1,y1,x2,y2,box=27;
	x1=15;y1=22;x2=box+15;y2=box+15;
	for(int m=0;m<x+2;m++)
	{
		for(int n=0,dx=0,dy=0;n<y+2;n++,dx++,dy++)
		{
		    if(grid[m][n]==1)
		       setfillstyle(LTBKSLASH_FILL,RED);
		    else if(grid[m][n]==888||grid[m][n]==2)
		       setfillstyle(LTBKSLASH_FILL,MAGENTA);
		    else if(grid[m][n]==333)
		       setfillstyle(LTBKSLASH_FILL,LIGHTGRAY);
		    else if(grid[m][n]==666)
		       setfillstyle(LTBKSLASH_FILL,GREEN);
		    else
		       setfillstyle(LTBKSLASH_FILL,YELLOW);
		    bar3d(x1,y1,x2,y2,(x2-x1)/8,1);
		    x1+=box+5;
		    x2+=box+5;
		    if(m==0)
		    {
			   if(n==0)
				  cout<<dx+1<<"      ";
			   else
				  cout<<dy+1<<"   ";
		    }
		}
		y1=y1+box+5;
		y2=y2+box+5;
		x1=15;
		x2=box+15;
		if(m==0)
			cout<<"\n\n\n";
		else
			cout<<m+1<<"\n\n";
	}
	delay(450);
}

void setpage()
{
	setbkcolor(BLACK);
	setcolor(WHITE);
	setlinestyle(0,0,1);
	settextstyle(1,0,4);
	rectangle(0,0,maxx,maxy);
	rectangle(3,3,maxx-3,maxy-3);
}
int get1(int range)
{
	int itemp,i=0,rescl;
	char ctemp[3];
	while(i<3)
	{
		ctemp[i++]='\0';
	}
	i=0;
	while(i<3)
	{
		ctemp[i++]=getch();
		if(ctemp[1]==13||ctemp[1]==32)
			break;
	}
	if((ctemp[0]>48&&ctemp[0]<58)&&((ctemp[1]>47&&ctemp[1]<58||ctemp[1]==13||ctemp[1]==10||ctemp[1]==32))&&(atoi(ctemp)>0&&atoi(ctemp)<=range))
	{
		itemp=atoi(ctemp);
	}
	else
	{
		setcolor(15);
		sprintf(msg,"INPUT ERROR !!!");
		outtextxy((maxx/2)-(textwidth("INPUT ERROR !!!")/2),maxy-100,msg);
		delay(500);
		rescl=getbkcolor();
		setcolor(2);
		setcolor(rescl);outtextxy((maxx/2)-(textwidth("INPUT ERROR !!!")/2),maxy-100,msg);
		setcolor(15);
		sprintf(msg,"GIVE INPUT IN BETWEEN 0 AND %d",range+1);
		outtextxy((maxx/2)-(textwidth(msg)/2),maxy-100,msg);
		delay(500);
		rescl=getbkcolor();
		setcolor(2);
		setcolor(rescl);outtextxy((maxx/2)-(textwidth(msg)/2),maxy-100,msg);
		setcolor(GREEN);
		itemp=get1(range);
	}
	return(itemp);
}
void manish()
{
	setpage();
	setcolor(4);
	outtextxy(midx-textwidth("RAT     IN    A     MAZE")/2,midy-170,"RAT     IN    A     MAZE");delay(500);setpage();
	outtextxy(midx-textwidth("DEVELOPED BY")/2,midy-120,"DEVELOPED BY");delay(400);
	setlinestyle(1,1,2);
	rectangle(midx-220,midy-60,midx+220,midy+60);
	for(int p=0;p<15;p++)
	{
		setcolor(p);
		settextstyle(4,0,8);
		outtextxy(midx-textwidth("MANISH")/2,midy-50,"MANISH");delay(200);
		sound(350);
	}
	nosound();
	getch();
}
void wall()
{
	cleardevice();
	setpage();
	int tem;
	settextstyle(4,0,4);
	setcolor(4);
	outtextxy(midx-textwidth("YOUR SPECIFICATION")/2,50,"YOUR SPECIFICATION");
	settextstyle(3,0,2);
	setcolor(5);
	outtextxy(40,120,"ROW >0 AND ROW <=10");
	outtextxy(midx+50,120,":");
	x=get1(10);
	setcolor(3);sprintf(msg,"%d",x);
	outtextxy(midx+90,120,msg);
	setcolor(5);
	outtextxy(40,190,"COLUMN >0 AND COLUMN <=10");
	outtextxy(midx+50,190,":");
	y=get1(10);
	setcolor(3);
	sprintf(msg,"%d",y);
	outtextxy(midx+90,190,msg);
	delay(1000);
	for(int i=0;i<x+2;i++)
	   for(int j=0;j<y+2;j++)
		grid[i][j]=0;
	for(j=0;j<y+2||j<x+2;j++)
	{
		grid[0][j]=1;
		grid[j][0]=1;
		grid[x+1][j]=1;
		grid[j][y+1]=1;
	}
	do
	{
		randomize();
		for(i=1;i<x+1;i++)
		   for(j=1;j<y+1;j++)
			grid[i][j]=random(3)%2;
		show();
		settextstyle(3,0,3);
		setcolor(7);
		outtextxy(400,150,"NOT SATISFIED ?");
		setcolor(9);
		outtextxy(400,200,"PRESS 1 :");
		tem=get1(100);
		setcolor(10);
		sprintf(msg,"%d",tem);
		outtextxy(530,200,msg);
		delay(1000);
		cleardevice();
	}while(tem==1);
}
void fun()
{
	do
	{
		cleardevice();
		show();
		settextstyle(3,0,2);
		setcolor(13);
		outtextxy(400,150,"START VALUE");
		r1=get1(12);
		setcolor(3);
		sprintf(msg,": (%d",r1);
		outtextxy(400,200,msg);
		c1=get1(12);
		sprintf(msg,": (%d,%d)",r1,c1);
		outtextxy(400,200,msg);
		delay(1000);
		r1--,c1--;
		if(grid[r1][c1]==1)
		{
			setcolor(15);
			settextstyle(2,0,5);
			outtextxy(400,250,"BLOCKED POSITION");
			delay(1000);
			setcolor(10);
			outtextxy(400,250,"BLOCKED POSITION");
			delay(1000);
		}
	}while(grid[r1][c1]==1);
	grid[r1][c1]=2;
	do
	{
		show();
		settextstyle(3,0,2);
		setcolor(13);
		outtextxy(400,150,"FINISH VALUE");
		r2=get1(12);
		setcolor(3);
		sprintf(msg,": (%d",r2);
		outtextxy(400,200,msg);
		c2=get1(12);
		sprintf(msg,": (%d,%d)",r2,c2);
		outtextxy(400,200,msg);
		delay(1000);
		r2--,c2--;
		if(grid[r2][c2]==1)
		{
			setcolor(15);
			settextstyle(2,0,5);
			outtextxy(400,250,"BLOCKED POSITION");
			delay(1000);
			setcolor(10);
			outtextxy(400,250,"BLOCKED POSITION");
			delay(1000);
		}
	}while(grid[r2][c2]==1);
}
int shortdistance()
{
	int m=1,k,o=0,d[100][2];
	grid[r1][c1]=2;
	for(int l=0;l<(x+2)*(y+2);l++)
	{
		m++;
		for(int i=0;i<x+2;i++)
			for(int j=0;j<y+2;j++)
			{
				if(grid[i][j]==m)
				{
				       for(k=0;k<8;k++)
					{
						if(grid[i+move[k][0]][j+move[k][1]]==0)
							grid[i+move[k][0]][j+move[k][1]]=m+1;
					}
				}
			}
	}
	m=grid[r2][c2];
	if(m==0)
	{
		settextstyle(4,0,4);
		setcolor(3);
		outtextxy(40,380,"NO PATH FOUND");
		getch();
		return 0;
	}
	m--;
	d[o][0]=r2,d[o][1]=c2;
	o++;
	for(int i=r2,j=c2;(i!=r1)||(j!=c1);o++)
	{
		for( k=0;k<8;k++)
		{
			if(grid[i+move[k][0]][j+move[k][1]]==m)
			{
				i=i+move[k][0];
				j=j+move[k][1];
				d[o][0]=i;
				d[o][1]=j;
				m--;
				break;
			}
		}
	}
	d[o][0]=r1,d[o][1]=c1;
	grid[r2][c2]=888;
	for(k=0;k<o;k++)
		grid[d[k][0]][d[k][1]]=888;
	show();
	settextstyle(4,0,4);
	setcolor(3);
	outtextxy(40,380,"PATH LENGTH");
	outtextxy(midx+40,380,"=");
	sprintf(msg,"%d",o);
	outtextxy(midx+80,380,msg);
	getch();
}
void wall1()
{
	wall();
	for(int i=0;i<x+2;i++)
		for(int j=0;j<y+2;j++)
			mark[i][j]=0;
	for(i=0;i<x+2;i++)
		for(j=0;j<y+2;j++)
		{
			mark[0][j]=1;
			mark[i][0]=1;
			mark[x+1][i]=1;
			mark[j][y+1]=1;
		}
}
int tracer()
{
	int i,j,g,h,dir;
	grid[r1][c1]=888;
	grid[r2][c2]=666;
	show();
	stack[0][0]=r1,stack[0][1]=c1,stack[0][2]=0;
	top=1;
	int t=1;
	while(top>0)
	{
		if(t>1)
		{
			grid[stack[top][0]][stack[top][1]]=333;
			show();
		}
		top=top-1;
		i=stack[top][0];
		j=stack[top][1];
		if(t>1)
			grid[i][j]=333;
		t++;
		dir=stack[top][2];
		for(;dir<8;dir++)
		{
			g=i+move[dir][0];
			h=j+move[dir][1];
			if(g==r2&&h==c2)
			{
				grid[r2][c2]=888;
				show();
				settextstyle(4,0,4);
				setcolor(3);
				outtextxy(40,400,"DESTINATION IS REACHED !");
				getch();
				return 0;
			}
			if(grid[g][h]==0&&mark[g][h]==0)
			{
				mark[g][h]=1;
				top=top+1;
				stack[top][0]=g,stack[top][1]=h,stack[top][2]=dir;
				i=g,j=h,dir=-1;
				grid[stack[top][0]][stack[top][1]]=888;
				show();
			}
		}
	}
	if(top==0)
	{
		settextstyle(4,0,4);
		setcolor(3);
		outtextxy(40,400,"NO PATH FOUND !");
		getch();
	}
}


