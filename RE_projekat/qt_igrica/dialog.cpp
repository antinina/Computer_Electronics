#include "dialog.h"
#include "ui_dialog.h"

//#include <QPushButton>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
	ui->attackBox->hide();
	
    lcd = lcdInit(2, 16, 4, 3, 14, 4, 12, 13, 6,4, 12, 13, 6 );
    lcdClear(lcd);
	
    time = new QTimer(this);
    buttons_p = new QPushButton*[100];
    buttons_c = new QPushButton*[100];
	
	//creating grid of buttons
    for(int i = 0; i<10; i++)
        for(int j = 0; j<10; j++)
        {
           buttons_p[(i*10 + j)] = new QPushButton(this);
           buttons_p[(i*10 + j)] -> setCheckable(true);
           buttons_p[(i*10 + j)] -> show();

           buttons_c[(i*10 + j)] = new QPushButton(this);
           buttons_c[(i*10 + j)] -> setCheckable(true);
           buttons_c[(i*10 + j)] -> setEnabled(true);
           buttons_c[(i*10 + j)] -> show();
           
           connect (buttons_p[(i*10 + j)], SIGNAL (clicked(bool)), this, SLOT (mark()) );
           
           ui -> layout1 -> addWidget(buttons_p[(i*10 + j)], i, j);
           ui -> layout2 -> addWidget(buttons_c[(i*10 + j)], i, j);
        }
    connect(time, SIGNAL(timeout()), this, SLOT(readKEY0()));
    time->start(350);
	
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog :: readKEY0()
{
    if(!digitalRead(21))
    {
    
        QMessageBox :: information(this,"Game Rules","Hello!\n First, you need to place your ships:\n Select the coordinates by clicking a cell in Player's grid,"
        "\n then choose the type of ship you want to place. Finally, click the PLACE button"
        "\n(or if you've made a mistake, delete ship by clicking UNDO button)"
        "\n! Your ships can occupy 20 cells in total."
        "\nWhen you place all of your ships -> click the START BATTLE!"
        "\nEnter the target coordinates and try to sink all of the opponent's ships"
        "\nGood luck!");
    
    }
        
}


//helper func , returns the position of clicked button(cell)
int Dialog :: buttonIsChecked(QPushButton **button_check)
{
    for(int i =0; i<10; i++)
        for(int j=0; j<10;j++)
        {
            if(button_check[i*10+j]->isChecked())
            {
                button_check[i*10+j]->setCheckable(false);
                button_check[i*10+j]->setEnabled(false);


               ui-> coordLabel1->setNum(i);
               ui-> coordLabel2->setNum(j);
                return (i*10+j);

            }
        }
    return 100; // none of buttons is pressed

}
void Dialog :: mark()
{
    int pos = 0;
    pos= buttonIsChecked(buttons_p);
	
    if(pos != 100)
	{
		this->position = pos;
		buttons_p[pos]->setCheckable(true);
		buttons_p[pos]->setEnabled(true);
   }

}


