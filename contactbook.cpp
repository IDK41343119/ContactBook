#include "contactbook.h"
#include "ui_contactbook.h"

#include<QFile>
#include<QDebug>



QString mFilename = "C:/Users/user/Desktop/EX/test/test.txt";

void Write(QString Filename,QString str)
{
    QFile mFile(Filename);
    if(!mFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug()<<"could not open file for write";
        return;
    }

    QTextStream out(&mFile);
    out<<str;
    mFile.flush();
    mFile.close();

}
ContactBook::ContactBook(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ContactBook)
{
    ui->setupUi(this);

    QStringList ColTotle;

    ui->tableWidget->setColumnCount(4);
    ColTotle<<QStringLiteral("學號")<<QStringLiteral("班級")<<QStringLiteral("姓名")<<QStringLiteral("電話");
    ui->tableWidget->setHorizontalHeaderLabels(ColTotle);
}

ContactBook::~ContactBook()
{
    delete ui;
}

void ContactBook::on_pushButton_2_clicked()
{
    QTableWidgetItem *inputRow1,*inputRow2,*inputRow3,*inputRow4;

    inputRow1 = new QTableWidgetItem(QString(ui->lineEdit->text()));
    inputRow2 = new QTableWidgetItem(QString(ui->lineEdit_2->text()));
    inputRow3 = new QTableWidgetItem(QString(ui->lineEdit_3->text()));
    inputRow4 = new QTableWidgetItem(QString(ui->lineEdit_4->text()));

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,inputRow1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,inputRow2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,inputRow3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,inputRow4);
}


void ContactBook::on_pushButton_clicked()
{
    QString saveFile="";

    for(int i = 0;i<ui->tableWidget->rowCount();i++){
        for (int j = 0 ;j<ui->tableWidget->columnCount();j++) {
            saveFile+=ui->tableWidget->item(i,j) ->text()+" ";
        }
        saveFile+="\n";
    }
    Write (mFilename, saveFile);
}


void ContactBook::on_pushButton_4_clicked()
{
    QString saveFile="";

    for(int i = 0;i<ui->tableWidget->rowCount();i++){
        for (int j = 0 ;j<ui->tableWidget->columnCount();j++) {
            saveFile+=ui->tableWidget->item(i,j) ->text()+" ";
        }
        saveFile+="\n";
    }
    Write (mFilename, saveFile);
    close();
}

