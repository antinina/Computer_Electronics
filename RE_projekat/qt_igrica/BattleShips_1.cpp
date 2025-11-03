#include "BattleShips.h"
#include "stdlib.h"
#include "time.h"
#include <QDebug>

//Legend: 0 -> initial, 1 -> submarine, 2 -> cruiser, 3 -> battle ship, 4 -> carrier , 5 -> hit, 6 -> miss

BattleShips::BattleShips()
{
    for(int i = 0; i<=GRID_MAX;i++)
            for(int j = 0; j<=GRID_MAX;j++)
                grid_matrix[i][j] = 0;    
}

//helper functions
int min(int a, int b)
{
    if(a<b)return a;
    else return b;
}
int max(int a, int b)
{
    if(a<b)return b;
    else return a;
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


int BattleShips :: generateRandomNumbers() {
    
	return rand() % (GRID_MAX+1); // number from 0 to GRID_MAX + 1 - 1 (0->9)

}

//random number, 0 or 1
int GenOrient()
{
    srand(time(NULL));
    return  rand()%2;
    return 0;
}

bool BattleShips :: randomGenShips()
{      
    int x = generateRandomNumbers();
    int y = generateRandomNumbers();
    char orient = 'h';

    if(GenOrient())
        orient = 'h';
    else
        orient = 'v';
    
    x = generateRandomNumbers();
    y = generateRandomNumbers();            
    
    //qDebug()<<"carrier "<<" "<<x<<" "<<y;

    for(int i= 0; i<2; i++)
	{
        while(placeShip(x,y,3,orient)!=true)
		{
            x = generateRandomNumbers();
            y = generateRandomNumbers();
            if(GenOrient())
				orient = 'h';
            else
				orient = 'v';
        }
        //qDebug()<<"battle num:"<<i<<" "<<x<<" "<<y;
    }
    
	for(int i= 0; i<3; i++)
	{
        while(placeShip(x,y,2,orient)!=true)
		{
            x = generateRandomNumbers();
            y = generateRandomNumbers();
            if(GenOrient())
				orient = 'h';
            else
				orient = 'v';
        }
        //qDebug()<<"cruiser num:"<<i<<" "<<x<<" "<<y;
    }
    
    for(int i= 0; i<4; i++)
	{
        while(placeShip(x,y,1)==false)
		{            
            x = generateRandomNumbers();
            y = generateRandomNumbers();
        
        }
        //qDebug()<<"submarine num "<<i<<" "<<x<<" "<<y;
    }

    qDebug()<<"Computer has placed his ships!";
    return true;
}

bool BattleShips :: isHit(int x, int y)
{
 //Legend: 0 -> initial, 1 -> submarine, 2 -> cruiser, 3 -> battle ship, 4 -> carrier , 5 -> hit, 6 -> miss
 
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

void BattleShips :: restartGame()
{
    lives = SHIP_NUM;
    for(int i = 0; i<=GRID_MAX; i++)
        for(int j=0;j<=GRID_MAX;j++)
			grid_matrix[i][j] = 0;
}

//undo ship placement
void BattleShips :: undo(int _x, int _y, int shipType, char orientation)
{
    for(int i=0; i<shipType; i++)
    {   
        grid_matrix[_x][_y] = 0;               
        if(orientation == 'h')
			_y++;
        else if(orientation == 'v')
			_x++;
    }
}

int BattleShips :: getLives()
{
    return lives;
}

int BattleShips :: getCellValue(int x, int y)
{
    return grid_matrix[x][y];
}
