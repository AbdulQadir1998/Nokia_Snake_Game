#include<iostream>
#include<conio.h>
#include<ctime>
#include<Windows.h>
using namespace std;
const int mapwidth=25;
const int mapheight=70;
class Game
{
	private:

		bool flag;
		int food;
		int rows;
		int cols;
		int direction;
		int head_xpos;
		int head_ypos;
		int map[mapwidth][mapheight];

	public:

		Game();
		void initialize_Map();
		void generate_Food();
		void print_Map();
		void change_direction(char);
		void update_Map();
		void move(int,int);
		void process();
};
Game::Game()
{
	this->direction=0;
	this->food=3;
	this->head_xpos=0;
	this->head_ypos=0;
	this->flag=true;
	this->rows=mapwidth;
	this->cols=mapheight;
}
void Game::initialize_Map()
{
	for(int i=0;i<this->rows;i++)
	{
		for(int j=0;j<this->cols;j++)
		{
			this->map[i][j]=0;
		}
	}
	this->head_xpos=this->rows/2;
	this->head_ypos=this->cols/2;
	this->map[this->head_xpos][this->head_ypos]=1;
	for(int i=0;i<this->rows;i++)
	{
		for(int j=0;j<this->cols;j++)
		{
			if(j==0 || j==this->cols-1)
			{
				this->map[i][j]=-1;
			}
			else if(j>=1 && i==0)
			{
				this->map[i][j]=-1;
			}
			else if(i==this->rows-1 && j>=1)
			{
				this->map[i][j]=-1;
			}
		}
	}
	this->generate_Food();
}
void Game::generate_Food()
{
	int x;
	int y;
	do
	{
		x=rand()%(this->rows-2)+1;
		y=rand()%(this->cols-2)+1;
	}while(this->map[x][y]!=0);

	this->map[x][y]=-2;
}
void Game::print_Map()
{
	for(int i=0;i<this->rows;i++)
	{
		for(int j=0;j<this->cols;j++)
		{
			if(this->map[i][j]==-1)
			{
				cout<<"!";
			}
			else if(this->map[i][j]==-2)
			{
				cout<<"O";
			}
			else if(this->map[i][j]>=1)
			{
				cout<<"o";
			}
			else if(this->map[i][j]==0)
			{
				cout<<" ";
			}
		}
		cout<<endl;
	}
}
void Game::change_direction(char key)
{
	/*
      W
    A + D
      S

      0
    3 + 1
      2
    */

	switch(key)
	{
		case 'w':
				 if(this->direction!=2)
					 this->direction=0;
				 break;
		case'd':
				  if(this->direction!=3)
					 this->direction=1;
				 break;
		case'a':
				  if(this->direction!=1)
					 this->direction=3;
				 break;
		case's':
				  if(this->direction!=0)
					 this->direction=2;
				 break;
	}
}
void Game::move(int dx,int dy)
{
	int newx=this->head_xpos+dx;
	int newy=this->head_ypos+dy;
	if(this->map[newx][newy]>=-1 && this->map[newx][newy]!=0)
	{
		this->flag=false;
	}
	else if(this->map[newx][newy]==-2)
	{
		this->food++;
		this->generate_Food();
	}
	this->head_xpos=newx;
	this->head_ypos=newy;
	this->map[this->head_xpos][this->head_ypos]=this->food+1;
}
void Game::update_Map()
{
	switch(this->direction)
	{
		case 0:
			this->move(-1,0);
			break;
		case 1:
			this->move(0,1);
			break;
		case 2:
			this->move(1,0);
			break;
		case 3:
			this->move(0,-1);
			break;
	}
	for(int i=0;i<this->rows;i++)
	{
		for(int j=0;j<this->cols;j++)
		{
			if(this->map[i][j]>=1)
			{
				this->map[i][j]--;
			}
		}
	}
}
void Game::process()
{
	int score=0;
	int times=10;
	this->initialize_Map();
	while(this->flag==true)
	{
		if(_kbhit())
		{
			this->change_direction(_getch());
		}
		this->update_Map();
		system("cls");
		cout<<endl<<endl;
		this->print_Map();
		Sleep(times);
	}
	cout<<endl<<endl;
	score=(this->food-3)*10;
	cout<<">>>>>>>>>>>>>>>>>>GAME OVER>>>>>>>>>>>> "<<endl<<endl<<"YOUR SCORE : "<<score<<endl<<endl;
}
int main()
{
	Game obj;
	obj.process();
	char choice;
	while(1)
	{
		cout<<endl;
		cout<<"Do you want to play again......  (Y/N)"<<endl<<endl;
		cin>>choice;
		if(choice=='n' || choice=='N')
		{
			break;
		}
		else if(choice=='Y' || choice=='y')
		{
			Game obj1;
			obj1.process();
		}
	}
	system("pause");
	return 0;
}