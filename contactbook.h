#ifndef CONTACTBOOK_H
#define CONTACTBOOK_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class ContactBook;
}
QT_END_NAMESPACE

class ContactBook : public QWidget
{
    Q_OBJECT

public:
    ContactBook(QWidget *parent = nullptr);
    ~ContactBook();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::ContactBook *ui;
};
#endif // CONTACTBOOK_H
