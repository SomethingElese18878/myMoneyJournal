#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    //Implement database-model
    Database *database = new Database();
    QSqlError err =  database->initDb();

    if (err.type() != QSqlError::NoError) {
//        showError(err);
        return;
    }

    // Create the data model
    model = new QSqlRelationalTableModel(ui->tableBooking);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable("booking");
    model->setHeaderData(model->fieldIndex("date"), Qt::Horizontal, tr("Date"));
    model->setHeaderData(model->fieldIndex("description"), Qt::Horizontal, tr("Description"));
    model->setHeaderData(model->fieldIndex("price"), Qt::Horizontal, tr("Price"));
    model->setHeaderData(model->fieldIndex("total"), Qt::Horizontal, tr("Total"));

    // Populate the model
    model->select();
    ui->tableBooking->setModel(model);
    ui->tableBooking->setColumnHidden(model->fieldIndex("id"), true);
    ui->tableBooking->setSelectionMode(QAbstractItemView::SingleSelection);
    // ColumnHeaders set to FIXED size, except for the "description" which is STRETCHED.
    ui->tableBooking->resizeColumnsToContents();
    ui->tableBooking->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);
    ui->tableBooking->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    ui->tableBooking->horizontalHeader()->setResizeMode(3, QHeaderView::Fixed);
    ui->tableBooking->horizontalHeader()->setResizeMode(4, QHeaderView::Fixed);
}


MainWindow::~MainWindow()
{
    delete ui;
}


QSqlError MainWindow::add2List()
{
    /*
    * add new Booking to database and ui->tableBooking;
    */

    float total = database->getTotal();
    total += ui->lineEditPrice->text().toFloat();
    std::cout << "--- add2List ---" << std::endl;
    QSqlQuery q;
    if (!q.prepare(QLatin1String("insert into booking(date, description, price, total) values(?, ?, ?, ?)"))){
        return q.lastError();
    }
    database->addBooking(q, ui->dateEdit->date(), ui->lineEditDescription->text(), ui->lineEditPrice->text().toFloat(), total);

    model->setTable("booking");
    model->select();
    ui->tableBooking->setModel(model);
    ui->tableBooking->resizeColumnsToContents(); //prevents that data will not shown correctly, if they got more digits as the field can show.
    if(!model->submitAll()) return q.lastError(); //use not necessary, but in thought on future-bugs implemented

    return q.lastError();
}


void MainWindow::on_lineEdit_accountName_returnPressed()
{
    /*
    * LINE EDIT for add accounts
    */
    //Add newUser-radiobutton
    QString new_account_name = ui->lineEdit_accountName->text();

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

void MainWindow::on_lineEditDescription_returnPressed()
{
    this->add2List();
}

void MainWindow::on_lineEditPrice_returnPressed()
{
    this->add2List();
}


