#include "mainwindow.h"

#include <QApplication>

#include <ITable.h>
#include <tableowners.h>
#include <tablecars.h>

// Константы, определяющие подключения
const QString      host = "localhost";
const     int      port = 5432;
const QString user_name = "capybara";
const QString user_pass = "iamcapybara";
const QString   db_name = "qtdb";

// Объекты таблиц
ITable* table_owners = new TableOwners(host, port, user_name, user_pass, db_name);
ITable* table_cars   = new   TableCars(host, port, user_name, user_pass, db_name);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr, table_owners, table_cars);
    w.show();
    return a.exec();
}
