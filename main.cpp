#include "mainwindow.h"
#include <QApplication>
#include <dbmanager.h>
#include <QDebug>
#include <login.h>
#include <QDir>
#include <QString>
#include <QStandardPaths>
#include <QDirIterator>
#include <QFileInfo>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    Login cs;
    MainWindow w;
    QMap<QString,QString> currentUserInfo;
    if(cs.exec()==QDialog::Accepted){
        currentUserInfo=cs.getCurrentUser();
        w.setCurrentUser(currentUserInfo);
        w.show();
    }
//    w.show();
    return a.exec();
}
