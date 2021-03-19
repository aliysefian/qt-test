#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <dbmanager.h>
#include <QDebug>
#include<QCryptographicHash>
#include<QMessageBox>
#include<mainwindow.h>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
     QMap<QString,QString> getCurrentUser();

private slots:
    void on_btnLogin_clicked();


private:
    Ui::Login *ui;
    QMap<QString,QString> _currenUser ;
    bool updateLastLoginOfUser(QString userId) ;
};

#endif // LOGIN_H
