#include "dbasking.h"
#include "ui_dbasking.h"

DBAsking::DBAsking(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DBAsking)
{
    ui->setupUi(this);
}

DBAsking::~DBAsking()
{
    delete ui;
}

void DBAsking::on_pushButton_clicked()
{
    emit buttonPressed( ui->lineEdit_1->text(),
                        ui->lineEdit_2->text(),
                        ui->lineEdit_3->text(),
                        ui->lineEdit_4->text(),
                        ui->lineEdit_5->text() );
}

void DBAsking::connection_successful() {
    QMessageBox msgBox;
    msgBox.setText("База данных успешно подключена!");
    msgBox.setWindowTitle("Успешно!");
    msgBox.exec();
    this->~DBAsking();
}

void DBAsking::connection_failed() {
    QMessageBox msgBox;
    msgBox.setText("Не удалось подключить базу данных!\nПопробуйте ещё раз");
    msgBox.setWindowTitle("Ошибка!");
    msgBox.exec();
}
