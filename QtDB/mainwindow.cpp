#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создание окна с данными подключения
    DBAsking* dbask = new DBAsking();

    // Соединение сигнала нажатия кнопки dbasking в mainwindow, аналогично обработчики подключения в dbasking
    connect( &(*dbask), &DBAsking::buttonPressed, &(*this), &MainWindow::getConnectionData );
    connect( &(*this), &MainWindow::connection_successful, &(*dbask), &DBAsking::connection_successful );
    connect( &(*this), &MainWindow::connection_failed, &(*dbask), &DBAsking::connection_failed );

    // сделать модальным (остальные окна недоступны)
    dbask->setWindowModality(Qt::WindowModality::ApplicationModal);

    // this ->setEnabled(false);
    // Показать
    dbask->show();
    // Сделать акцент/фокус на окне
    dbask->activateWindow();

    // Спрятать главное окно
    this->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Подключиться к БД
void MainWindow::getConnectionData(QString s1, QString s2, QString s3, QString s4, QString s5) {
    qDebug() << s1 << '\n' << s2 << '\n' << s3 << '\n' << s4 << '\n' << s5 << "\n\n";

    // Задать параметры подключения
    db.setHostName( s1 );
    db.setPort( s2.toInt() );
    db.setUserName( s3 );
    db.setPassword( s4 );
    db.setDatabaseName( s5 );

    // Если открыто, показать окно, инициализировать, выдать сигнал успеха
    if ( db.open() ) {
        this->setEnabled(true);
        this->setHidden(false);

        init();

        emit connection_successful();
    }
    // иначе вывести ошибку и выдать соответствующий сигнал
    else {
        qDebug() << db.lastError().text() << '\n';
        emit connection_failed();
    }
}

// Инициализация
void MainWindow::init() {
    // Подключение query к БД
    query_0   = QSqlQuery(db);
    query_1   = QSqlQuery(db);
    query_2_0 = QSqlQuery(db);
    query_2_1 = QSqlQuery(db);

    // Выражение количества страниц через количество строк, обновление таблиц

    update_table_0();
    update_table_1();
    update_table_2_0();

    qDebug() << "NumPages:" << numPages_0 << numPages_1 << numPages_2_0 << '\n';


}

