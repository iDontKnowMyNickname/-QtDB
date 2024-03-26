#ifndef TABLECARS_H
#define TABLECARS_H

#include "ITable.h"

class TableCars : public ITable
{
public:
    // Конструктор, принимающий хост, порт, имя пользователя, пароль, название БД
    TableCars(QString _host, int _port, QString _user_name, QString _user_pass, QString _db_name);
    // Деструктор
    virtual ~TableCars();
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
    //int port;           // Порт сервера БД
    //QString user_name;  // Имя пользователя БД
    //QString user_pass;  // Пароль пользователя БД
    //QString db_name;    // Название БД

    QSqlDatabase db;    // БД
};

#endif // TABLECARS_H
