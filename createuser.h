#ifndef CREATEUSER_H
#define CREATEUSER_H

#include <QDialog>

namespace Ui {
class CreateUser;
}

class CreateUser : public QDialog
{
    Q_OBJECT

public:
    explicit CreateUser(QWidget *parent = 0);
    void getDataBetweenForms(QString id);
    ~CreateUser();

private slots:
    void on_btn_create_user_clicked();
    void load_combo_relation_role_id();
    void on_cmbRoles_currentIndexChanged(int index);


private:
    Ui::CreateUser *ui;
    bool _createMode=true;
    QString _password="";
    void createUser();
    void updateUser();
};

#endif // CREATEUSER_H
