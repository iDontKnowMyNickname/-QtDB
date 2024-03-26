#include "tablecars.h"

#include <QString>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

TableCars::TableCars(QString _host, int _port, QString _user_name, QString _user_pass, QString _db_name)
    : ITable(_host, _port, _user_name, _user_pass, _db_name)
{
    db = QSqlDatabase::addDatabase("QPSQL", "TableCars Connection");

    db.setHostName(host);
    db.setPort(port);
    db.setUserName(user_name);
    db.setPassword(user_pass);
    db.setDatabaseName(db_name);

    db.open();

    qDebug() << db.isOpen() << db.lastError().text() << '\n';
}

TableCars::~TableCars() {
    db.close();
}

QSqlQuery& TableCars::read() {
    if ( db.open() ) {
        QSqlQuery* query = new QSqlQuery(db);
        query -> exec("SELECT * FROM cars_data");

        qDebug() << query->lastError().text() << '\n';

        return (*query);
    }
    else {
        throw "Database is closed or something... Look at TableCars::read()\0";
    }
}

bool TableCars::insert(QList<QString> args) {
    if ( db.open() ) {
        // Если количество элементов не совпадает с количеством столбцов
        if ( args.size() != 5 ) {
            return false;
        }

        QSqlQuery query = QSqlQuery(db);
        query.prepare("INSERT INTO cars_data (car_number, car_mark, car_model, car_color, car_category) VALUES (:a0, :a1, :a2, :a3, :a4);");
        query.bindValue(":a0", args[0]);
        query.bindValue(":a1", args[1]);
        query.bindValue(":a2", args[2]);
        query.bindValue(":a3", args[3]);
        query.bindValue(":a4", args[4]);
        query.exec();

        qDebug() << query.lastError().text() << '\n';

        if ( query.lastError().text().length() ) {
            throw query.lastError().text();
        }

        return true;
    }
    else {
        throw "Database is closed or something... Look at TableCars::insert()\0";
    }
}

bool TableCars::remove(unsigned int ID) {
    if ( db.open() ) {
        QSqlQuery query = QSqlQuery(db);
        query.prepare("DELETE FROM cars_data WHERE car_id = :id;");
        query.bindValue(":id", ID);
        query.exec();

        qDebug() << query.lastError().text() << '\n';

        if ( query.lastError().text() == "" )
            return true;
        else
            return false;
    }
    else {
        throw "Database is closed or something... Look at TableCars::insert()\0";
    }
}

bool TableCars::isDBopen() {
    return db.isOpen();
}
