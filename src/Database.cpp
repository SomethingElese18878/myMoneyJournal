#include "Database.h"

Database::Database()
{
    this->activeUser = "All_Accounts";
    this->tblAccounts = "accounts";

    this->cmdCreateTableAccounts = QString("CREATE TABLE accounts(id INTEGER primary key, name VARCHAR, accBalance REAL)");
    this->cmdCreateTableBooking = QString("CREATE TABLE ") + this->activeUser + QString("(id INTEGER primary key, Date TEXT, Description VARCHAR,  Price REAL, Total REAL)");

    this->cmdInsertIntoAccounts = "insert into " + QString(tblAccounts) + "(name, accBalance) values(?,?)";
}


void Database::insertGeneric2Tables(QString tblName, QList<QString> listCol, QList<QString> listVal)
{
    /* UNDER CONSTRUCTION - replaces addBooking, addAccounts?
     * @tblName: table in which you want to insert
     * @listCol: columns which have to be inserted
     * @listVal: values which have to be inserted to the selected columns
     */
    QString cmdCol = QString("(");
    QString cmdVal = QString("values(");

    for(int i = 0; i < listCol.size(); i++){
        qDebug() << i << listCol[i];
        cmdCol.append(listCol[i] + ", ");
        cmdVal.append("?, ");
    }
    //replace last ',' with ')'
    cmdCol.replace(cmdCol.lastIndexOf(", "), 1, ")");
    cmdVal.replace(cmdVal.lastIndexOf(", "), 1, ")");

    QString cmdInsert = "insert into " + tblName + cmdCol + cmdVal;
    qDebug() << "cmdInsert: " << cmdInsert;

//    QSqlQuery q;
}

void Database::updateGeneric2Tables(QString tblName, QString colName, QString valName, QString rowParam)
{
    /*
     *@tblName: table in which you want to update
     *@nameCol: columns which have to be inserted
     *@listVal: values which have to be inserted to the selected columns
     *
     *cmdUpdate
     *  UPDATE <accounts>
     *  SET <accBalance> = <200>
     *  WHERE <name> = <"peter">;
     */
    QString cmdUpdate = "update " + tblName
            + " SET " + colName + " = " + valName
            + " WHERE " + rowParam + " = " + "\"" + this->activeUser + "\"";
    qDebug() << "cmdInsert: " << cmdUpdate;
    QSqlQuery q(cmdUpdate);
    q.exec();
}

void Database::addAccount(QSqlQuery &q, const QString &name, const float &accBalance)
{
    q.addBindValue(name);
    q.addBindValue(accBalance);
    q.exec();
}

QSqlError Database::addBooking(const QString &activeBtn, const QDate &date, const QString &description, const float &price, const float &total)
{
    /*
     * Format of booking:
     * <description>   <date>     <price> <total>
     * food           17.12.2013  5,49    15,49
     */
    QString cmdInsertActiveAccount = QString("insert into ") + activeBtn + QString("(date, description, price, total) values(?, ?, ?, ?)");
    QSqlQuery q;
    if (!q.prepare(cmdInsertActiveAccount)){
        return q.lastError();
    }
    q.addBindValue(date.toString("dd.MM.yyyy"));    // <date>
    q.addBindValue(description); //<description>
    q.addBindValue(price);  // <price>
    q.addBindValue(total);  // <total>
    q.exec();

    this->updateGeneric2Tables(tblAccounts, "accBalance", QString::number(total), "name");
    return q.lastError();
}

QSqlError Database::createBookingTable(QString newAccountName)
{
    QSqlQuery q;
    tablenameBooking = newAccountName;
    this->cmdCreateNewTable = QString("CREATE TABLE ") + tablenameBooking + QString("(Id INTEGER primary key, Date TEXT, Description VARCHAR,  Price REAL, Total REAL)");

    qDebug() << "CreateTable: " << cmdCreateNewTable;
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

void Database::setActiveUser(const QString &activeUser)
{
    this->activeUser = activeUser;
    qDebug() << "setActiveUser: " << this->activeUser;
}

float Database::getTotal()
{
    QString cmdGetTotal = QString("SELECT total FROM ") + activeUser + QString(" WHERE id = (SELECT MAX(ID) FROM ") + activeUser + QString(")");
    QSqlQuery query(cmdGetTotal);
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
        if (tables.contains(activeUser, Qt::CaseInsensitive) && tables.contains("accounts", Qt::CaseInsensitive))
            std::cout << "TABLES CONTAINS!!!!" << std::endl;
            return QSqlError();
    } else{
        //Create tables ACCOUNTS & BOOKING, if no database exists.
        QSqlQuery q;
        if (!q.exec(this->cmdCreateTableAccounts)) //total for lbl?
            return q.lastError();
        if (!q.exec(this->cmdCreateTableBooking))
            return q.lastError();

        // Example: Insert datas into table ACCOUNTS
            if (!q.prepare(this->cmdInsertIntoAccounts))
                return q.lastError();
            this->addAccount(q, activeUser);
    }
    return QSqlError();
}

