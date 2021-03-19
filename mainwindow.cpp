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
//    setCentralWidget(ui->tableView);
    QSqlQuery query;
    DbManager db(path);
    _current_page++;
   if(db.isOpen()){
       query=db.getUserTable(_pagination_per_page,_current_page,"");
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



void MainWindow::setCurrentUser(const QMap<QString, QString> currentUserInfo)
{
    _currentUserInfo=currentUserInfo;
    ui->lblCurrentUser->setText(QString("Welcome User: %1 ").arg(_currentUserInfo["username"]));
}

void MainWindow::on_btn_load_user_data_clicked()
{
    QSqlQuery query;
    DbManager db(path);
    _current_page++;
   if(db.isOpen()){
       query=db.getUserTable(_pagination_per_page,_current_page,"");
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
   ui->tbl_user->viewport()->update();

}

void MainWindow::on_tbl_user_doubleClicked(const QModelIndex &index)
{

    QModelIndexList indexList = ui->tbl_user->selectionModel()->selectedIndexes();
    int row;
    foreach (QModelIndex index, indexList) {
        row = index.row();
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
    if(((_current_page)*_pagination_per_page)>=_totalUserInDb.toInt())
        ui->btnNext->setEnabled(false);
    else
        ui->btnNext->setEnabled(true);


   if(db.isOpen()){
       QString search=ui->txtSearch->text();
       query=db.getUserTable(_pagination_per_page,_current_page,search);
       ui->lblCountOfUser->setText(QString("Total User is : %1").arg(db.countUser().toString()));
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
        QString search=ui->txtSearch->text();
       query=db.getUserTable(_pagination_per_page,_current_page,search);
       //get total count of User
       ui->lblCountOfUser->setText(QString("Total User is : %1").arg(db.countUser().toString())); 
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

void MainWindow::on_txtSearch_textChanged(const QString &arg1)
{
    QSqlQuery query;
    DbManager db(path);
    _current_page++;
   if(db.isOpen()){
       query=db.getUserTable(_pagination_per_page,_current_page,arg1);
//       _totalUserInDb=db.countUser();
//       ui->lblCountOfUser->setText(QString("Total User is : %1").arg(_totalUserInDb.toString()));
//       qDebug() << "Endss"<<_totalUserInDb;
   }
   else
   {
       qDebug() << "Database is not open!";
   }
   QSqlQueryModel* modal=new QSqlQueryModel();
   modal->setQuery(query);

   ui->tbl_user->setModel(modal);
   ui->tbl_user->viewport()->update();



}
