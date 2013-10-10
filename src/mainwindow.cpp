#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->btnGroup_user = new QButtonGroup();
    QObject::connect(btnGroup_user, SIGNAL(buttonClicked(int)), this, SLOT(userChanged(int)));
    //Implement database-model
    this->database = new Database();
    database->initDb();
    qDebug() << "afterInit";
    //addBooking
    ui->lineEditDescription->setFocus();
    ui->dateEdit->setDate(QDate::currentDate());

    //Sidebar
    this->updateUsers(false); // default value i = 0 will add allUsers

    // Create the data model
    model = new QSqlRelationalTableModel(ui->tableBooking);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable("All_Accounts");
    model->setHeaderData(model->fieldIndex("Date"), Qt::Horizontal, tr("Date"));
    model->setHeaderData(model->fieldIndex("Description"), Qt::Horizontal, tr("Description"));
    model->setHeaderData(model->fieldIndex("Price"), Qt::Horizontal, tr("Price"));
    model->setHeaderData(model->fieldIndex("Total"), Qt::Horizontal, tr("Total"));

    // Populate the model
//    model->select();
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

void MainWindow::updateUsers(bool addUserFlag)
{
    /*
     * i = 0 (default!) ==> allUsers will be added.
     * i = rowCount() - 1 it adds only the last.
     */
    int i;
    if(addUserFlag){
        i = ui->gLay_userSwitch->rowCount() - 1;
    }else{
        i = 0;
    }
    userModel = new QSqlQueryModel();
    userModel->setQuery("SELECT name, accBalance FROM accounts");

    for (i; i < userModel->rowCount(); i++) {
          QString name = userModel->record(i).value("name").toString();
          QString accBalance = userModel->record(i).value("accBalance").toString();
          QLabel *lbl = new QLabel(accBalance);
          QRadioButton *newRadioBtnAccount = new QRadioButton(this);

          this->listUserBtn.append(newRadioBtnAccount);
          this->listUserLbl.append(lbl);

          btnGroup_user->addButton(newRadioBtnAccount);
          btnGroup_user->setId(newRadioBtnAccount, ui->gLay_userSwitch->rowCount());
          newRadioBtnAccount->setText(name);
          if(i < 1){
              newRadioBtnAccount->setChecked(true);   //Check first element - AddAllUsers
          } else if(addUserFlag) {
              newRadioBtnAccount->setChecked(true);
          }
          newRadioBtnAccount->show();

          int userRow = ui->gLay_userSwitch->rowCount();
          ui->gLay_userSwitch->addWidget(newRadioBtnAccount, userRow, 0, 1, 1);
          ui->gLay_userSwitch->addWidget(lbl, userRow, 1, 1, 1);
      }
}


void MainWindow::add2List()
{
    /*
    * add new Booking to database and ui->tableBooking;
    */
    float total = database->getTotal();
    total += ui->lineEditPrice->text().toFloat();

    QString activeBtn = btnGroup_user->checkedButton()->text();
    database->addBooking(activeBtn, ui->dateEdit->date(), ui->lineEditDescription->text(), ui->lineEditPrice->text().toFloat(), total);
    //Search for position of activeUser and set the related label to the totalAmount of the account.
    for(int i = 0; i < listUserBtn.size(); i++){
        if(listUserBtn[i]->text() == activeBtn){
            listUserLbl[i]->setText(QString::number(total));
            break;
        }
    }

    model->setTable(activeBtn);
    model->select();
    ui->tableBooking->setModel(model);
    ui->tableBooking->resizeColumnsToContents(); //prevents that data will not shown correctly, if they got more digits as the field can show.
}


void MainWindow::on_lineEdit_accountName_returnPressed()
{
    /*
    * Add new User
    */
    QString newAccountName = ui->lineEdit_accountName->text();
    this->database->insertAccount(newAccountName);
    this->database->createBookingTable(newAccountName);
    this->updateUsers(true);
    this->userChanged(0);
    ui->lineEdit_accountName->setText("");
}

void MainWindow::on_lineEditDescription_returnPressed()
{
    this->add2List();
}

void MainWindow::on_lineEditPrice_returnPressed()
{
    this->add2List();
}

void MainWindow::userChanged(int id)
{
    /*
     * Triggered by clicked radioButton.
     */
    QString activeUser = btnGroup_user->checkedButton()->text();
    model->setTable(activeUser);
    model->select();
    ui->tableBooking->resizeColumnsToContents();

    this->database->setActiveUser(activeUser);
}
