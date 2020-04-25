#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QWidget>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QHeaderView>
#include <QDate>
#include <QDateEdit>


#include "DataBase.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void insertInTable();
    void setDatabyDate();
private:
    QDateEdit *recordDateEdit;
    QLineEdit *gas_LineEdit;
    QLineEdit *light_LineEdit;
    QLineEdit *bathWater_LineEdit;
    QLineEdit *toiletWater_LineEdit;
    QTextEdit *comment_TextEdit;
    QPushButton *addPayments_pb;

    QTableView     *paymentsView;
    QTableWidget   *tablePayments;

    DataBase *db;

    QWidget *createCentralWidget();

    void createTablePayments();
    void fillTablePayments();
    void createMenus();
    void createInterface();
    void about();
    void setFirstDayOfMonth();

};
#endif // MAINWINDOW_H
