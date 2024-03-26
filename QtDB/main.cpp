#include "mainwindow.h"

#include <QApplication>

#include <ITable.h>
#include <tableowners.h>

const QString host = "localhost";
const int port = 5432;
const QString user_name = "capybara";
const QString user_pass = "iamcapybara";
const QString db_name = "qtdb";

ITable* table_owners = new TableOwners(host, port, user_name, user_pass, db_name);

int main(int argc, char *argv[])
{
    QSqlQuery query = std::move( table_owners->read() );

    while ( query.next() ) {
        qDebug() << query.value(0) << query.value(1) << query.value(2) << query.value(3) << query.value(4) << query.value(5) << '\n';
    }

    QList<QString> args = {"КуСтрингов", "КуЛист", "", "1515", "456456", "86542316565"};
    table_owners -> insert( args );

    table_owners->remove( 2 );

    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    */
}
