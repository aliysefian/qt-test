#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include <QSqlQuery>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setCurrentUser(const QMap<QString,QString> currentUserInfo);

    private slots:
        void on_btn_load_user_data_clicked();

        void on_tbl_user_doubleClicked(const QModelIndex &index);

        void on_btn_create_user_clicked();

        void on_btnNext_clicked();

        void on_btnPrevPage_clicked();


        void on_txtSearch_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    int _current_page=0;
    int _pagination_per_page=10;
    QVariant _totalUserInDb;
    QMap<QString, QString> _currentUserInfo;

};

#endif // MAINWINDOW_H
