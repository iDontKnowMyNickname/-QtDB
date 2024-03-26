#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, ITable* owners, ITable* cars)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , owner_table(owners)
    , car_table(cars)

{
    ui->setupUi(this);

    refreshTable0();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if ( index == 0) {
        refreshTable0();
    }
    else if ( index == 1) {
        refreshTable1();
    }
    else {
        return;
    }
}

void MainWindow::setTables(ITable* owners, ITable* cars) {
    owner_table = owners;
      car_table = cars;
}

void MainWindow::on_owner_add_button_clicked()
{

}


void MainWindow::on_owner_remove_button_clicked()
{

}


void MainWindow::on_car_add_button_clicked()
{

}


void MainWindow::on_car_remove_button_clicked()
{

}

void MainWindow::refreshTable0() {
    QSqlQuery query = std::move( owner_table->read() );

    while ( ui->tableWidget->rowCount() ) {
        ui->tableWidget->removeRow( 0 );
    }

    while ( query.next() ) {
        ui->tableWidget->insertRow( 0 );

        ui->tableWidget->setItem( 0, 0, new QTableWidgetItem( query.value(0).toString() ) );
        ui->tableWidget->setItem( 0, 1, new QTableWidgetItem( query.value(1).toString() ) );
        ui->tableWidget->setItem( 0, 2, new QTableWidgetItem( query.value(2).toString() ) );
        ui->tableWidget->setItem( 0, 3, new QTableWidgetItem( query.value(3).toString() ) );
        ui->tableWidget->setItem( 0, 4, new QTableWidgetItem( query.value(4).toString() ) );
        ui->tableWidget->setItem( 0, 5, new QTableWidgetItem( query.value(5).toString() ) );
        ui->tableWidget->setItem( 0, 6, new QTableWidgetItem( query.value(6).toString() ) );

    }
}

void MainWindow::refreshTable1() {
    QSqlQuery query = std::move( car_table->read() );

    while ( ui->tableWidget_2->rowCount() ) {
        ui->tableWidget_2->removeRow( 0 );
    }

    while ( query.next() ) {
        ui->tableWidget_2->insertRow( 0 );

        ui->tableWidget_2->setItem( 0, 0, new QTableWidgetItem( query.value(0).toString() ) );
        ui->tableWidget_2->setItem( 0, 1, new QTableWidgetItem( query.value(1).toString() ) );
        ui->tableWidget_2->setItem( 0, 2, new QTableWidgetItem( query.value(2).toString() ) );
        ui->tableWidget_2->setItem( 0, 3, new QTableWidgetItem( query.value(3).toString() ) );
        ui->tableWidget_2->setItem( 0, 4, new QTableWidgetItem( query.value(4).toString() ) );
        ui->tableWidget_2->setItem( 0, 5, new QTableWidgetItem( query.value(5).toString() ) );
    }
}
