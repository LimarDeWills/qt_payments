#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      db(new DataBase)
{
    setWindowIcon(QIcon("C:/Work/Qt/Training/Payment/meter.png"));
    setWindowTitle(tr("Показания счетчиков"));

    createMenus();
    createInterface();


    connect(addPayments_pb, &QPushButton::clicked, this, &MainWindow::insertInTable);
    connect(recordDateEdit, &QDateEdit::dateChanged, this, &MainWindow::setDatabyDate);
    
    setDatabyDate();
}

void MainWindow::createMenus()
{

    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *quitAct = fileMenu->addAction(tr("&Quit"), this, QApplication::quit);
    quitAct->setStatusTip(tr("Exit from the application"));
    quitAct->setShortcut(Qt::CTRL + Qt::Key_Q);

    QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));

    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    aboutAct->setShortcut(Qt::CTRL + Qt::Key_A);
}

void MainWindow::createInterface()
{
    QTabWidget* tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);
    createTablePayments();

    tabWidget->addTab(createCentralWidget(), tr("Показания"));
    tabWidget->addTab(tablePayments,         tr("Данные"));

}

QWidget* MainWindow::createCentralWidget()
{
    QWidget *centralWidget = new QWidget(this);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(mainLayout);

    QGridLayout* gLayout = new QGridLayout(centralWidget);

    mainLayout->addLayout(gLayout);

    QLabel *minimumDateLabel  = new QLabel(tr("Месяц:"),       centralWidget);
    QLabel *gasLable          = new QLabel(tr("Газ:"),         centralWidget);
    QLabel *lightLable        = new QLabel(tr("Свет:"),        centralWidget);
    QLabel *bathWaterLable    = new QLabel(tr("Вода ванна:"),  centralWidget);
    QLabel *toiletWater_lable = new QLabel(tr("Вода туалет:"), centralWidget);


    gLayout->addWidget(minimumDateLabel,  0, 0, Qt::AlignRight);
    gLayout->addWidget(gasLable,          1, 0, Qt::AlignRight);
    gLayout->addWidget(lightLable,        2, 0, Qt::AlignRight);
    gLayout->addWidget(bathWaterLable,    3, 0, Qt::AlignRight);
    gLayout->addWidget(toiletWater_lable, 4, 0, Qt::AlignRight);

    gas_LineEdit         = new QLineEdit(this);
    light_LineEdit       = new QLineEdit(this);
    bathWater_LineEdit   = new QLineEdit(this);
    toiletWater_LineEdit = new QLineEdit(this);

    gas_LineEdit->setValidator        ( new QDoubleValidator(0, 15, 2, this) );
    light_LineEdit->setValidator      ( new QDoubleValidator(0, 15, 2, this) );
    bathWater_LineEdit->setValidator  ( new QDoubleValidator(0, 15, 2, this) );
    toiletWater_LineEdit->setValidator( new QDoubleValidator(0, 15, 2, this) );

    recordDateEdit = new QDateEdit;
    recordDateEdit->setDisplayFormat("MMMM yyyy");
    recordDateEdit->setDateRange(QDate(2016, 1, 1),
                                 QDate(2100, 12, 31));
    QDate tempDate(QDate::currentDate());
    recordDateEdit->setDate(QDate(tempDate.year(), tempDate.month(), 1));

    comment_TextEdit = new QTextEdit(this);
    addPayments_pb   = new QPushButton(tr("&Записать"), this);

    gLayout->addWidget(recordDateEdit,       0, 1);
    gLayout->addWidget(gas_LineEdit,         1, 1);
    gLayout->addWidget(light_LineEdit,       2, 1);
    gLayout->addWidget(bathWater_LineEdit,   3, 1);
    gLayout->addWidget(toiletWater_LineEdit, 4, 1);
    gLayout->addWidget(comment_TextEdit,     5, 0, 4, 2);

    mainLayout->addWidget(addPayments_pb);

    return centralWidget;
}

void MainWindow::createTablePayments()
{
    QStringList headers;
    headers << "id"
            << "Дата"
            << "Газ"
            << "Свет"
            << "Вода ванна"
            << "Вода туалет"
            << "Комментарий";

    tablePayments = new QTableWidget(this);
    tablePayments->setColumnCount(headers.size());
    tablePayments->setHorizontalHeaderLabels(headers);
    tablePayments->horizontalHeader()->setStretchLastSection(true);
    tablePayments->hideColumn(0);

    fillTablePayments();

}

void MainWindow::fillTablePayments()
{
    while (tablePayments->rowCount() > 0)
    {
        tablePayments->removeRow(0);
    }

    db->fillTablePayments(tablePayments);
}

void MainWindow::insertInTable()
{
    QVariantList data;

    data.append(recordDateEdit->date().toString("yyyy-MM-dd"));
    data.append(gas_LineEdit->text().toFloat());
    data.append(light_LineEdit->text().toFloat());
    data.append(bathWater_LineEdit->text().toFloat());
    data.append(toiletWater_LineEdit->text().toFloat());
    data.append(comment_TextEdit->toPlainText());

    db->insertIntoTable(data);

    fillTablePayments();
}

void MainWindow::setFirstDayOfMonth()
{
    int m = recordDateEdit->date().month();
    int y = recordDateEdit->date().year();

    recordDateEdit->setDate(QDate(y, m, 1));
}

void MainWindow::setDatabyDate()
{
    MainWindow::setFirstDayOfMonth();
    
    QSqlQuery query;
    query.prepare("SELECT * FROM my_payments WHERE date = :date");
    query.bindValue(":date", recordDateEdit->date().toString("yyyy-MM-dd"));

    if(query.exec())
    {
        query.first();

        gas_LineEdit->setText(query.value(2).toString());
        light_LineEdit->setText(query.value(3).toString());
        bathWater_LineEdit->setText(query.value(4).toString());
        toiletWater_LineEdit->setText(query.value(5).toString());
        comment_TextEdit->setText(query.value(6).toString());

    }
    else
    {
        gas_LineEdit->setText("");
        light_LineEdit->setText("");
        bathWater_LineEdit->setText("");
        toiletWater_LineEdit->setText("");
        comment_TextEdit->setText("");
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, "About", "Information about this programm");
}

MainWindow::~MainWindow()
{

}