// обновление таблицы на первой вкладке
void MainWindow::update_table_0() {
    // Получение количества строк
    query_0.exec("SELECT count(*) AS exact_count FROM owners_data;");
    if ( query_0.next() ) {
        numPages_0 = query_0.value(0).toInt();
    }
    qDebug() << query_0.lastError().text();
    // Получение количества страниц
    numPages_0   = 1 + ( (numPages_0   - 1) / pageRows );
    // Обработка для некорректного номера текущей страницы
    if ( currentPage_0 < 1 ) {
        currentPage_0 = 1;
    }
    else if ( currentPage_0 > numPages_0 ) {
        currentPage_0 = numPages_0;
    }
    // вывести номер страницы к общему числу страниц
    ui -> page_0 -> setText( QString::number( currentPage_0 ) + "/" + QString::number( numPages_0 ) );

    query_0.clear();
    // Команда получения данных из таблицы
    query_0.prepare("SELECT * FROM owners_data LIMIT :a0 OFFSET :a1;");
    query_0.bindValue(":a0", pageRows);
    query_0.bindValue(":a1", (currentPage_0 - 1) * pageRows );
    query_0.exec();
    qDebug() << pageRows << (currentPage_0 - 1) * pageRows << query_0.lastError().text() << '\n';
    // Очистка виджета
    ui->tableWidget_0->setRowCount( 0 );
    // Добавление строк из БД в виджет
    while ( query_0.next() ) {
        ui->tableWidget_0->insertRow( ui->tableWidget_0->rowCount() );

        ui->tableWidget_0->setItem( ui->tableWidget_0->rowCount() - 1, 0, new QTableWidgetItem( query_0.value(0).toString() ) );
        ui->tableWidget_0->setItem( ui->tableWidget_0->rowCount() - 1, 1, new QTableWidgetItem( query_0.value(1).toString() ) );
        ui->tableWidget_0->setItem( ui->tableWidget_0->rowCount() - 1, 2, new QTableWidgetItem( query_0.value(2).toString() ) );
        ui->tableWidget_0->setItem( ui->tableWidget_0->rowCount() - 1, 3, new QTableWidgetItem( query_0.value(3).toString() ) );
        ui->tableWidget_0->setItem( ui->tableWidget_0->rowCount() - 1, 4, new QTableWidgetItem( query_0.value(4).toString() ) );
        ui->tableWidget_0->setItem( ui->tableWidget_0->rowCount() - 1, 5, new QTableWidgetItem( query_0.value(5).toString() ) );
        ui->tableWidget_0->setItem( ui->tableWidget_0->rowCount() - 1, 6, new QTableWidgetItem( query_0.value(6).toString() ) );
    }
}
// Аналогично таблица на второй вкладке
void MainWindow::update_table_1() {
    // Кол-во строк
    query_1.exec("SELECT count(*) AS exact_count FROM cars_data;");
    if ( query_1.next() ) {
        numPages_1 = query_1.value(0).toInt();
    }
    qDebug() << query_1.lastError().text();
    // Кол-во страниц
    numPages_1   = 1 + ( (numPages_1   - 1) / pageRows );
    // Обработка номера текущей страницы
    if ( currentPage_1 < 1 ) {
        currentPage_1 = 1;
    }
    else if ( currentPage_1 > numPages_1 ) {
        currentPage_1 = numPages_1;
    }
    // Вывод номера/количества страниц
    ui -> page_1 -> setText( QString::number( currentPage_1 ) + "/" + QString::number( numPages_1 ) );

    query_1.clear();
    // Получение строк таблицы из БД
    query_1.prepare("SELECT * FROM  cars_data LIMIT :a0 OFFSET :a1;");
    query_1.bindValue(":a0", pageRows);
    query_1.bindValue(":a1", (currentPage_1 - 1) * pageRows );
    query_1.exec();
    qDebug() << pageRows << (currentPage_1 - 1) * pageRows << query_1.lastError().text() << '\n';
    // Очистка виджета таблицы
    ui->tableWidget_1->setRowCount( 0 );
    // Внесение строк в виджет таблицы
    while ( query_1.next() ) {
        ui->tableWidget_1->insertRow( ui->tableWidget_1->rowCount() );

        ui->tableWidget_1->setItem( ui->tableWidget_1->rowCount() - 1, 0, new QTableWidgetItem( query_1.value(0).toString() ) );
        ui->tableWidget_1->setItem( ui->tableWidget_1->rowCount() - 1, 1, new QTableWidgetItem( query_1.value(1).toString() ) );
        ui->tableWidget_1->setItem( ui->tableWidget_1->rowCount() - 1, 2, new QTableWidgetItem( query_1.value(2).toString() ) );
        ui->tableWidget_1->setItem( ui->tableWidget_1->rowCount() - 1, 3, new QTableWidgetItem( query_1.value(3).toString() ) );
        ui->tableWidget_1->setItem( ui->tableWidget_1->rowCount() - 1, 4, new QTableWidgetItem( query_1.value(4).toString() ) );
        ui->tableWidget_1->setItem( ui->tableWidget_1->rowCount() - 1, 5, new QTableWidgetItem( query_1.value(5).toString() ) );
        ui->tableWidget_1->setItem( ui->tableWidget_1->rowCount() - 1, 6, new QTableWidgetItem( query_1.value(6).toString() ) );
    }
}
// Аналогично update_table_0
void MainWindow::update_table_2_0() {
    query_2_0.exec("SELECT count(*) AS exact_count FROM owners_data;");
    if ( query_2_0.next() ) {
        numPages_2_0 = query_2_0.value(0).toInt();
    }
    qDebug() << query_2_0.lastError().text();

    numPages_2_0   = 1 + ( (numPages_2_0   - 1) / pageRows );

    if ( currentPage_2_0 < 1 ) {
        currentPage_2_0 = 1;
    }
    else if ( currentPage_2_0 > numPages_2_0 ) {
        currentPage_2_0 = numPages_2_0;
    }

    ui -> page_2_0 -> setText( QString::number( currentPage_2_0 ) + "/" + QString::number( numPages_2_0 ) );

    query_2_0.clear();

    query_2_0.prepare("SELECT * FROM owners_data LIMIT :a0 OFFSET :a1;");
    query_2_0.bindValue(":a0", pageRows);
    query_2_0.bindValue(":a1", (currentPage_2_0 - 1) * pageRows );
    query_2_0.exec();
    qDebug() << pageRows << (currentPage_2_0 - 1) * pageRows << query_2_0.lastError().text() << '\n';

    ui->tableWidget_2_0->setRowCount( 0 );

    while ( query_2_0.next() ) {
        ui->tableWidget_2_0->insertRow( ui->tableWidget_2_0->rowCount() );

        ui->tableWidget_2_0->setItem( ui->tableWidget_2_0->rowCount() - 1, 0, new QTableWidgetItem( query_2_0.value(0).toString() ) );
        ui->tableWidget_2_0->setItem( ui->tableWidget_2_0->rowCount() - 1, 1, new QTableWidgetItem( query_2_0.value(1).toString() ) );
        ui->tableWidget_2_0->setItem( ui->tableWidget_2_0->rowCount() - 1, 2, new QTableWidgetItem( query_2_0.value(2).toString() ) );
        ui->tableWidget_2_0->setItem( ui->tableWidget_2_0->rowCount() - 1, 3, new QTableWidgetItem( query_2_0.value(3).toString() ) );
        ui->tableWidget_2_0->setItem( ui->tableWidget_2_0->rowCount() - 1, 4, new QTableWidgetItem( query_2_0.value(4).toString() ) );
        ui->tableWidget_2_0->setItem( ui->tableWidget_2_0->rowCount() - 1, 5, new QTableWidgetItem( query_2_0.value(5).toString() ) );
        ui->tableWidget_2_0->setItem( ui->tableWidget_2_0->rowCount() - 1, 6, new QTableWidgetItem( query_2_0.value(6).toString() ) );
    }
}

