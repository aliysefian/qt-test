#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

}

Login::~Login()
{
    delete ui;
}

void Login::on_btnLogin_clicked()
{
    QString username=ui->txtUsername->text();
    QString password=ui->txtPassword->text();
    QString md5Pass = QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex());

    DbManager db("");
   if(db.isOpen()){
       bool exist=false;

       QMap<QString,QString> userData=db.UserExistWitdata(username,md5Pass,&exist);

       if(exist){
           _currenUser=userData;
           qDebug()<<"exist";
           MainWindow w;
           w.show();
           this->accept();

       }else
       {
           qDebug()<<"not exist";
           QMessageBox::critical(this, tr("Wrong Password! "),
                                         tr("username or password is wrong"
                                            ),
                                         QMessageBox::Cancel
                                         );
       }

   }
   else
   {
       qDebug() << "Database is not open!";
   }


}

QMap<QString, QString> Login::getCurrentUser()
{
    return _currenUser;
}
