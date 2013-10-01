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
    this->allAccounts = new Account("allAccounts"); //TODO: Read-out users from database.

    //Implement database-model
    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
//        showError(err);
        return;
    }

    // Create the data model
    model = new QSqlRelationalTableModel(ui->tableBooking);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
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

    std::cout << "rowCount: " << model->rowCount() << std::endl;

    //Mapping database ==> widgets
//    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
//    mapper->setModel(model);
//    mapper->addMapping(ui->lineEditDescription, model->fieldIndex("description"));
//    mapper->addMapping(ui->lineEditPrice, model->fieldIndex("price"));

//    Values of marked entry are shown in lineEdit_description && lineEdit_price
//    connect(ui->tableBooking->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
//            mapper, SLOT(setCurrentModelIndex(QModelIndex)));
//    ui->tableBooking->setCurrentIndex(model->index(model->rowCount(), model->columnCount()));
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
    std::cout << "--- add2List ---" << std::endl;
    QSqlQuery q;
    if (!q.prepare(QLatin1String("insert into booking(description, price) values(?, ?)"))){
        return q.lastError();
    }
    QSqlRecord rec =  addBooking(q, ui->lineEditDescription->text(), ui->lineEditPrice->text().toInt());

    model->setTable("booking");
    model->select();
    ui->tableBooking->setModel(model);

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

void MainWindow::on_lineEditDescription_returnPressed()
{
    this->add2List();
}

void MainWindow::on_lineEditPrice_returnPressed()
{
    this->add2List();
}