// Получение данных о машинах по ID владельца
void MainWindow::update_table_2_1( int ID ) {

    query_2_1.prepare( "SELECT * FROM cars_data WHERE owner_id = :id;" );
    query_2_1.bindValue(":id", ID);
    query_2_1.exec();

    qDebug() << query_2_1.lastError().text() << '\n';

    ui->tableWidget_2_1->setRowCount( 0 );
    while ( query_2_1.next() ) {
        ui->tableWidget_2_1->insertRow( ui->tableWidget_2_1->rowCount() );

        ui->tableWidget_2_1->setItem( ui->tableWidget_2_1->rowCount() - 1, 0, new QTableWidgetItem( query_2_1.value(0).toString() ) );
        ui->tableWidget_2_1->setItem( ui->tableWidget_2_1->rowCount() - 1, 1, new QTableWidgetItem( query_2_1.value(1).toString() ) );
        ui->tableWidget_2_1->setItem( ui->tableWidget_2_1->rowCount() - 1, 2, new QTableWidgetItem( query_2_1.value(2).toString() ) );
        ui->tableWidget_2_1->setItem( ui->tableWidget_2_1->rowCount() - 1, 3, new QTableWidgetItem( query_2_1.value(3).toString() ) );
        ui->tableWidget_2_1->setItem( ui->tableWidget_2_1->rowCount() - 1, 4, new QTableWidgetItem( query_2_1.value(4).toString() ) );
        ui->tableWidget_2_1->setItem( ui->tableWidget_2_1->rowCount() - 1, 5, new QTableWidgetItem( query_2_1.value(5).toString() ) );
        ui->tableWidget_2_1->setItem( ui->tableWidget_2_1->rowCount() - 1, 6, new QTableWidgetItem( query_2_1.value(6).toString() ) );
    }
}
// Предыдущая страница
void MainWindow::on_pushButton_0_prev_clicked()
{
    currentPage_0--;
    update_table_0();
}
// Следующая
void MainWindow::on_pushButton_0_next_clicked()
{
    currentPage_0++;
    update_table_0();
}
//Добавление пользователя
void MainWindow::on_pushButton_0_add_clicked()
{
    QList<QString> args;
    QString error_message;

    QRegularExpression re;

    // Фамилия, имя, отчество
    re.setPattern( "^[\\ А-ЯЁа-яё'\\-]+$" );
    if ( re.match( ui->lineEdit_0_0->text() ).hasMatch() ) {
        args.append( ui->lineEdit_0_0->text() ); // Добавить, если проверка пройдена
    }
    else {
        error_message += "Фамилия\n";        // Иначе добавить в ошибки
    }

    if ( re.match( ui->lineEdit_0_1->text() ).hasMatch() ) {
        args.append( ui->lineEdit_0_1->text() );  // Добавление
    }
    else {
        error_message += "Имя\n";               // Ошибка
    }

    if ( re.match( ui->lineEdit_0_2->text() ).hasMatch() ) {
        args.append( ui->lineEdit_0_2->text() );  // Добавление
    }
    else {
        error_message += "Отчество\n";          // Ошибка
    }

    // Серия паспорта
    re.setPattern( "^\\d\\d\\d\\d$" );
    if ( re.match( ui->spinBox_0_0->text() ).hasMatch() ) {
        args.append( ui->spinBox_0_0->text() );     // Добавление
    }
    else {
        error_message += "Серия паспорта\n";    // Ошибка
    }
    // Номер паспорта
    re.setPattern( "^\\d\\d\\d\\d\\d\\d$" );
    if ( re.match( ui->spinBox_0_1->text() ).hasMatch() ) {
        args.append( ui->spinBox_0_1->text() );   // Добавление
    }
    else {
        error_message += "Номер паспорта\n";    // Ошибка
    }
    // Номер телефона
    re.setPattern( "^8\\d\\d\\d\\d\\d\\d\\d\\d\\d\\d$" );
    QString phone = "8" + ui->lineEdit_0_3_0->text() + ui->lineEdit_0_3_1->text() + ui->lineEdit_0_3_2->text() + ui->lineEdit_0_3_3->text();
    if ( re.match( phone ).hasMatch() ) {
        args.append( phone );  // Добавление
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
            query_0.prepare( "INSERT INTO owners_data(last_name, first_name, patronymic, pass_series, pass_number, phone_number) VALUES (:a0, :a1, :a2, :a3, :a4, :a5);" );
            query_0.bindValue(":a0", args[0]);
            query_0.bindValue(":a1", args[1]);
            query_0.bindValue(":a2", args[2]);
            query_0.bindValue(":a3", args[3]);
            query_0.bindValue(":a4", args[4]);
            query_0.bindValue(":a5", args[5]);
            query_0.exec();

            qDebug() << query_0.lastError().text() << '\n';

            if ( query_0.lastError().text() == "" ) {
                QMessageBox::warning( 0, "Успешно!", "Пользователь добавлен!");
            }
            else {
                QMessageBox::warning( 0, "Ошибка!", query_0.lastError().text() );
            }
        }
        // В случае ошибки, вывести окно с текстом ошибки
        catch (QString s) {
            QMessageBox::warning( 0, "Ошибка БД", s);
        }
        // Обновить таблицу
       update_table_0();
    }
}
// Удаление пользователя
void MainWindow::on_pushButton_0_delete_clicked()
{
    // Получить ID пользователя
    int id = ui -> spinBox_0->value();

    // Определить, есть ли в БД такие
    query_0.prepare( "SELECT * FROM owners_data WHERE owner_id = :a0;" );
    query_0.bindValue(":a0", id);
    query_0.exec();

    // Если есть, вывести сообщение и удалить пользователя
    if ( query_0.next() ) {

        qDebug() << "Удаление: пользователь найден\n" << query_0.lastError().text() << '\n';

        QSqlQuery q(db);

        q.prepare( "DELETE FROM owners_data WHERE owner_id = :id;" );
        q.bindValue(":id", id);
        q.exec();

        // Вывести ошибку или сообщение об успехе
        if ( q.lastError().text() == "" ) {
            QMessageBox::warning( 0, "Успешно!", "Пользователь удален!");
            update_table_0();
        }
        else {
            QMessageBox::warning( 0, "Ошибка!", q.lastError().text() );
        }
    }
    // иначе сообщить, что пользователя нет
    else {
        QMessageBox::warning( 0, "Ошибка!", "Пользователь не найден!");
    }
}

