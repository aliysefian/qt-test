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
    QList<QString> contactNames;
    QList<QString> contactPhoneNums;

    // Create some data that is tabular in nature:
    contactNames.append("Thomas");
    contactNames.append("Richard");
    contactNames.append("Harrison");
    contactPhoneNums.append("123-456-7890");
    contactPhoneNums.append("222-333-4444");
    contactPhoneNums.append("333-444-5555");

    // Create model:
    TestModel* PhoneBookModel = new TestModel(this);

    // Populate model with data:
    PhoneBookModel->populateData(contactNames,contactPhoneNums);

    // Connect model to table view:
    ui->tableView->setModel(PhoneBookModel);

    // Make table header visible and display table:
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->show();

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
        query=db.getUserTable();
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
