#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "initdb.h"
#include <iostream>
#include <QDataWidgetMapper>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //addBar
    ui->lineEditDescription->setFocus();

    //set dateEdit to currentDate
    ui->dateEdit->setDate(QDate::currentDate());

    //sidebar
    ui->rbtn_allAccounts->setChecked(true);

    this->btnGroup_user = new QButtonGroup();
    this->btnGroup_user->addButton(ui->rbtn_allAccounts);

    //own logic
    this->allAccounts = new Account("allAccounts");


    //Implement database-model
    // initialize the database, filename: unused
    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
//        showError(err);
        return;
    }

    // Create the data model
    model = new QSqlRelationalTableModel(ui->tableBooking);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("booking");

    model->setHeaderData(model->fieldIndex("description"), Qt::Horizontal, tr("Description"));
    model->setHeaderData(model->fieldIndex("price"), Qt::Horizontal, tr("Price"));

    // Populate the model
    if (!model->select()) {
//        showError(model->lastError());
        return;
    }

    ui->tableBooking->setModel(model);
//    ui->tableBooking->setItemDelegate(new Book);
    ui->tableBooking->setColumnHidden(model->fieldIndex("id"), true);
    ui->tableBooking->setSelectionMode(QAbstractItemView::SingleSelection);

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(ui->lineEditDescription, model->fieldIndex("description"));
    mapper->addMapping(ui->lineEditPrice, model->fieldIndex("price"));

    //Values of marked entry are shown in lineEdit_description && lineEdit_price
//    connect(ui->tableBooking->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
//            mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    ui->tableBooking->setCurrentIndex(model->index(0, 0));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::add2List()
{
    /*
    * add new Booking to booking-journal
    */
//    //create newBooking object
//    Booking newBooking = Booking(ui->lineEditPrice->text().toFloat(), ui->lineEditDescription->text().toStdString());
////    this->allAccounts->setBooking(newBooking);
//    //Get a new row
//    int insertRow = ui->tableWidgetBooking->rowCount();
//    ui->tableWidgetBooking->insertRow(insertRow);

//    //insert description, price and date into the table
//    ui->tableWidgetBooking->setItem(insertRow, 0, new QTableWidgetItem(ui->lineEditDescription->text()));
//    ui->tableWidgetBooking->setItem(insertRow, 1, new QTableWidgetItem(ui->lineEditPrice->text()));
//    ui->tableWidgetBooking->setItem(insertRow, 2,  new QTableWidgetItem(ui->dateEdit->date().toString()));

//    //Total calculation
//    QString *qstr_allAccount = new QString(ui->lineEditPrice->text());
//    this->allAccounts->setMoney(qstr_allAccount->toFloat());
//    QString qstr_totalTable = QString("%1").arg(this->allAccounts->getMoney()); //convert: float ==> qstring
//    ui->tableWidgetBooking->setItem(insertRow, 3, new QTableWidgetItem( qstr_totalTable ));
}


void MainWindow::on_lineEdit_accountName_returnPressed()
{
    /*
    * LINE EDIT for add accounts
    */
    //Add newUser-radiobutton
    QString new_account_name = ui->lineEdit_accountName->text();

    Account newAccount(new_account_name.toStdString()); //Account *newAccount = new Account(new_account_name.toStdString()); FIXME?
    listAccounts.push_back(newAccount);

    QRadioButton *newRadioButtonAcc = new QRadioButton(this);
    btnGroup_user->addButton(newRadioButtonAcc);
    newRadioButtonAcc->setText(new_account_name);
    newRadioButtonAcc->setChecked(true);
    newRadioButtonAcc->show();
    int userRow = ui->gLay_userSwitch->rowCount();
    ui->gLay_userSwitch->addWidget(newRadioButtonAcc, userRow, 0, 1, 1);

    //add newLabel for total account TODO: GROUP RADIOBUTTONS
    QLabel *newLabel = new QLabel(this);
    newLabel->setText("0,00");
    ui->gLay_userSwitch->addWidget(newLabel, userRow, 1, 1, 1);

    ui->lineEdit_accountName->setText(NULL);
}


void MainWindow::on_btnSave_clicked()
{
    /*
    * Save accounts and bookings to database
    */


}

void MainWindow::on_btnLoad_clicked()
{
    Account::loadFromDatabase();
}



void MainWindow::on_lineEditDescription_returnPressed()
{
//    this->add2List();
}

void MainWindow::on_lineEditPrice_returnPressed()
{
//    this->add2List();
}


