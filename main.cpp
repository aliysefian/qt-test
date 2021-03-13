#include "mainwindow.h"
#include <QApplication>
#include <dbmanager.h>
#include <QDebug>
static const QString path = "/home/ali/QT/QTDatatableView/project.db";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    DbManager db(path);
    if(db.isOpen()){
//        db.createTable();
//        db.addPerson("ali");
//        db.addPerson("reza");
        db.printAllPersons();
        qDebug() << "End";
    }
    else
    {
        qDebug() << "Database is not open!";
    }



    w.show();

    return a.exec();
}
