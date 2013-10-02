#include "Database.h"

Database::Database()
{

}


void Database::addAccount(QSqlQuery &q, const QString &name)
{
    q.addBindValue(name);
    q.exec();
}

void Database::addBooking(QSqlQuery &q, const QDate &date, const QString &description, const float &price, const float &total)
{
    /*
     * Format of booking:
     * <description>   <date>     <price> <total>
     * food           17.12.2013  5,49    15,49
     */
    q.addBindValue(date.toString("dd.MM.yyyy"));    // <date>
    q.addBindValue(description); //<description>
    q.addBindValue(price);  // <price>
    q.addBindValue(total);  // <total>
    q.exec();
}

float Database::getTotal()
{
    QSqlQuery query("SELECT total FROM booking WHERE id = (SELECT MAX(ID) FROM booking)");
    if (!query.first()) return 0.0f;
    return query.value(0).toFloat();
}

QSqlError Database::initDb()
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

