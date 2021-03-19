#include "createuser.h"
#include "ui_createuser.h"
#include <QString>
#include <QDebug>
#include <QCryptographicHash>
#include <dbmanager.h>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMap>

CreateUser::CreateUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateUser)
{
    ui->setupUi(this);
    load_combo_relation_role_id();


    connect(ui->txt_username,&QLineEdit::textChanged,this,&CreateUser::checkInput);

    connect(ui->txt_password,&QLineEdit::textChanged,this,&CreateUser::checkInput);

    if(_createMode){
        ui->lbl_password_old->setVisible(false);
        ui->txt_password_old->setVisible(false);
    }
    //regex validators

    QRegularExpression rx("\\b^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#\$%\^&\*])(?=.{8,})\\b",QRegularExpression::CaseInsensitiveOption);
    ui->txt_password->setValidator(new QRegularExpressionValidator(rx,this));

}

void CreateUser::getDataBetweenForms(QString id)
{
    qDebug()<<"dddd"<<id;
    _idUser=id;
    _createMode=false;
    QString path="";
    DbManager db(path);

    ui->lbl_password_old->setVisible(true);
    ui->txt_password_old->setVisible(true);
    ui->btn_create_user->setText("Update");

    if(db.isOpen()){
       QMap<QString, QString> values=db.getUser(id);
       ui->txt_username->setText(values["username"]);
       ui->txt_permision->setText(values["permission"]);
       ui->cmbRoles->setCurrentIndex(values["role_id"].toInt());
       ui->date_exp->setDate(QDate::fromString(values["password_expire_date"],"yyyy-MM-dd"));
       ui->txtDescription->setText(values["description"]);
       _password=values["password"];
    }
    else
    {
        qDebug() << "Database is not open!";
    }




}

CreateUser::~CreateUser()
{
    delete ui;
}

void CreateUser::on_btn_create_user_clicked()
{
    if(_createMode)
        createUser();
    else
        updateUser();


}

void CreateUser::load_combo_relation_role_id()
{
    QString path="";
    QSqlQuery query;
    DbManager db(path);
   if(db.isOpen()){
//        db.createTable();
//        db.addPerson("ali");
//        db.addPerson("reza");
       query=db.getAllRoles();
       qDebug() << "End";
   }
   else
   {
       qDebug() << "Database is not open!";
   }
   QSqlQueryModel* modal=new QSqlQueryModel();
   modal->setQuery(query);
   ui->cmbRoles->setModel(modal);
   ui->cmbRoles->setModelColumn(1); // for id being as id and secound col for label usr


//    for(int i=1;i<11;i++){
//        ui->cmbRoles->addItem();
//    }
}

void CreateUser::on_cmbRoles_currentIndexChanged(int index)
{
    qDebug() << ui->cmbRoles->model();

}

void CreateUser::createUser()
{
    QString username=ui->txt_username->text();
    QString password=ui->txt_password->text();
    QString passwordConfirm=ui->txt_password_confirm->text();
    int cmb=ui->cmbRoles->currentIndex();
    QString date=ui->date_exp->text();
    QString description=ui->txtDescription->toPlainText();
    QString md5Pass = QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex());

    QString path="";
    bool query;
    DbManager db(path);
   if(db.isOpen()){
       query=db.addUser(username,md5Pass,(cmb+1),date,description);
       qDebug() << username << md5Pass << cmb << "End";
   }
   else
   {
       qDebug() << "Database is not open!";
   }
    qDebug() << "aa" << date << username << md5Pass<< cmb+1;

}

void CreateUser::updateUser()
{

    QString username=ui->txt_username->text();
    QString password=ui->txt_password->text();
    QString passwordConfirm=ui->txt_password_confirm->text();
    QString passwordOld=ui->txt_password_old->text();
    QString permision=ui->txt_permision->text();


    int cmb=ui->cmbRoles->currentIndex();
    QString date=ui->date_exp->text();
    QString description=ui->txtDescription->toPlainText();
    QString md5PassOld = QString(QCryptographicHash::hash((passwordOld.toUtf8()),QCryptographicHash::Md5).toHex());
    QString md5NewPassword = QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex());

    if(passwordOld.length()>0){
        if(md5PassOld==_password){
            qDebug()<< "equallll";

            QString path="";
            bool query;
            DbManager db(path);
           if(db.isOpen()){
               query=db.updateUser(_idUser,username,permision,md5NewPassword,(cmb+1),date,description,true);
               qDebug() << username << md5NewPassword << cmb << "End";
           }
           else
           {
               qDebug() << "Database is not open!";
           }
            qDebug() << "update iwth password." << date << username << md5NewPassword<< cmb+1;
            return;
        }
        else{
//            QMessageBox msgBox;
//            msgBox.setText("Your old password does not match.");
//            msgBox.exec();
            QMessageBox::critical(this, tr("Update User "),
                                          tr("Your old password does not match."
                                             ),
                                          QMessageBox::Discard
                                          );
            return;
        }
    }
    qDebug()<< "change without passowd";

    QString path="";
    bool query;
    DbManager db(path);
   if(db.isOpen()){
       query=db.updateUser(_idUser,username,permision,md5NewPassword,(cmb+1),date,description,false);
       qDebug() << username << md5NewPassword << cmb << "End";
   }
   else
   {
       qDebug() << "Database is not open!";
   }
    qDebug() << "update not password." << date << username << md5NewPassword<< cmb+1;

}



void CreateUser::on_btnClose_clicked()
{
    reject();
}

void CreateUser::checkInput()
{
    QLineEdit *txt_username=ui->txt_username;

    if(txt_username->text().length()<2)
    {
        txt_username->setStyleSheet("QLineEdit {color:red;}");
    }
    else{
        txt_username->setStyleSheet("QLineEdit {color:black;}");
    }


    if(ui->txt_password->hasAcceptableInput()){
        txt_username->setStyleSheet("QLineEdit {color:black;}");

    }
    else{
        txt_username->setStyleSheet("QLineEdit {color:red;}");
    }
    qDebug()<<"ssss"<<ui->txt_password->hasAcceptableInput();


}
