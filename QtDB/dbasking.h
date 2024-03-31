#ifndef DBASKING_H
#define DBASKING_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class DBAsking;
}

class DBAsking : public QWidget
{
    Q_OBJECT

public:
    explicit DBAsking(QWidget *parent = nullptr);
    ~DBAsking();

private slots:
    void on_pushButton_clicked();

public slots:
    void connection_successful();
    void connection_failed();

signals:
    void buttonPressed(QString s1, QString s2, QString s3, QString s4, QString s5);

private:
    Ui::DBAsking *ui;
};

#endif // DBASKING_H