// Предыдущая страница
void MainWindow::on_pushButton_1_prev_clicked()
{
    currentPage_1--;
    update_table_1();
}
// Следующая
void MainWindow::on_pushButton_1_next_clicked()
{
    currentPage_1++;
    update_table_1();
}

// Добавление авто
void MainWindow::on_pushButton_1_add_clicked()
{
    QList<QString> args;
    QString error_message;

    QRegularExpression re;

    // Номер, марка, цвет
    re.setPattern( "^[АВЕКМНОРСТУХ]\\d\\d\\d[АВЕКМНОРСТУХ]{2}\\d\\d\\d?RUS$" );
    if ( re.match( ui->lineEdit_1_0->text() ).hasMatch() ) {
        args.append( ui->lineEdit_1_0->text() );
    }
    else {
        error_message += "Номер\n";
    }
    // Марка
    if ( !ui->lineEdit_1_1->text().isEmpty() ) {
        args.append( ui->lineEdit_1_1->text() );
    }
    else {
        error_message += "Марка\n";
    }
    // Цвет
    if ( !ui->lineEdit_1_2->text().isEmpty() ) {
        args.append( ui->lineEdit_1_2->text() );
    }
    else {
        error_message += "Цвет\n";
    }

    // Категория задана в UI и соответствует ENUM в БД
    args.append( ui->comboBox_1_0->currentText() );

    // VIN
    re.setPattern( "^[A-HJ-NPR-Z\\d]{17}$" );
    if ( re.match( ui->lineEdit_1_3->text() ).hasMatch() ) {
        args.append( ui->lineEdit_1_3->text() );
    }
    else {
        error_message += "VIN\n";
    }

    args.append( ui->spinBox->text() );


    // Если строка с ошибками не пуста, вывести окно с неправильно введенными полями
    if ( !error_message.isEmpty() ) {
        QMessageBox::warning( 0, "Ошибка в полях:", error_message);
        return;
    }
    // Иначе (с обработкой ошибок) добавить элемент
    else {
        try {
            query_1.prepare( "INSERT INTO cars_data(car_number, car_mark, car_color, car_category, car_vin, owner_id) VALUES (:a0, :a1, :a2, :a3, :a4, :a5);" );
            query_1.bindValue(":a0", args[0]);
            query_1.bindValue(":a1", args[1]);
            query_1.bindValue(":a2", args[2]);
            query_1.bindValue(":a3", args[3]);
            query_1.bindValue(":a4", args[4]);
            query_1.bindValue(":a5", args[5]);
            query_1.exec();

            qDebug() << query_1.lastError().text() << '\n';

            if ( query_1.lastError().text() == "" ) {
                QMessageBox::warning( 0, "Успешно!", "Авто добавлено!");
            }
            else {
                QMessageBox::warning( 0, "Ошибка!", query_1.lastError().text() );
            }
        }
        // В случае ошибки, вывести окно с текстом ошибки
        catch (QString s) {
            QMessageBox::warning( 0, "Ошибка БД", s);
        }
        // Обновить таблицу
       update_table_1();
    }
}

