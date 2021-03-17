#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <testmodel.h>
#include <QSqlQuery>
#include <dbmanager.h>
#include <QSqlQueryModel>
#include <QDebug>
#include <createuser.h>

static const QString path = "/home/ali/QT/QTDatatableView/project.db";



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlQuery query;
    DbManager db(path);
    _current_page++;
   if(db.isOpen()){
       query=db.getUserTable(1,_current_page);
       _totalUserInDb=db.countUser();
       ui->lblCountOfUser->setText(QString("Total User is : %1").arg(_totalUserInDb.toString()));
       qDebug() << "Endss"<<_totalUserInDb;
   }
   else
   {
       qDebug() << "Database is not open!";
   }
   QSqlQueryModel* modal=new QSqlQueryModel();


   modal->setQuery(query);
   ui->tbl_user->setModel(modal);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btn_load_user_data_clicked()
{
     QSqlQuery query;
     DbManager db(path);
    if(db.isOpen()){
//        db.createTable();
//        db.addPerson("ali");
//        db.addPerson("reza");
//        query=db.getUserTable();
        qDebug() << "End";
    }
    else
    {
        qDebug() << "Database is not open!";
    }
    QSqlQueryModel* modal=new QSqlQueryModel();


    modal->setQuery(query);
    ui->tbl_user->setModel(modal);



}

void MainWindow::on_tbl_user_doubleClicked(const QModelIndex &index)
{

    QModelIndexList indexList = ui->tbl_user->selectionModel()->selectedIndexes();
    int row;
    foreach (QModelIndex index, indexList) {
        row = index.row();

        qDebug() << "ali" <<row<<ui->tbl_user->model()->index(row,0).data().toString();

        CreateUser userFrom;
        userFrom.setModal(true);
        userFrom.getDataBetweenForms
                (ui->tbl_user->model()->index(row,0).data().toString());
        userFrom.exec();
    }


}

void MainWindow::on_btn_create_user_clicked()
{
    CreateUser userFrom;
    userFrom.setModal(true);
//    userFrom.getDataBetweenForms();
    userFrom.exec();
}

void MainWindow::on_btnNext_clicked()
{
    QSqlQuery query;
    DbManager db(path);
    _current_page++;
    qDebug() << _current_page<< _pagination_per_page;
    if(((_current_page)*_pagination_per_page)>=_totalUserInDb.toInt())
        ui->btnNext->setEnabled(false);
    else
        ui->btnNext->setEnabled(true);


   if(db.isOpen()){


       query=db.getUserTable(1,_current_page);


       //get total count of User
       ui->lblCountOfUser->setText(QString("Total User is : %1").arg(db.countUser().toString()));
       qDebug() << "Endss"<<db.countUser();
   }
   else
   {
       qDebug() << "Database is not open!";
   }
   QSqlQueryModel* modal=new QSqlQueryModel();


   modal->setQuery(query);
   ui->tbl_user->setModel(modal);
}

void MainWindow::on_btnPrevPage_clicked()
{
    QSqlQuery query;
    DbManager db(path);
    if(!ui->btnNext->isEnabled())
        ui->btnNext->setEnabled(true);

    _current_page--;
    if(_current_page<=0){
        _current_page=1;
        return ;
    }
   if(db.isOpen()){
       query=db.getUserTable(1,_current_page);


       //get total count of User
       ui->lblCountOfUser->setText(QString("Total User is : %1").arg(db.countUser().toString()));
       qDebug() << "Endss"<<db.countUser();
   }
   else
   {
       qDebug() << "Database is not open!";
   }
   QSqlQueryModel* modal=new QSqlQueryModel();


   modal->setQuery(query);
   ui->tbl_user->setModel(modal);
}
