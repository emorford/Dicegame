//Dice
//Emily Morford
//May 25, 2017

#include <iostream>
#include <cstdlib>  //for rand and srand
#include <ctime>  //for time function
#include <vector>
using namespace std;

class Dice
{
	private:
		int num;
	public:
	  void roll();   //this is the set
	  int getNum();
};

void Dice::roll()
{
	num=(rand()%(6 -1 +1)+1);	
}

int Dice::getNum()
	{
		return num;
	}

class Player
{
	private:
		string name;
		int currScore;
		int highScore;
	public:
		string getname();   
		void setname(string);   
		int getcurrScore();   
		void setcurrScore(int);   
		int gethighScore();   
		void sethighScore(int);	
};

string Player::getname()
	{
		return name;
	}
void Player::setname(string n)
	{
		name =n;
	}
int Player::getcurrScore()
	{
		return currScore;
	}
void Player::setcurrScore(int c)
	{
		currScore =c;
	}
int Player::gethighScore()
	{
		return highScore;
	}
void Player::sethighScore(int h)
	{
		highScore =h;
	}
	
void printRules();
//void setHighScorestoZero(int, Player *);	

int main()
{
	
//declare variables

int number=4;          
//int number=0    // I wanted to let the player choose this number but as seen below I commented it out. I'm not sure why it caused an error when I tried to put it in
Player player[number];
//vector <Player> player;  //I don't understand how to initialize the elements

Dice dice1;
string name;
int num, currScore=0, highScore=0, x, y, z;
char choice, decision;

//get the system time
unsigned seed = time (0);

//seed the random number generator
srand(seed);

printRules();

//setHighScorestoZero(number, & player[]);  //couldn't get to work

//loop to set highest scores to 0
for (  x=0; x<number; x++)
{
	player[x].sethighScore(0);
}

//loop to collect player names
for (x=0; x<number; x++)
{
	cout << "Enter your name player #"<<x+1<<":  " ;
	getline(cin, name);
	player[x].setname(name);
	//cout << player[x].getname()<<"\n" ;
}

cout<<"\n\n";

do
{

//loop to set current scores to 0
for (x=0; x<number; x++)
{
	player[x].setcurrScore(0);
}

//loop to roll die first time for each player
for (x=0; x<number; x++)
{
	cout << "Time for your first roll player #"<<x+1<<" , " <<player[x].getname()<<"!\t\t";
	dice1.roll();
	y=dice1.getNum();
	cout<<"You rolled a "<< y <<" .\n";
	z= y + player[x].getcurrScore();
	player[x].setcurrScore(z);
}
cout<<"\n\n";

//loop to continue rolling	
//outer loop cycles through nine more times
for(int a=2; a<11; a++)
{
	//one turn for each player
	for (x=0; x<number; x++)
	{
	cout <<"\t"<< player[x].getname()<< " your current score is : " <<player[x].getcurrScore()<<"\t";
	cout << "Time for roll #"<<a<<", " <<player[x].getname()<<"!\t";
	dice1.roll();
	y=dice1.getNum();
	cout<<"You rolled a "<< y <<" .\n";
	cout << "Would you like to add or multiply to your total? Enter A or M:  \t";
	cin>>choice;
	//validate choice
		while  ( (!(choice=='a'))&&(!(choice=='A'))&&(!(choice=='M'))&&(!(choice=='m')))
	{
	cout <<"\nPlease enter A or M\t" <<endl;
	cin>> choice;
	}	
	
	switch(choice)
	{
		case 'A': case 'a':
			z= y + player[x].getcurrScore();
			player[x].setcurrScore(z);
			cout <<"\t"<< player[x].getname()<< " your new score is : " <<player[x].getcurrScore()<<"\n\n";	
			break;
		case 'M': case 'm':
			z= y * player[x].getcurrScore();
			player[x].setcurrScore(z);
			cout <<"\t"<< player[x].getname()<< " your new score is : " <<player[x].getcurrScore()<<"\n\n";	
			break;
	}
 }
}

//find maximum score--must be at most 1000
int maxval=0;
for (x=0; x<number; x++)
{
	if ((player[x].getcurrScore() > maxval)&&(player[x].getcurrScore() <= 1000))
	{
	 maxval=player[x].getcurrScore();
	}
}

//find number of players with the maximum score
int counter =0;
	for (x=0; x<number; x++){
		if ( maxval == player[x].getcurrScore() ){
			counter++;
		//	cout<< counter<<endl; 
		}
	}
	
//list the winners	
if (counter==1)
{for (x=0; x<number; x++)
{
	if (player[x].getcurrScore() == maxval)
	 {cout<<"The winner is "<<player[x].getname() << " with a score of "<< player[x].getcurrScore()<< endl;	}
}}
else
{cout<<"The winners with a score of "<< maxval<<  " are:\n ";
for (x=0; x<number; x++)
{
	if (player[x].getcurrScore() == maxval)
	 {cout<<player[x].getname() << " \n ";	}	
}
}

//store high scores             //I'm not really sure if I am using high score for the correct purpose
for (x=0; x<number; x++)     
{
	player[x].getcurrScore();
	y=player[x].getcurrScore();
	//cout<< y<<endl;
	if ((y> player[x].gethighScore())&&(y<=1000))
	      {player[x].sethighScore(y);}
	cout << player[x].gethighScore()<<endl;  
}

 cout << "Would you like to play again? Enter Y for yes or N for no\t";
 cin  >> decision;
 while  ( (!(decision=='y'))&&(!(decision=='n'))&&(!(decision=='Y'))&&(!(decision=='N')))
	{
	cout <<"\nPlease enter Y or N\t" <<endl;
	cin>> decision;
	}	
	cin.ignore(100,'\n');
if ((decision=='n')or (decision=='N'))
{
	cout<< "Goodbye!";
	exit(0);
	
}
}

while (!(player[0].gethighScore()==0));

return 0;	
}

void printRules()
{
	//game rules
	cout << "\t\t\tTHE CLOSEST TO 1000 DICE GAME!!\n\n" ;
	cout << "Goal: You will roll ten times. Each time choose whether to add or multiply to your current total\n" ;
	cout << "The winner is the player that has a score from the ten dice rolls closest to 1000 without going over\n\n" ;
//	cout << "How many players will play the game? choose from 1 to 10\n";
//	cin >> number;
//	cout << number;
}

/*void setHighScorestoZero (int number, Player* player[] )
//loop to set highest scores to 0
{for ( int x=0; x<number; x++)
{
	player[x]->sethighScore(0);
}
}*/


