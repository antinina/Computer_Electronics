#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    if(wiringPiSetup()<0){
            qCritical("WiringPi:ERROR!");
            return 1;
            }
    //KEY0
    pinMode(21, INPUT);


    QApplication a(argc, argv);   
    Dialog w;

    w.show();
    return a.exec();
}
