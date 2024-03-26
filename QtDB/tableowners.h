#ifndef TABLEOWNERS_H
#define TABLEOWNERS_H

#include <ITable.h>

class TableOwners : public ITable
{
public:
    // Конструктор, принимающий хост, порт, имя пользователя, пароль, название БД
    TableOwners(QString _host, int _port, QString _user_name, QString _user_pass, QString _db_name);
    // Деструктор
    virtual ~TableOwners();
    // Чтение из таблицы
    virtual QSqlQuery& read();
    // Вставка в таблицу
    virtual bool insert(QList<QString> args);
    // Удаление из таблицы
    virtual bool remove(unsigned int ID);
    // Проверка открытия
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
