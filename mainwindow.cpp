#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidgetBooking->setColumnCount(3);
    ui->tableWidgetBooking->setColumnWidth(0, 250);
    ui->tableWidgetBooking->setColumnWidth(1, 200);
    ui->tableWidgetBooking->setColumnWidth(2, 100);

    QStringList columnText;
    columnText << "Description" << "Price" << "Date";

    ui->tableWidgetBooking->setHorizontalHeaderLabels(columnText);
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
//    ui->tableWidgetBooking->setItem(insertRow, 1, new QTableWidgetItem(ui->dateEdit->date()));    //FIXME: How to handle date? Convert to string?
}

