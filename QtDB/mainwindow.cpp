#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DBAsking* dbask = new DBAsking();

    connect( &(*dbask), &DBAsking::buttonPressed, &(*this), &MainWindow::getConnectionData );
    connect( &(*this), &MainWindow::connection_successful, &(*dbask), &DBAsking::connection_successful );
    connect( &(*this), &MainWindow::connection_failed, &(*dbask), &DBAsking::connection_failed );

    dbask->setWindowModality(Qt::WindowModality::ApplicationModal);

    // this ->setEnabled(false);
    dbask->show();
    dbask->activateWindow();


    this->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getConnectionData(QString s1, QString s2, QString s3, QString s4, QString s5) {
    qDebug() << s1 << '\n' << s2 << '\n' << s3 << '\n' << s4 << '\n' << s5 << "\n\n";

    db.setHostName( s1 );
    db.setPort( s2.toInt() );
    db.setUserName( s3 );
    db.setPassword( s4 );
    db.setDatabaseName( s5 );

    if ( db.open() ) {
        emit connection_successful();
        this->setEnabled(true);
        this->setHidden(false);
    }
    else {
        qDebug() << db.lastError().text() << '\n';
        emit connection_failed();
    }
}
