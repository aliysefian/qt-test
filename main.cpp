#include "mainwindow.h"
#include <QApplication>
#include <dbmanager.h>
#include <QDebug>
#include <login.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login cs;
    MainWindow w;
    if(cs.exec()==QDialog::Accepted){
        qDebug()<<"welcome Ali";
        w.show();
    }




    return a.exec();
}
