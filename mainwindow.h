#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include <QSqlQuery>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    private slots:
        void on_btn_load_user_data_clicked();

        void on_tbl_user_doubleClicked(const QModelIndex &index);

        void on_btn_create_user_clicked();

        void on_btnNext_clicked();

        void on_btnPrevPage_clicked();

private:
    Ui::MainWindow *ui;
    int _current_page=0;
    int _pagination_per_page=3;
    QVariant _totalUserInDb;
};

#endif // MAINWINDOW_H
