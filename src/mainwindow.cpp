#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->btnGroup_user = new QButtonGroup();

    //Implement database-model
    this->database = new Database();
    QSqlError err =  database->initDb();

    if (err.type() != QSqlError::NoError) {
//        showError(err);
        return;
    }

    //addBooking
    ui->lineEditDescription->setFocus();
    ui->dateEdit->setDate(QDate::currentDate());

    //Sidebar
    this->updateUsers(); // default value i = 0 will add allUsers

    // Create the data model
    model = new QSqlRelationalTableModel(ui->tableBooking);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable("booking");
    model->setHeaderData(model->fieldIndex("Date"), Qt::Horizontal, tr("Date"));
    model->setHeaderData(model->fieldIndex("Description"), Qt::Horizontal, tr("Description"));
    model->setHeaderData(model->fieldIndex("Price"), Qt::Horizontal, tr("Price"));
    model->setHeaderData(model->fieldIndex("Total"), Qt::Horizontal, tr("Total"));

    // Populate the model
    model->select();
    ui->tableBooking->setModel(model);
    ui->tableBooking->setColumnHidden(model->fieldIndex("id"), true);
    ui->tableBooking->setSelectionMode(QAbstractItemView::SingleSelection);
    // ColumnHeaders set to FIXED size, except for the "description" which is STRETCHED.
    ui->tableBooking->resizeColumnsToContents();
    ui->tableBooking->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->tableBooking->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableBooking->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    ui->tableBooking->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUsers(int i)
{
    /*
     * Default: int i = 0 ==> allUsers will be added.
     * If is set to: ui->gLay_userSwitch->rowCount() - 1
     */
    userModel = new QSqlQueryModel();
    userModel->setQuery("SELECT name, accBalance FROM accounts");

    for (i; i < userModel->rowCount(); ++i) {
          QString name = userModel->record(i).value("name").toString();
          QString accBalance = userModel->record(i).value("accBalance").toString();
          QLabel *lbl = new QLabel(accBalance);
          QRadioButton *newRadioBtnAccount = new QRadioButton(this);
          btnGroup_user->addButton(newRadioBtnAccount);
          newRadioBtnAccount->setText(name);
          if(i < 1) newRadioBtnAccount->setChecked(true);   //Check first element
          newRadioBtnAccount->show();
          int userRow = ui->gLay_userSwitch->rowCount();
          ui->gLay_userSwitch->addWidget(newRadioBtnAccount, userRow, 0, 1, 1);
          ui->gLay_userSwitch->addWidget(lbl, userRow, 1, 1, 1);
          qDebug() << name << accBalance;
      }
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
    QString newAccountName = ui->lineEdit_accountName->text();
    this->database->insertAccount(newAccountName);
    this->database->createBookingTable(newAccountName);
    this->updateUsers(ui->gLay_userSwitch->rowCount() - 1);

}

void MainWindow::on_lineEditDescription_returnPressed()
{
    this->add2List();
}

void MainWindow::on_lineEditPrice_returnPressed()
{
    this->add2List();
}


