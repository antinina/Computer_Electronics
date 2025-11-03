#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H


const int SHIP_NUM = 20;
const int GRID_MAX = 9; //last index in row/column
const int GRID_MIN = 0;

class BattleShips
{
    protected:
		int grid_matrix[GRID_MAX + 1][GRID_MAX + 1];    
		unsigned char lives = SHIP_NUM;
	
    public:

        BattleShips();
		//places the certain type of ship in the grid, returns true if it's placed succesfully
        bool placeShip(int x, int y, int shipType = 1, char orintation = 'h');
		
		//checks if the ship is placable
		bool isPlacable(int _x, int _y, int shipType, char orientation);//checks if ship is placable
		
		//erases the certain kind of ship from place with coordinates (_x, _y)
		void undo(int _x, int _y, int shipType=1, char orientation='h');
		
		//returns true if the ship is hit by opponent
        bool isHit(int x, int y);              
		
		//actually, that's what it does
		int generateRandomNumbers();
		
		//places ships on random coordinates, returns true when it is finished
        bool randomGenShips();
		
		//getter methods:
        int getLives();
        int getCellValue(int x, int y);
        
		//sets grid_matrix & lives to default values
        void restartGame();


};
#endif // BATTLESHIPS_H
