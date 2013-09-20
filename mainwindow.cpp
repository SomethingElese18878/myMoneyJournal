#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set dateEdit to currentDate
    ui->dateEdit->setDate(QDate::currentDate());

    //setColumn, it's width and how they named
    ui->tableWidgetBooking->setColumnCount(4);
    ui->tableWidgetBooking->setColumnWidth(0, 250);
    ui->tableWidgetBooking->setColumnWidth(1, 200);
    ui->tableWidgetBooking->setColumnWidth(2, 100);
    ui->tableWidgetBooking->setColumnWidth(2, 100);
    QStringList columnText;
    columnText << "Description" << "Price" << "Date" << "Total";
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
    ui->tableWidgetBooking->setItem(insertRow, 2,  new QTableWidgetItem(ui->dateEdit->date().toString()));
}

