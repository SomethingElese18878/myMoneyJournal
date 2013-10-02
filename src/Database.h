#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QFileDialog>
#include <iostream>
#include <QFile>

class Database
{
public:
    Database();

    QSqlError initDb();
    void addAccount(QSqlQuery &q, const QString &name);
    void addBooking(QSqlQuery &q, const QString &description, const float &price, const float &total);
    float getTotal();
private:
    float total;

};

#endif // DATABASE_H
