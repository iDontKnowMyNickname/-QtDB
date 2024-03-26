#include "tableowners.h"

#include <QString>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

TableOwners::TableOwners(QString _host, int _port, QString _user_name, QString _user_pass, QString _db_name)
    : ITable(_host, _port, _user_name, _user_pass, _db_name)
{
    db = QSqlDatabase::addDatabase("QPSQL", "TableOwners Connection");

    db.setHostName(host);
    db.setPort(port);
    db.setUserName(user_name);
    db.setPassword(user_pass);
    db.setDatabaseName(db_name);

    db.open();

    qDebug() << db.isOpen() << db.lastError().text() << '\n';
}

TableOwners::~TableOwners() {
    db.close();
}

QSqlQuery& TableOwners::read() {
    if ( db.open() ) {
        QSqlQuery* query = new QSqlQuery(db);
        query -> exec("SELECT * FROM owners_data");

        qDebug() << query->lastError().text() << '\n';

        return (*query);
    }
    else {
        throw "Database is closed or something... Look at TableOwners::read()\0";
    }
}

bool TableOwners::insert(QList<QString> args) {
    if ( db.open() ) {
        // Если количество элементов не совпадает с количеством столбцов
        if ( args.size() != 6 ) {
            return false;
        }

        QSqlQuery query = QSqlQuery(db);
        query.prepare("INSERT INTO owners_data (last_name, first_name, patronymic, pass_series, pass_number, phone_number) VALUES (:a0, :a1, :a2, :a3, :a4, :a5);");
        query.bindValue(":a0", args[0]);
        query.bindValue(":a1", args[1]);
        query.bindValue(":a2", args[2]);
        query.bindValue(":a3", args[3]);
        query.bindValue(":a4", args[4]);
        query.bindValue(":a5", args[5]);
        query.exec();

        qDebug() << query.lastError().text() << '\n';

        if ( query.lastError().text().length() ) {
            throw query.lastError().text();
        }

        return true;
    }
    else {
        throw "Database is closed or something... Look at TableOwners::insert()\0";
    }
}

bool TableOwners::remove(unsigned int ID) {
    if ( db.open() ) {
        QSqlQuery query = QSqlQuery(db);
        query.prepare("DELETE FROM owners_data WHERE owner_id = :id;");
        query.bindValue(":id", ID);
        query.exec();

        qDebug() << query.lastError().text() << '\n';
        if ( query.lastError().text() == "" )
            return true;
        else
            return false;
    }
    else {
        throw "Database is closed or something... Look at TableOwners::insert()\0";
    }
}

bool TableOwners::isDBopen() {
    return db.isOpen();
}
