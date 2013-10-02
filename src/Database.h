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
    void addAccount(QSqlQuery &q, const QString &name);
    void addBooking(QSqlQuery &q, const QDate& date,  const QString &description, const float &price, const float &total);
    QSqlError createBookingTable(QString newAccountName);
    QSqlError insertAccount(const QString &accountName);
    float getTotal();

private:
    float total;

    QString cmdCreateTableAccounts;
    QString cmdCreateTableBooking;
    QString cmdCreateNewTable;
    QString tablenameBooking;
};

#endif // DATABASE_H