//Ship Placement 
void Dialog::on_placeButton_clicked()
{
    int canBePlaced = false;
    int row = position/10;
    int col = position%10;

    switch(ui->comboBox->currentIndex())
    {
        case 0://submarine
			if(player.placeShip(row, col) && shipNum>=1)
			{
				buttons_p[position]->setStyleSheet("background-color: navy");
				canBePlaced = true;
				shipNum--;
			}
        break;

        case 1://cruiser h
            if(player.placeShip(row, col,2) && shipNum>=2)
            {
                buttons_p[row*10+col]->setStyleSheet("background-color: navy");
                buttons_p[row*10+col+1]->setStyleSheet("background-color: navy");
                canBePlaced = true;
                shipNum-=2;
            }
        break;
        case 2://cruiser v
            if(player.placeShip(row, col,2,'v') && shipNum>=2)
            {
                buttons_p[row*10+col]->setStyleSheet("background-color: navy");
                buttons_p[(row+1)*10+col]->setStyleSheet("background-color: navy");
                canBePlaced = true;
                shipNum-=2;
            }
        break;
        case 3://battleship h
            if(player.placeShip(row, col,3) && shipNum>=3)
            {
                buttons_p[row*10+col]->setStyleSheet("background-color: navy");
                buttons_p[row*10+col+1]->setStyleSheet("background-color: navy");
                buttons_p[row*10+col+2]->setStyleSheet("background-color: navy");
                canBePlaced = true;
                shipNum-=3;
            }
        break;
        case 4://battleship v
            if(player.placeShip(row, col,3,'v') && shipNum>=3)
            {
                buttons_p[row*10+col]->setStyleSheet("background-color: navy");
                buttons_p[(row+1)*10+col]->setStyleSheet("background-color: navy");
                buttons_p[(row+2)*10+col]->setStyleSheet("background-color: navy");
                canBePlaced = true;
                shipNum-=3;
            }
        break;
        case 5://carrier h
            if(player.placeShip(row, col,4) && shipNum>=4)
            {
                buttons_p[row*10+col]->setStyleSheet("background-color: navy");
                buttons_p[row*10+col+1]->setStyleSheet("background-color: navy");
                buttons_p[row*10+col+2]->setStyleSheet("background-color: navy");
                buttons_p[row*10+col+3]->setStyleSheet("background-color: navy");
                canBePlaced = true;
                shipNum-=4;
            }
        break;
        case 6://carrier v
            if(player.placeShip(row, col,4, 'v') && shipNum>=4)
            {
                buttons_p[row*10+col]->setStyleSheet("background-color: navy");
                buttons_p[(row+1)*10+col]->setStyleSheet("background-color: navy");
                buttons_p[(row+2)*10+col]->setStyleSheet("background-color: navy");
                buttons_p[(row+3)*10+col]->setStyleSheet("background-color: navy");
                canBePlaced = true;
                shipNum-=4;
            }
        break;
        default:
            qDebug()<<"Invalid action!";
        break;
        }
    
    ui->occupLabel->setNum(20-shipNum);
	if(!canBePlaced)//ovo je ok
		QMessageBox :: warning(this, "Warning", "Ship can not be placed! Please check the number of occupied cells \n or try choosing different coordinates. ");

}

void Dialog::on_undoButton_clicked()
{
    int row = position/10;
    int col = position%10;

        switch(ui->comboBox->currentIndex())
        {
        case 0://submarine

            player.undo(row, col);
            buttons_p[position]->setStyleSheet("background-color: none");
            shipNum++;

        break;

        case 1://cruiser h
                player.undo(row, col,2);
                buttons_p[position]->setStyleSheet("background-color: none");
                buttons_p[position+1]->setStyleSheet("background-color: none");

                shipNum+=2;

        break;
        case 2://cruiser v
                player.undo(row, col,2, 'h');
                buttons_p[row*10+col]->setStyleSheet("background-color: none");
                buttons_p[(row+1)*10+col]->setStyleSheet("background-color: none");

                shipNum+=2;

        break;
        case 3://battleship h
                player.undo(row, col,3);
                buttons_p[position]->setStyleSheet("background-color: none");
                buttons_p[position+1]->setStyleSheet("background-color: none");
                buttons_p[position+2]->setStyleSheet("background-color: none");

                shipNum+=3;

        break;
        case 4://battleship v
                player.undo(row, col,3, 'v');
                buttons_p[row*10+col]->setStyleSheet("background-color: none");
                buttons_p[(row+1)*10+col]->setStyleSheet("background-color: none");
                buttons_p[(row+2)*10+col]->setStyleSheet("background-color: none");

                shipNum+=3;

        break;
        case 5://carrier h
            player.undo(row, col,4);
                buttons_p[position]->setStyleSheet("background-color: none");
                buttons_p[position+1]->setStyleSheet("background-color: none");
                buttons_p[position+2]->setStyleSheet("background-color: none");
                buttons_p[position+3]->setStyleSheet("background-color: none");

                shipNum+=4;

        break;
        case 6://carrier v
                player.undo(row, col,4, 'v');
                buttons_p[row*10+col]->setStyleSheet("background-color: none");
                buttons_p[(row+1)*10+col]->setStyleSheet("background-color: none");
                buttons_p[(row+2)*10+col]->setStyleSheet("background-color: none");
                buttons_p[(row+3)*10+col]->setStyleSheet("background-color: none");

                shipNum+=4;

        break;

        default:
            qDebug()<<"UNDO:Invalid action!";
        break;
        }

    ui->occupLabel->setNum(20-shipNum);

}

