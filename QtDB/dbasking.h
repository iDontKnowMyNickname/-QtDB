#ifndef DBASKING_H
#define DBASKING_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class DBAsking;
}

// Класс, получающий данные для пожключения к БД
class DBAsking : public QWidget
{
    Q_OBJECT

public:
    explicit DBAsking(QWidget *parent = nullptr);
    ~DBAsking();

private slots:
    // Нажатие кнопки "присоединиться"
    void on_pushButton_clicked();

public slots:
    // При подключении
    void connection_successful();
    // При неподключении
    void connection_failed();

signals:
    // Передача данных для подключения
    void buttonPressed(QString s1, QString s2, QString s3, QString s4, QString s5);

private:
    Ui::DBAsking *ui;
};

#endif // DBASKING_H
