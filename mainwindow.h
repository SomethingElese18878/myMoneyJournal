#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Account.h"
#include "Booking.h"

#include <QMainWindow>
#include <QModelIndex>
#include <QStringList>
#include <QButtonGroup>


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
    void add2List();
    void on_lineEdit_accountName_returnPressed();
    void on_lineEditDescription_returnPressed();
    void on_lineEditPrice_returnPressed();

    void on_btnSave_clicked();

private:
    Ui::MainWindow *ui;
    QButtonGroup *btnGroup_user;

    Account *allAccounts;
    std::list<Account> listAccounts;

    Booking *newBooking;
};

#endif // MAINWINDOW_H
