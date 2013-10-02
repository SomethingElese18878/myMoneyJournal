#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Database.h"

#include <QMainWindow>
#include <QModelIndex>
#include <QStringList>
#include <QButtonGroup>

#include <QtSql>


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
    QSqlError add2List();
    void on_lineEdit_accountName_returnPressed();
    void on_lineEditDescription_returnPressed();
    void on_lineEditPrice_returnPressed();

private:
    Ui::MainWindow *ui;
    QButtonGroup *btnGroup_user;
    Database *database;

    QSqlRelationalTableModel *model;
    int priceIdx, descriptionIdx;
};

#endif // MAINWINDOW_H
