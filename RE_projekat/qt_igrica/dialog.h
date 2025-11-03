#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include "BattleShips.h"
#include "wiringPi.h"
#include "lcd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);

    QTimer *time;
    QPushButton **buttons_p;
    QPushButton **buttons_c;
    BattleShips player;
    BattleShips computer;

    int lcd;

    int position = 0;
    int shipNum = 20;//
    bool started = false;
 
    //funcs
    int buttonIsChecked(QPushButton **button_check);
    void defaultColor(QPushButton **cell1, QPushButton **cell2);
    ~Dialog();
	
public slots:
	
	//checks if the first button on RPi HAT is pressed
    void readKEY0();
	//event of marking cell in player's grid
    void mark();

private slots:
//buttons
    void on_placeButton_clicked();

    void on_undoButton_clicked();

    void on_startButton_clicked();

    void on_attackButton_clicked();

private:

    Ui::Dialog *ui;
};
#endif // DIALOG_H
