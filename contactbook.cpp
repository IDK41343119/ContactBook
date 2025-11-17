#include "contactbook.h"
#include "ui_contactbook.h"

#include<QFile>
#include<QDebug>
#include<QFileDialog>


QString mFilename = "C:/Users/user/Desktop/EX/test/test.xlsx";

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
    mFilename=QFileDialog::getSaveFileName(this,"匯出存檔",".");
    int rc,cc;
    rc=ui->tableWidget->rowCount();
    cc=ui->tableWidget->columnCount();

    for(int i = 0;i<rc;i++){
        for (int j = 0 ;j<cc;j++) {
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


void ContactBook::on_pushButton_3_clicked()
{
    // 匯入：不使用 QTextStream、QMessageBox、QRegularExpression
    QString loadFile = QFileDialog::getOpenFileName(this, tr("匯入檔案"), ".", tr("Text Files (*.txt *.csv);;All Files (*)"));
    if (loadFile.isEmpty()) {
        return; // 使用者取消
    }

    QFile file(loadFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file for read:" << loadFile;
        return;
    }

    // 讀取整個檔案（避免使用 QTextStream）
    QByteArray data = file.readAll();
    // 視目標環境使用適當的編碼轉換；這裡使用 local8Bit 以兼容 Windows 預設編碼：
    QString content = QString::fromLocal8Bit(data);
    file.close();

    // 更新目前檔名
    mFilename = loadFile;

    // 清除現有資料
    ui->tableWidget->setRowCount(0);
    const int cc = ui->tableWidget->columnCount();

    // 逐行處理
    QStringList lines = content.split('\n');
    for (QString rawLine : lines) {
        QString line = rawLine.trimmed();
        if (line.isEmpty()) continue;

        // simplified() 會去除前後空白並把任意連續空白壓縮成單一空格
        QString normalized = line.simplified();
        // 以單一空格分割欄位（不使用 QRegularExpression）
        QStringList parts = normalized.split(' ', Qt::SkipEmptyParts);

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        if (parts.size() >= cc) {
            for (int j = 0; j < cc; ++j) {
                QString text;
                if (j == cc - 1) {
                    // 剩下的合併到最後一欄
                    text = parts.mid(j).join(" ");
                } else {
                    text = parts.value(j);
                }
                ui->tableWidget->setItem(row, j, new QTableWidgetItem(text));
            }
        } else {
            for (int j = 0; j < cc; ++j) {
                QString text = (j < parts.size()) ? parts.at(j) : QString();
                ui->tableWidget->setItem(row, j, new QTableWidgetItem(text));
            }
        }
    }
}

