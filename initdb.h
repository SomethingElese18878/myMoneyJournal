#ifndef INITDB_H
#define INITDB_H

#include <QtSql>
#include <QFileDialog>


QVariant addAccount(QSqlQuery &q, const QString &name)
{
    q.addBindValue(name);
    q.exec();
    return q.lastInsertId();
}

QSqlError initDb(QString filename)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");

    db.setHostName("localhost");
    db.setDatabaseName(filename);

    if (!db.open())
        return db.lastError();

    // ???
    QStringList tables = db.tables();
    if (tables.contains("booking", Qt::CaseInsensitive) && tables.contains("accounts", Qt::CaseInsensitive))
        return QSqlError();

    //Create tables
    QSqlQuery q;
    if (!q.exec(QLatin1String("create table booking(id integer primary key, description varchar)")))
        return q.lastError();
    if (!q.exec(QLatin1String("create table accounts(id integer primary key, name varchar)"))) //total for lbl?
        return q.lastError();

    //Insert datas into table
    if (!q.prepare(QLatin1String("insert into accounts(id, name) values(?, ?)")))
        return q.lastError();
    QVariant userNorman = addAccount(q, QLatin1String("norman"));
    QVariant userTest = addAccount(q, QLatin1String("test"));


}



#endif // INITDB_H
