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

    void setTables(ITable* owners, ITable* cars);

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_owner_add_button_clicked();

    void on_owner_remove_button_clicked();

    void on_car_add_button_clicked();

    void on_car_remove_button_clicked();

private:
    Ui::MainWindow *ui;

    ITable *owner_table, *car_table;

    void refreshTable0();

    void refreshTable1();
};
#endif // MAINWINDOW_H
