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
    QMap<QString,QString> currentUserInfo;
    if(cs.exec()==QDialog::Accepted){
        qDebug()<<"welcome Ali";
        currentUserInfo=cs.getCurrentUser();
        w.setCurrentUser(currentUserInfo);
        w.show();
    }




    return a.exec();
}
