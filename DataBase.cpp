#include "DataBase.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    connectDB();
}

bool DataBase::connectDB()
{

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");//mw_db.setHostName("127.0.0.1");
    db.setDatabaseName("my_data");
    db.setUserName("root");
    db.setPassword("myPass");
    db.setConnectOptions();

    if(!db.open())
    {
        qDebug() << "Cannot open database: " << db.lastError();
        return false; // Вернуть признак неудачного подключения.
    }
    return true;
}

bool DataBase::insertIntoTable(const QVariantList &data)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM my_payments WHERE date = :date");
    query.bindValue(":date", data[0]);
    query.exec();
    if(query.next())
    {
        query.prepare("UPDATE my_payments SET "
                   "gas_value = :gas_value,"
                   "light_value = :light_value,"
                   "water_bath_value = :water_bath_value,"
                   "water_toilet_value = :water_toilet_value,"
                   "comment = :comment,"
                   " WHERE date = :date");
        query.bindValue(":date",               data[0]);
        query.bindValue(":gas_value",          data[1]);
        query.bindValue(":light_value",        data[2]);
        query.bindValue(":water_bath_value",   data[3]);
        query.bindValue(":water_toilet_value", data[4]);
        query.bindValue(":comment",            data[5]);
    }
    else
    {
        query.prepare("INSERT INTO my_payments (date, gas_value, light_value, water_bath_value, water_toilet_value, comment) "
                      "VALUES (:date, :gas_value, :light_value, :water_bath_value, :water_toilet_value, :comment)");
        query.bindValue(":date",               data[0]);
        query.bindValue(":gas_value",          data[1]);
        query.bindValue(":light_value",        data[2]);
        query.bindValue(":water_bath_value",   data[3]);
        query.bindValue(":water_toilet_value", data[4]);
        query.bindValue(":comment",            data[5]);

    }

    if(!query.exec())
    {
        qDebug() << "error insert into my_payments";
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

void DataBase::fillTablePayments(QTableWidget* tablePayments)
{
    QSqlQuery query;
    query.exec("SELECT * FROM my_payments");
    for (int i = 0; query.next(); i++)
    {
        tablePayments->insertRow(i);
        QDate date = query.value(1).toDate();
        tablePayments->setItem(i, 0, new QTableWidgetItem(query.value(0).toString()));
        tablePayments->setItem(i, 1, new QTableWidgetItem(date.toString("MMMM yyyy")));
        tablePayments->setItem(i, 2, new QTableWidgetItem(query.value(2).toString()));
        tablePayments->setItem(i, 3, new QTableWidgetItem(query.value(3).toString()));
        tablePayments->setItem(i, 4, new QTableWidgetItem(query.value(4).toString()));
        tablePayments->setItem(i, 5, new QTableWidgetItem(query.value(5).toString()));
        tablePayments->setItem(i, 6, new QTableWidgetItem(query.value(6).toString()));

    }
}


DataBase::~DataBase()
{
    QSqlDatabase::removeDatabase("my_data");
}
