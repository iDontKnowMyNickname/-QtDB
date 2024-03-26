#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QStandardItemModel>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <QMessageBox>

#include <ITable.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, ITable* owners = nullptr, ITable* cars = nullptr);
    ~MainWindow();

    // Сеттер для таблиц
    void setTables(ITable* owners, ITable* cars);

private slots:
    // Обновление таблиц при смене вкладок
    void on_tabWidget_currentChanged(int index);
    // Добавление владельца
    void on_owner_add_button_clicked();
    // Удаление владельца
    void on_owner_remove_button_clicked();
    // Добавление машины
    void on_car_add_button_clicked();
    // Удаление машины
    void on_car_remove_button_clicked();

private:
    Ui::MainWindow *ui;
    // Указатели на объекты, работающие с таблицами
    ITable *owner_table, *car_table;
    // Обновление виджета с таблицей владельцев
    void refreshTable0();
    // Обновление виджета с таблицей пользователей
    void refreshTable1();
};
#endif // MAINWINDOW_H
