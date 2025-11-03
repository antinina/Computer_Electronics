#include <iostream>
using namespace std;
#include "BattleShips.h"

const int GRID_MAX = 10;
const int GRID_MIN = 1;
//Legend: 0 -> initial, 1 -> submarine, 2 -> cruiser /3 battle ship 4 /, 5 -> hit, 6 -> miss

BattleShips::BattleShips()
{
	grid_matrix.resize(GRID_MAX+1, vector < int >(GRID_MAX+1, 0));//creates grid with 0's in it
	cout<<"matrix created..."<<endl;
}

void BattleShips::printGrid(bool battle_mode) //prints grid
{
	//battle mode -> prints only 'X'(hit), 'O'(miss) & '_'
	cout << "--------------------------------------------" << endl;
	cout << "   1  2  3  4  5  6  7  8  9  10" << endl;
	cout << "--------------------------------------------" << endl;
	for (int i = 1; i <=GRID_MAX; i++) { // rows
	cout << " " << i<<"  ";
		for (int j = 1; j <= GRID_MAX; j++) { // columns
			if(j!=1)	cout <<" ";
			if(battle_mode)
			{	switch(grid_matrix[i][j])
				{
					case 0:	//initial
						cout<<"_";
					break;
					case 1: //submarine
						cout<<"_";
					break;
					case 2: //cruiser
						cout<<"_";
					break;
					case 3: //battle ship
						cout<<"_";
					break;
					case 4: //carrier
						cout<<"_";
					break;
					case 5://hit
						cout<<"X";
					break;
					case 6://miss
						cout<<"O";
					break;
					default:
					cout<<"Ooops!";
					break;
				}
			}
				else 	cout<<grid_matrix[i][j];
				cout<< " ";
		}
		cout << endl;
	}
	cout << "--------------------------------------------" << endl;
}

bool BattleShips :: isPlacable(int _x, int _y, int shipType, char orientation)
{
    bool placable = true;
    int x = _x, y = _y;
    int len = shipType;

    if(orientation=='h')
    {
		if( y+shipType-1 <= GRID_MAX )
		{
            if( _y > 0 )
			{
				y--;
				len++;
			}
            if( (_y+len-1) < GRID_MAX )
				len++; 

            for(int i = 0; i<len ; i++)
            {            
				//checking: current cell, cell on the left, -||- right 
                if(grid_matrix[max(x-1,GRID_MIN)][y]!=0 || grid_matrix[x][y]!=0 ||  grid_matrix[min(x+1,GRID_MAX)][y]!=0 )
                    placable = false;
                
                if(y < GRID_MAX)
                    y++;
				
            }
        }
        else
            placable = false;
    }

    else if(orientation=='v')
    {	
		if( x+shipType-1 <= GRID_MAX )
		{            
            if( _x > 0 )
			{
				x--;
				len++;
			}
            if( (_x+len-1) < GRID_MAX )
				len++;              
            for(int i = 0; i<len ; i++)
            {
				//checking: current cell, cell on the above, -||- beneath 
                if(grid_matrix[x][max(y-1,GRID_MIN)]!=0 || grid_matrix[x][y]!=0 ||  grid_matrix[x][min(y+1,GRID_MAX)]!=0 )                    
					placable = false;
			
                if(x<GRID_MAX)
                    x++;
				
            }
        }
        else
            placable = false;
    }
    
    return placable;
}

bool BattleShips :: placeShip(int x, int y, int shipType, char orientation)//sees if ships are placable
{

    bool isPlaced = false; 
    int xi=x;
    int yi=y;
    int it = shipType;
    
    if (xi <= GRID_MAX && yi <= GRID_MAX )
    {
        if(isPlacable(xi,yi,shipType,orientation))
        {
            while(it>0)
            {
                grid_matrix[xi][yi] = shipType;
                if(orientation == 'h')yi++;
                else if(orientation == 'v')xi++;
                it--;
            }
            isPlaced = true;
        }
    }

    
    return isPlaced;
}



int generateRandomNumbers() {
	return rand() % GRID_MAX; // number from 0 to GRID_MAX - 1
	
}
int GenOrient()
{
    srand(time(NULL));
    return  rand()%2;
}

void BattleShips :: randomGenShips()
{
		int x = generateRandomNumbers();
		int y = generateRandomNumbers();
		char orient = 'h';

		for(int i= 0; i<3; i++){
			while(placeShip(x,y,1)!=true){	
			x = generateRandomNumbers();
			y = generateRandomNumbers();
			
	
			}
		}
		
		if(GenOrient())
		orient = 'h';
		else
		orient = 'v';
		
		for(int i= 0; i<2; i++){
			while(placeShip(x,y,2,orient)!=true){	
			x = generateRandomNumbers();
			y = generateRandomNumbers();
			
	
			}
		}
		
		x = generateRandomNumbers();
		y = generateRandomNumbers();
		
		if(GenOrient())
		orient = 'h';
		else
		orient = 'v';
	
		while(placeShip(x,y,3,orient)!=true){	
			x = generateRandomNumbers();
			y = generateRandomNumbers();
			
	
		}
		
	cout << "Computer has placed it's ships" << endl << endl;
}

bool BattleShips :: randomHit()
{
	
	int x = generateRandomNumbers();
	int	y = generateRandomNumbers();
	cout<<"Computer -> target coordinates: "<<x<<" "<<y<<endl;
	return isHit(x, y);
	
	
}





bool BattleShips :: isHit(int x, int y) {

	// 0 -> initial, 1 -> submarine, 2 -> cruiser 3 battle ship 4 /, 5 -> hit, 6 -> miss
	if( grid_matrix[x][y]!=0 && grid_matrix[x][y]!=5 && grid_matrix[x][y]!=6 )
    {
 
        grid_matrix[x][y] = 5;//hit
        if(lives>0)
			lives--;
    
		return true;
        
    }
    else
	{
        if(grid_matrix[x][y]!=5)
                grid_matrix[x][y] = 6;//miss
        
		return false;
    }
	
}

bool BattleShips :: coordValid(int x, int y, char ori)
{
	
	if ((x <= GRID_MAX && y <= GRID_MAX) && (x >= GRID_MIN && y >= GRID_MIN) && (ori == 'h' || ori == 'v'))
		return true;
	else
		return false; //coordinates are not valid
}
void BattleShips :: restartGame()
{
	lives = SHIP_NUM;
}

//undo ship placement
void BattleShips :: undo(int _x, int _y, int shipType, char orientation)
{
	for(int i=0; i<shipType; i++)
	{
		grid_matrix[_x][_y] = 0;
		if(orientation == 'h')_y++;
		else if(orientation == 'v')_x--;
	}
}

int BattleShips ::getLives()
{
	return lives;
}