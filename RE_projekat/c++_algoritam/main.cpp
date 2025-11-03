#include <iostream>
using namespace std;
#include "BattleShips.h"


#include<unistd.h>
#include <time.h>

typedef enum game_states {init, place_ships, players_turn, comps_turn, the_end}game_states;

int main()
{	
	//def
	game_states state = init;
	int row, col;
	int shipNum = 0;
	int cell = 0;
	char ori = 'h'; char tmp;
	bool game = true;
	BattleShips player;
	BattleShips comp;
	//--
	do{
	cout<<"______________________________________________"<<endl;		
	switch(state)
	{	
		case init:
		
		shipNum = 10;
		cout<<"AAy! Captain, the battle is on!"<<endl;
		comp.randomGenShips();
		state = place_ships;
		break;
		
		case place_ships:
		cout<<"Let's place submarines first"<<endl;
		cell = 3;
		while(cell>0)
		{
			cout<<"Enter the coordinates:( 1->10 )"<<endl;
			cout<<"Row->";
			cin>>row;
			cout<<"Column->";
			cin>>col;
			cout<<endl;
			if(player.coordValid(row,col)){
				if(player.placeShip(row, col, 1))cell--;
				else cout<<"No NO NOOO"<<endl;
				cout<<"Submarines: placed "<<3-cell<<"/3"<<endl;
				player.printGrid();
			}
		}
		
		cout<<"Now, place the cruisers!"<<endl;
		cell = 2;
		while(cell>0)
		{
			cout<<"Enter the coordinates:( 1->10 )"<<endl;
			cout<<"Row->";
			cin>>row;
			cout<<"Column->";
			cin>>col;
			cout<<"Horizontal/vertical('h'/'v')->";
			cin>>ori;
			cout<<endl;
			
			if(player.coordValid(row,col)){
				if(player.placeShip(row, col, 2, ori))cell--;
				else cout<<"No NO NOOO"<<endl;
				cout<<"Cruisers: placed "<<2-cell<<"/2"<<endl;
				player.printGrid();
			}
		}
		
		cout<<"Battle ship!"<<endl;
		cell = 1;
		while(cell>0)
		{
			cout<<"Enter the coordinates:( 1->10 )"<<endl;
			cout<<"Row->";
			cin>>row;
			cout<<"Column->";
			cin>>col;
			cout<<"Horizontal/vertical('h'/'v')->";
			cin>>ori;
			cout<<endl;
			if(player.coordValid(row,col,ori)){
				if(player.placeShip(row, col, 3, ori))cell--;
				else cout<<"Can not be placed"<<endl;
				cout<<"Battle ship? "<<1-cell<<"/1"<<endl;
			}
			
			player.printGrid();
		}
		cout<<"Ships are placed! Let the games begin!"<<endl;
		player.printGrid();
		state = players_turn;
		break;
		
		case players_turn:
		cout<<"Locating the enemy...."<<endl;
		cout<<"Enter the coordinates:( 1->10 )"<<endl;
		cout<<"Row->";
		cin>>row;
		cout<<"Column->";
		cin>>col;
		if(player.coordValid(row,col)){
			if(comp.isHit(row,col))
			{
				cout<<"Hooray!"<<endl;
				if(comp.getLives()!=0)state = players_turn;
				else if(comp.getLives()==0)state=the_end;
			}
			else
			{	
				cout <<"Enemy: Is that all you got?!"<<endl;
				state = comps_turn;	
			}
			cout<<"********Computer*********"<<endl;
			comp.printGrid(true);
		}
		break;
		case comps_turn:
		if(player.randomHit()){
			cout<<"Nooo! :("<<endl;
				if(player.getLives()!=0)state = comps_turn;
				else if(player.getLives()==0)state=the_end;
			
		}
			else
			{	
				cout <<"Captain: Nice try!"<<endl;
				state = players_turn;	
			}
			cout<<"********Player*********"<<endl;	
			player.printGrid(true);

		break;
		case the_end:
		if(comp.getLives()==0)cout<<"Hooray! You won!!!"<<endl;
		else if(player.getLives()==0)cout<<"...The winner takes it all... :("<<endl;
		cout<<"New game ('y'/'n') ";
		cin>>tmp;
		game = (tmp == 'n') ? false : true;
		if(tmp == 'y')state = init;
		
		break;
		default:
		cout<<"Ooops!"<<endl;
		break;
	}

	}while(game);
	
	return 0;
}