#ifndef TABLEOWNERS_H
#define TABLEOWNERS_H

#include <ITable.h>

class TableOwners : public ITable
{
public:
    TableOwners(QString _host, int _port, QString _user_name, QString _user_pass, QString _db_name);

    virtual QSqlQuery& read();

    virtual bool insert(QList<QString> args);

    virtual bool remove(unsigned int ID);

    virtual bool isDBopen();

protected:
    //QString host;       // Хост сервера БД
    //int port;       // Порт сервера БД
    //QString user_name;  // Имя пользователя БД
    //QString user_pass;  // Пароль пользователя БД
    //QString db_name;    // Название БД

    QSqlDatabase db;    // БД
};

#endif // TABLEOWNERS_H
