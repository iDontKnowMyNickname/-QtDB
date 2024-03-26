#include "tablecars.h"

#include <QString>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

// Конструктор
TableCars::TableCars(QString _host, int _port, QString _user_name, QString _user_pass, QString _db_name)
    : ITable(_host, _port, _user_name, _user_pass, _db_name)
{
    // Создание объекта БД с заданными параметрами
    db = QSqlDatabase::addDatabase("QPSQL", "TableCars Connection");

    db.setHostName(host);
    db.setPort(port);
    db.setUserName(user_name);
    db.setPassword(user_pass);
    db.setDatabaseName(db_name);

    // Открытие БД
    db.open();

    // Вывод сведений об открытии и последней ошибки в отладочный поток
    qDebug() << db.isOpen() << db.lastError().text() << '\n';
}

// Закрытие БД при удалении объекта
TableCars::~TableCars() {
    db.close();
}

// Чтение из таблицы
QSqlQuery& TableCars::read() {
    // Если БД открыта
    if ( db.open() ) {
        // Создать объекта команды
        QSqlQuery* query = new QSqlQuery(db);
        // Выполнить команду извлечения всех данных таблицы
        query -> exec("SELECT * FROM cars_data");
        // Вывод последней ошибки
        qDebug() << query->lastError().text() << '\n';
        // Возврат объекта с данными из БД
        return (*query);
    }
    // При неуспехе генерация исключения
    else {
        throw "Database is closed or something... Look at TableCars::read()\0";
    }
}

// Добавление элемента
bool TableCars::insert(QList<QString> args) {
    if ( db.open() ) {
        // Если количество элементов не совпадает с количеством столбцов
        if ( args.size() != 5 ) {
            return false;
        }
        // Создать объект с подготовленным выражением, подставить атрибуты, применить команду
        QSqlQuery query = QSqlQuery(db);
        query.prepare("INSERT INTO cars_data (car_number, car_mark, car_model, car_color, car_category) VALUES (:a0, :a1, :a2, :a3, :a4);");
        query.bindValue(":a0", args[0]);
        query.bindValue(":a1", args[1]);
        query.bindValue(":a2", args[2]);
        query.bindValue(":a3", args[3]);
        query.bindValue(":a4", args[4]);
        query.exec();

        // Вывод отладочной информации - текст ошибки
        qDebug() << query.lastError().text() << '\n';

        // Если произошла ошибка, сгенерировать исключение на основе её текста
        if ( query.lastError().text().length() ) {
            throw query.lastError().text();
        }

        return true;
    }
    // Если БД закрыта, генерация ошибки
    else {
        throw "Database is closed or something... Look at TableCars::insert()\0";
    }
}

// Удаление элемента
bool TableCars::remove(unsigned int ID) {
    if ( db.open() ) {
        // Подготовка команды удаления по ID
        QSqlQuery query = QSqlQuery(db);
        query.prepare("DELETE FROM cars_data WHERE car_id = :id;");
        query.bindValue(":id", ID);
        query.exec();

        // Вывод ошибки
        qDebug() << query.lastError().text() << '\n';

        // Генерация исключения при наличии ошибки
        if ( query.lastError().text() == "" )
            return true;
        else
            return false;
    }
    else {
        throw "Database is closed or something... Look at TableCars::insert()\0";
    }
}

// Возврат истины, если БД открыта, иначе ложь
bool TableCars::isDBopen() {
    return db.isOpen();
}
