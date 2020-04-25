#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QDate>

class DataBase : public QObject
{
public:
    explicit DataBase(QObject* parent = nullptr);
    ~DataBase();
    bool insertIntoTable(const QVariantList &data);
    void fillTablePayments(QTableWidget* tablePayments);
private:
    QSqlDatabase db;


    bool connectDB();

};

#endif // DATABASE_H
