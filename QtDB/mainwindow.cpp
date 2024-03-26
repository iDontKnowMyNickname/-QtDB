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
    QList<QString> args;
    QString error_message;

    QRegularExpression re;

    // Фамилия, имя, отчество
    re.setPattern( "^[\\ А-ЯЁа-яё'\\-]+$" );
    if ( re.match( ui->lineEdit->text() ).hasMatch() ) {
        args.append( ui->lineEdit->text() );
    }
    else {
        error_message += "Фамилия\n";
    }

    if ( re.match( ui->lineEdit_2->text() ).hasMatch() ) {
        args.append( ui->lineEdit_2->text() );
    }
    else {
        error_message += "Имя\n";
    }

    if ( re.match( ui->lineEdit_3->text() ).hasMatch() ) {
        args.append( ui->lineEdit_3->text() );
    }
    else {
        error_message += "Отчество\n";
    }

    // Серия паспорта
    re.setPattern( "^\\d\\d\\d\\d$" );
    if ( re.match( ui->spinBox->text() ).hasMatch() ) {
        args.append( ui->spinBox->text() );
    }
    else {
        error_message += "Серия паспорта\n";
    }
    // Номер паспорта
    re.setPattern( "^\\d\\d\\d\\d\\d\\d$" );
    if ( re.match( ui->spinBox_2->text() ).hasMatch() ) {
        args.append( ui->spinBox_2->text() );
    }
    else {
        error_message += "Номер паспорта\n";
    }
    // Номер телефона
    re.setPattern( "^8\\d\\d\\d\\d\\d\\d\\d\\d\\d\\d$" );
    if ( re.match( ui->lineEdit_4->text() ).hasMatch() ) {
        args.append( ui->lineEdit_4->text() );
    }
    else {
        error_message += "Номер телефона\n";
    }

    if ( !error_message.isEmpty() ) {
        QMessageBox::warning( 0, "Ошибка в полях:", error_message);
        return;
    }
    else {
        try {
            owner_table->insert(args);
        }
        catch (QString s) {
            QMessageBox::warning( 0, "Ошибка БД", s);
        }

        refreshTable0();
    }
}


void MainWindow::on_owner_remove_button_clicked()
{
    if (!owner_table->remove( ui->spinBox_3->value() ) ) {
        QMessageBox::warning( 0 , "Ошибка удаления!", "");
    }
    refreshTable0();
}


void MainWindow::on_car_add_button_clicked()
{
    QList<QString> args;
    QString error_message;

    QRegularExpression re;

    // Номер, марка, модель, цвет
    re.setPattern( "^[ABEKMHOPCTYX]\\d\\d\\d[ABEKMHOPCTYX]{2}\\d\\d\\d?RU$" );
    if ( re.match( ui->lineEdit_5->text() ).hasMatch() ) {
        args.append( ui->lineEdit_5->text() );
    }
    else {
        error_message += "Номер\n";
    }
    re.setPattern( "^[\\ А-ЯЁа-яёA-Za-z'\\-]+$" );
    if ( re.match( ui->lineEdit_6->text() ).hasMatch() ) {
        args.append( ui->lineEdit_6->text() );
    }
    else {
        error_message += "Марка\n";
    }

    if ( re.match( ui->lineEdit_7->text() ).hasMatch() ) {
        args.append( ui->lineEdit_7->text() );
    }
    else {
        error_message += "Модель\n";
    }
    if ( re.match( ui->lineEdit_9->text() ).hasMatch() ) {
        args.append( ui->lineEdit_9->text() );
    }
    else {
        error_message += "Цвет\n";
    }

    // Категория
    args.append( ui->comboBox->currentText() );

    if ( !error_message.isEmpty() ) {
        QMessageBox::warning( 0, "Ошибка в полях:", error_message);
        return;
    }
    else {
        try {
            car_table->insert(args);
        }
        catch (QString s) {
            QMessageBox::warning( 0, "Ошибка БД", s);
        }

        refreshTable1();
    }
}


void MainWindow::on_car_remove_button_clicked()
{
    if (!car_table->remove( ui->spinBox_6->value() ) ) {
        QMessageBox::warning( 0 , "Ошибка удаления!", "");
    }
    refreshTable1();
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
