#ifndef INITDB_H
#define INITDB_H

#include <QtSql>
#include <QFileDialog>
#include <iostream>
#include <QFile>

void addAccount(QSqlQuery &q, const QString &name)
{
    q.addBindValue(name);
    q.exec();
}

void addBooking(QSqlQuery &q, const QString &description, const float &price)
{
    /*
     * Format of booking:
     * <description>   <date>     <price> <total>
     * food           17.12.2013  5,49    15,49
     */
    QString currentDate = QDate::currentDate().toString("dd.MM.yyyy");

    q.addBindValue(currentDate);    // <date>
    q.addBindValue(description); //<description>
    q.addBindValue(price);  // <price>
    q.addBindValue("0");  // <total>

    q.exec();
}

QSqlError initDb()
{
    /*
    *   Initiates a database with the table ACCOUNTS and BOOKING.
    */
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //db connection name
    const QString db_name = "db_moneyJournal";
    db.setHostName("127.0.0.1");
    db.setDatabaseName(db_name);

    bool db_exist = QFile::exists(db_name);
    std::cout << "db_exist: " << db_exist << std::endl;

    //Open db
    if (!db.open()) return db.lastError();

    //Read-in the existing tables.
    if (db_exist){
        // parses existing tables into model.
        QStringList tables = db.tables();
        if (tables.contains("booking", Qt::CaseInsensitive) && tables.contains("accounts", Qt::CaseInsensitive))
            std::cout << "TABLES CONTAINS!!!!" << std::endl;
            return QSqlError();
    } else{
        //Create tables ACCOUNTS & BOOKING, if no database exists.
        //Creates default ACCOUNT "All accounts".
        QSqlQuery q;
        if (!q.exec(QLatin1String("CREATE TABLE accounts(id INTEGER primary key, name VARCHAR)"))) //total for lbl?
            return q.lastError();
        if (!q.exec(QLatin1String("CREATE TABLE booking(id INTEGER primary key, date TEXT, description VARCHAR,  price REAL, total REAL)")))
            return q.lastError();

        // Example: Insert datas into table ACCOUNTS
            if (!q.prepare(QLatin1String("insert into accounts(name) values(?)")))
                return q.lastError();
            addAccount(q, QLatin1String("All accounts"));
    }
    return QSqlError();
}



#endif // INITDB_H
