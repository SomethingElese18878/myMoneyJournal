#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QFileDialog>
#include <QFile>
#include <QString>

#include <iostream>

class Database
{
public:
    Database();

    QSqlError initDb();
    void insertGeneric2Tables(QString tblName, QList<QString> columns, QList<QString> values);
    void updateGeneric2Tables(QString tblName, QString colName, QString valName, QString rowParam);
    void addAccount(QSqlQuery &q, const QString &name, const float &accBalance = 0.0f);
    QSqlError addBooking(const QString &activeBtn, const QDate& date,  const QString &description, const float &price, const float &total);
    QSqlError createBookingTable(QString newAccountName);
    QSqlError insertAccount(const QString &accountName);

    float getTotal();
    void setActiveUser(const QString &activeUser);


private:
    float total;

    QString activeUser;
    QString tblAccounts;


    QString cmdCreateTableAccounts;
    QString cmdCreateTableBooking;
    QString cmdCreateNewTable;
    QString cmdInsertIntoAccounts;
    QString tablenameBooking;
};

#endif // DATABASE_H
