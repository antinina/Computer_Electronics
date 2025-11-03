#ifndef GRID_H
#define GRID_H
#include <iostream>
using namespace std;

#include <vector>
#include <string>
#include <time.h>

const int SHIP_NUM = 10;
class BattleShips
{
	protected:
		vector<vector<int>> grid_matrix;
		//unsigned char lives = SHIP_NUM;
		unsigned char lives = 1; //test
	public:

		BattleShips();
		
		//vector<vector<int>>& getVector() { return grid_matrix; }
		bool placeShip(int x, int y, int shipType, char orintation = 'h');//sets ships and return true if it's set 
				
		bool isHit(int, int);
        
		bool isPlacable(int _x, int _y, int shipType, char orientation);//checks if ship is placable
		bool coordValid(int x, int y, char ori = 'h');
				
		void printGrid(bool battle_mode = false);//prints grid
		
		void randomGenShips();
		bool randomHit();
		
		void restartGame();
		
		int getLives();
		
		void undo(int _x, int _y, int shipType, char orientation);
		
		
};
#endif