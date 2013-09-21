#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //addBar
    ui->lineEditDescription->setFocus();

    //set dateEdit to currentDate
    ui->dateEdit->setDate(QDate::currentDate());

    //setColumn, it's width and how they named
    ui->tableWidgetBooking->setColumnCount(4);
    ui->tableWidgetBooking->setColumnWidth(0, 250); //Description
    ui->tableWidgetBooking->setColumnWidth(1, 100); //Price
    ui->tableWidgetBooking->setColumnWidth(2, 100); //Date
    ui->tableWidgetBooking->setColumnWidth(2, 100); //Total
    QStringList columnText;
    columnText << "Description" << "Price" << "Date" << "Total";
    ui->tableWidgetBooking->setHorizontalHeaderLabels(columnText);

    //sidebar
    ui->rbtn_allAccounts->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addList_clicked()
{
    //Get a new row
    int insertRow = ui->tableWidgetBooking->rowCount();
    ui->tableWidgetBooking->insertRow(insertRow);

    //insert description, price and date into the table
    ui->tableWidgetBooking->setItem(insertRow, 0, new QTableWidgetItem(ui->lineEditDescription->text()));
    ui->tableWidgetBooking->setItem(insertRow, 1, new QTableWidgetItem(ui->lineEditPrice->text()));
    ui->tableWidgetBooking->setItem(insertRow, 2,  new QTableWidgetItem(ui->dateEdit->date().toString()));
}


void MainWindow::on_le_accountName_returnPressed()
{
    QString new_account_name = ui->le_accountName->text();

    QRadioButton *newUser = new QRadioButton(this);
    newUser->setText(new_account_name);
    newUser->show();
    newUser->setChecked(true);
}

void MainWindow::on_lineEditDescription_returnPressed()
{
    this->on_addList_clicked();
}

void MainWindow::on_lineEditPrice_returnPressed()
{
    this->on_addList_clicked();
}
