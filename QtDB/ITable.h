#ifndef ITABLE_H
#define ITABLE_H

#include <QString>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>

#include <QList>

// Интерфейс для двух классов, которые будут работать с таблицами
class ITable {
    public:
        ITable(QString _host, int _port, QString _user_name, QString _user_pass, QString _db_name) :
            host(_host), port(_port), user_name(_user_name), user_pass(_user_pass), db_name(_db_name) {};

        virtual ~ITable() {};

        // Читает всю таблицу и возвращает QSqlQuery, позволяющий построить таблицу в GUI
        virtual QSqlQuery& read() = 0;

        // Пытается вставить значение в таблицу. Возвращает true, если успешно, и false в противном случае
        virtual bool insert(QList<QString> args) = 0;

        // Удаляет значение из таблицы по ID. Возвращает true, если успешно, и false в противном случае
        virtual bool remove(unsigned int ID) = 0;

        // Проверяет, открыта ли БД
        virtual bool isDBopen() = 0;


    protected:
        QString host;       // Хост сервера БД
        int port;           // Порт сервера БД
        QString user_name;  // Имя пользователя БД
        QString user_pass;  // Пароль пользователя БД
        QString db_name;    // Название БД
};

//ITable::~ITable() {};

#endif // ITABLE_H
