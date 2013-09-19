#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonBox_accepted()
{
    ui->lblShowBtnText->setText("OK!");
}

void MainWindow::on_buttonBox_rejected()
{
    ui->lblShowBtnText->setText("CANCEL");
}