void Dialog::on_startButton_clicked()
{
    if(shipNum == 0)
	{
        started = true;
        ui->placeBox->hide();
        ui->attackBox->show();
        
        QMessageBox :: information(this,"Info","The enemy is placing his ships...");
        computer.randomGenShips();
        QMessageBox :: information(this,"Info","Let the games begin... :)");
		ui-> startButton ->setEnabled(false);
		
    }
	else
		QMessageBox :: warning(this,"Warning","You haven't placed your ships yet!");
}


void Dialog::on_attackButton_clicked()
{
    int x , y, xr, yr;

    if(started){
		x = (ui->spinRow->value());
		y = (ui->spinCol->value());
     
	 
        if(computer.isHit(x,y))
		{
            buttons_c[x*10+y]->setStyleSheet("background-color: red");//hit

        }
        else
        {
            if(computer.getCellValue(x,y)!= 5) 
				buttons_c[x*10+y]->setStyleSheet("background-color: black"); //miss, enemy's turn
             
            xr=(computer.BattleShips :: generateRandomNumbers());
            yr=(computer.BattleShips :: generateRandomNumbers());
            qDebug()<<"Target coordinates "<<xr<<" "<<yr;
            while(player.isHit(xr,yr))
            {            

                buttons_p[xr*10+yr]->setStyleSheet("background-color: red"); //hit

                xr=(computer.BattleShips :: generateRandomNumbers());
                yr=(computer.BattleShips :: generateRandomNumbers());
                qDebug()<<"Target coordinates "<<xr<<" "<<yr;
             }
             
             qDebug()<<"Coords out of the loop "<<xr<<" "<<yr;
              if(player.getCellValue(xr,yr)!= 5) //was not hit before
                buttons_p[xr*10+yr]->setStyleSheet("background-color: black");//out of the loop -> miss

        }
		// LCD: Player -> num of lives; opponent -> num of lives
		lcdClear(lcd);
		lcdPosition(lcd, 0 ,0);
		lcdPrintf(lcd, "Player %d", player.getLives());
		lcdPosition(lcd, 0 ,1);
		lcdPrintf(lcd, "Computer %d", computer.getLives());

		 
		if(computer.getLives()==0 || player.getLives()==0)
		{			
			bool you_win = false;
			if(computer.getLives()==0)
				you_win = true;
			QMessageBox :: StandardButton ret;
			QMessageBox :: information(this,"Info",you_win?"Congrats!You're the winner!":"You've lost! :(");

			ret = QMessageBox :: question(this,"End of the game","Do you want to start a new one?",QMessageBox :: Yes|QMessageBox :: No);

			if(ret == QMessageBox :: Yes)
			{
				started = false;
				shipNum = 20;             
				player.restartGame();
				computer.restartGame();
				
				ui->attackBox->hide();
				ui->placeBox->show();
				ui-> startButton ->setEnabled(true);
				
				lcdClear(lcd);
				this -> defaultColor(buttons_p, buttons_c);
			}
			 
			else if(ret == QMessageBox :: No)
			{        
				lcdClear(lcd);
				ui->attackBox->hide();
				ui->placeBox->hide();				
				ui->startButton->hide();
				
			}
		}
    }
}

void  Dialog :: defaultColor(QPushButton **cell1, QPushButton **cell2)
{
    for(int i =0; i<10; i++)
        for(int j = 0; j<10; j++)
        {
            cell1[i*10+j]->setStyleSheet("background-color: none");
            cell2[i*10+j]->setStyleSheet("background-color: none");
        }
}



