#include "Database.h"

Database::Database()
{
    this->cmdCreateTableAccounts = QString("CREATE TABLE accounts(id INTEGER primary key, name VARCHAR, accBalance REAL)");
    this->cmdCreateTableBooking = QString("CREATE TABLE booking(id INTEGER primary key, Date TEXT, Description VARCHAR,  Price REAL, Total REAL)");

    this->cmdInsertIntoAccounts = "insert into accounts(name, accBalance) values(?,?)";
}


void Database::addAccount(QSqlQuery &q, const QString &name, const float &accBalance)
{
    q.addBindValue(name);
    q.addBindValue(accBalance);
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

QSqlError Database::createBookingTable(QString newAccountName)
{
    QSqlQuery q;
    tablenameBooking = newAccountName + QString("_booking");
    this->cmdCreateNewTable = QString("CREATE TABLE ") + tablenameBooking + QString("(id INTEGER primary key, date TEXT, description VARCHAR,  price REAL, total REAL)");

    std::cout << "cmdNuff: " << this->cmdCreateNewTable.toStdString() << std::endl;
    if (!q.exec(this->cmdCreateNewTable))
        return q.lastError();
   return q.lastError();
}

QSqlError Database::insertAccount(const QString &accountName)
{
    QSqlQuery q;
    if (!q.prepare(this->cmdInsertIntoAccounts))
        return q.lastError();
    this->addAccount(q, accountName);
    return q.lastError();
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
        if (!q.exec(this->cmdCreateTableAccounts)) //total for lbl?
            return q.lastError();
        if (!q.exec(this->cmdCreateTableBooking))
            return q.lastError();

        // Example: Insert datas into table ACCOUNTS
            if (!q.prepare(this->cmdInsertIntoAccounts))
                return q.lastError();
            this->addAccount(q, QLatin1String("All accounts"));
    }
    return QSqlError();
}

