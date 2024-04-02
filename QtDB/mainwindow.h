#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>

#include <dbasking.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Количество элементов на странице
    const int pageRows = 10;

signals:
    // Успешное подключение
    void connection_successful();
    // Неуспешное подключение
    void connection_failed();

public slots:
    // Получение данных для соединения
    void getConnectionData(QString s1, QString s2, QString s3, QString s4, QString s5);

private slots:
    // Предыдущая страница первой таблицы
    void on_pushButton_0_prev_clicked();
    // Следующая ~
    void on_pushButton_0_next_clicked();

    // Предыдущая страница второй таблицы
    void on_pushButton_1_prev_clicked();
    // Следующая
    void on_pushButton_1_next_clicked();

    // Кнопка "добавить водителя"
    void on_pushButton_0_add_clicked();
    // Кнопка "удалить водителя"
    void on_pushButton_0_delete_clicked();

    // Кнопка "добавить авто"
    void on_pushButton_1_add_clicked();
    // Кнопка "удалить авто"
    void on_pushButton_1_delete_clicked();

    // Общая таблица, предыдущая страница
    void on_pushButton_2_0_prev_clicked();
    // Общая таблица, следующая страница
    void on_pushButton_2_0_next_clicked();
    // Двойное нажатие на ячейку общей таблицы
    void on_tableWidget_2_0_cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;

    // инициализация таблиц и query
    void init();

    // Обновление каждой таблицы
    void update_table_0();
    void update_table_1();
    void update_table_2_0();
    void update_table_2_1( int ID );

    // База данных
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "QtDB Connection");

    // Четыре переменные под команды query, три количества страниц, три текущих страницы для таблиц
    QSqlQuery query_0;      int numPages_0;     int currentPage_0   = 1;
    QSqlQuery query_1;      int numPages_1;     int currentPage_1   = 1;
    QSqlQuery query_2_0;    int numPages_2_0;   int currentPage_2_0 = 1;
    QSqlQuery query_2_1;

};
#endif // MAINWINDOW_H
