#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent, ITable* owners, ITable* cars)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , owner_table(owners)
    , car_table(cars)

{
    ui->setupUi(this);
    // Обновление таблицы на первой вкладке
    refreshTable0();
}

MainWindow::~MainWindow()
{
    delete ui;
    // Очистка памяти, занятой таблицами
    delete owner_table, car_table;
}

// Смена вкладки
void MainWindow::on_tabWidget_currentChanged(int index)
{
    // Если первая вкладка, обновить таблицу на первой вкладке
    if ( index == 0) {
        refreshTable0();
    }
    // Если вторая вкладка, обновить таблицу на второй вкладке
    else if ( index == 1) {
        refreshTable1();
    }
    // Иначе ничего не делать
    else {
        return;
    }
}

// Сеттер для указателей таблиц
void MainWindow::setTables(ITable* owners, ITable* cars) {
    owner_table = owners;
      car_table = cars;
}

// Добавление владельца
void MainWindow::on_owner_add_button_clicked()
{
    QList<QString> args;    // Передаваемые БД атрибуты
    QString error_message;  // Строка с неправильно введенными полями

    QRegularExpression re;  // Регулярное выражение для проверки данных

    // Фамилия, имя, отчество
    re.setPattern( "^[\\ А-ЯЁа-яё'\\-]+$" );
    if ( re.match( ui->lineEdit->text() ).hasMatch() ) {
        args.append( ui->lineEdit->text() ); // Добавить, если проверка пройдена
    }
    else {
        error_message += "Фамилия\n";        // Иначе добавить в ошибки
    }

    if ( re.match( ui->lineEdit_2->text() ).hasMatch() ) {
        args.append( ui->lineEdit_2->text() );  // Добавление
    }
    else {
        error_message += "Имя\n";               // Ошибка
    }

    if ( re.match( ui->lineEdit_3->text() ).hasMatch() ) {
        args.append( ui->lineEdit_3->text() );  // Добавление
    }
    else {
        error_message += "Отчество\n";          // Ошибка
    }

    // Серия паспорта
    re.setPattern( "^\\d\\d\\d\\d$" );
    if ( re.match( ui->spinBox->text() ).hasMatch() ) {
        args.append( ui->spinBox->text() );     // Добавление
    }
    else {
        error_message += "Серия паспорта\n";    // Ошибка
    }
    // Номер паспорта
    re.setPattern( "^\\d\\d\\d\\d\\d\\d$" );
    if ( re.match( ui->spinBox_2->text() ).hasMatch() ) {
        args.append( ui->spinBox_2->text() );   // Добавление
    }
    else {
        error_message += "Номер паспорта\n";    // Ошибка
    }
    // Номер телефона
    re.setPattern( "^8\\d\\d\\d\\d\\d\\d\\d\\d\\d\\d$" );
    if ( re.match( ui->lineEdit_4->text() ).hasMatch() ) {
        args.append( ui->lineEdit_4->text() );  // Добавление
    }
    else {
        error_message += "Номер телефона\n";    // Ошибка
    }

    // Если строка с ошибками не пуста, вывести окно с неправильно введенными полями
    if ( !error_message.isEmpty() ) {
        QMessageBox::warning( 0, "Ошибка в полях:", error_message);
        return;
    }
    // Иначе (с обработкой ошибок) добавить элемент
    else {
        try {
            owner_table->insert(args);
        }
        // В случае ошибки, вывести окно с текстом ошибки
        catch (QString s) {
            QMessageBox::warning( 0, "Ошибка БД", s);
        }
        // Обновить таблицу
        refreshTable0();
    }
}

// Удаление владельца
void MainWindow::on_owner_remove_button_clicked()
{
    // Если метод вернет ошибку, вывести окно
    if (!owner_table->remove( ui->spinBox_3->value() ) ) {
        QMessageBox::warning( 0 , "Ошибка удаления!", "");
    }
    // Обновить таблицу
    refreshTable0();
}

// Аналогично добавлению владельца, добавление машины
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

    // Категория задана в UI и соответствует ENUM в БД
    args.append( ui->comboBox->currentText() );

    // Если были ошибки, вывести окно с ошибками
    if ( !error_message.isEmpty() ) {
        QMessageBox::warning( 0, "Ошибка в полях:", error_message);
        return;
    }
    // Иначе (с обработкой ошибок) добавить элемент
    else {
        try {
            car_table->insert(args);
        }
        // В случае ошибки вывести окно с текстом ошибки
        catch (QString s) {
            QMessageBox::warning( 0, "Ошибка БД", s);
        }
        // Обновить таблицу
        refreshTable1();
    }
}

// Удаление машины
void MainWindow::on_car_remove_button_clicked()
{
    // Если произошла ошибка, вывести окно ошибки
    if (!car_table->remove( ui->spinBox_6->value() ) ) {
        QMessageBox::warning( 0 , "Ошибка удаления!", "");
    }
    refreshTable1();
}

// Обновление первой таблицы
void MainWindow::refreshTable0() {
    // Получить данные из таблицы БД
    QSqlQuery query = std::move( owner_table->read() );

    // Удалить все строки текущей таблицы
    while ( ui->tableWidget->rowCount() ) {
        ui->tableWidget->removeRow( 0 );
    }
    // Добавлять сверху строки, заполнять строки элементами
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

// Обновление второй таблицы
void MainWindow::refreshTable1() {
    // Получить данные из таблицы БД
    QSqlQuery query = std::move( car_table->read() );

    // Удалить все строки текущей таблицы
    while ( ui->tableWidget_2->rowCount() ) {
        ui->tableWidget_2->removeRow( 0 );
    }
    // Добавлять сверху строки, заполнять строки элементами
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
