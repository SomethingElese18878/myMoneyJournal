#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "account.h"
//#include "booking.h"

#include <QMainWindow>
#include <QModelIndex>
#include <QStringList>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Account *allAccount;
    
private slots:
    void add2List();
    void on_le_accountName_returnPressed();

    void on_lineEditDescription_returnPressed();
    void on_lineEditPrice_returnPressed();



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