// Удаление авто
void MainWindow::on_pushButton_1_delete_clicked()
{
    // Получить ID, проверить, есть ли такое
    int id = ui -> spinBox_1->value();

    query_1.prepare( "SELECT * FROM cars_data WHERE car_id = :a0;" );
    query_1.bindValue(":a0", id);
    query_1.exec();

    // Если есть, удалить и сообщить об ошибке/успехе
    if ( query_1.next() ) {

        qDebug() << "Удаление: авто найдено\n" << query_1.lastError().text() << '\n';

        QSqlQuery q(db);

        q.prepare( "DELETE FROM cars_data WHERE car_id = :id;" );
        q.bindValue(":id", id);
        q.exec();

        if ( q.lastError().text() == "" ) {
            QMessageBox::warning( 0, "Успешно!", "Авто удалено!");
            update_table_1();
        }
        else {
            QMessageBox::warning( 0, "Ошибка!", q.lastError().text() );
        }
    }
    // Иначе сообщить, что авто нет
    else {
        QMessageBox::warning( 0, "Ошибка!", "Авто не найдено!");
    }
}

// Предыдущая страница
void MainWindow::on_pushButton_2_0_prev_clicked()
{
    currentPage_2_0--;
    update_table_2_0();
}
// Следующая
void MainWindow::on_pushButton_2_0_next_clicked()
{
    currentPage_2_0++;
    update_table_2_0();
}
//Действие при двойном нажатии на ячейку общей таблицы - получение из строки ID владельца и поиск соответствующих авто
void MainWindow::on_tableWidget_2_0_cellDoubleClicked(int row, int column)
{
    update_table_2_1( ui->tableWidget_2_0->item( row, 0 )->text().toInt() );
}

