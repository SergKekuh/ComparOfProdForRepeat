#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QVector>
#include "price_db.h"
#include <QList>
//#include <QLinkedList>
#include <QByteArray>
#include "QStandardItemModel"
#include "QStandardItem"
#include <memory>


#include "string.h"

#include "libxl.h"
using namespace libxl;
using namespace std;

QList<price_db*> price_profile;
QList<price_db*> price_round;
QStringList StringsProfile;
QStringList StringsRound;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    StringsProfile = QStringList() << "Откуда"
                                 << "Стандарт"
                                 << "Ширина"
                                 << "Высота"
                                 << "Толщина"
                                 << "Сталь"
                                 << "Тоннаж"
                                 << "Оптовая цена"
                                 << "Розничная цена";

    StringsRound = QStringList() << "Откуда"
                                 << "Стандарт"
                                 << "Ширина"
                                 << "Толщина"
                                 << "Сталь"
                                 << "Тоннаж"
                                 << "Оптовая цена"
                                 << "Розничная цена";
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_OpenProfileFile_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,tr("utsk-price-profile-pipe"), QDir::homePath(), tr("Files Excel(*.xls *.xlsx)"));

    //QMessageBox::information(this, "..", file_name);    

    QString str = file_name;
    QByteArray ba = str.toLocal8Bit();
    const char* c_str = ba.data();

    const char* name_file_profile = "utsk-price-profile-pipe.xlsx";
    //-----"/home/sergey/utsk-price-profile-pipe.xlsx"

       Book* book = xlCreateXMLBook();

       if(book->load(c_str))
       {
          Sheet* sheet = book->getSheet(0);
          if(sheet)
          {
             //price_profile = new QList<price_db>[sheet->lastRow()];

             for(int row = 9; row < sheet->lastRow(); ++row)
             {
                    //QString *st0 = new QString(sheet->readStr(row, 0));
                    QString st0 = sheet->readStr(row, 0);
                    QString st1 = sheet->readStr(row, 1);
                    QString st2 = sheet->readStr(row, 2);
                    QString st3 = sheet->readStr(row, 3);
                    QString st4 = sheet->readStr(row, 4);
                    QString st5 = sheet->readStr(row, 5);
                    QString st6 = sheet->readStr(row, 6);
                    QString st7 = sheet->readStr(row, 7);
                    QString st8 = sheet->readStr(row, 8);
                    price_profile.append(new price_db(st0, st1, st2, st3, st4, st5, st6, st7, st8));
             }
          }
          else
          {
                 QMessageBox::warning(this, "Error file selection", "File is empty");
          }

       }
       book->release();


       ui->tableWidgetProfile->setColumnCount(9); // Указываем число колонок
       ui->tableWidgetProfile->setShowGrid(true); // Включаем сетку
       // Разрешаем выделение только одного элемента
       ui->tableWidgetProfile->setSelectionMode(QAbstractItemView::SingleSelection);
       // Разрешаем выделение построчно
       ui->tableWidgetProfile->setSelectionBehavior(QAbstractItemView::SelectRows);
       // Устанавливаем заголовки колонок
       ui->tableWidgetProfile->setHorizontalHeaderLabels(StringsProfile);
       // Растягиваем последнюю колонку на всё доступное пространство
       ui->tableWidgetProfile->horizontalHeader()->setStretchLastSection(true);
       // Скрываем колонку под номером 0
       //ui->tableWidgetProfile->hideColumn(0);
       ui->tableWidgetProfile->setEditTriggers(QTableWidget::NoEditTriggers);

       // Выполняем заполнение QTableWidget записями с помощью цикла


    int i = 0;
    foreach( price_db *it, price_profile ){
    //for (QList<price_db>::iterator it = price_profile.begin(); it != price_profile.end(); ++it){

           ui->tableWidgetProfile->insertRow(i);


           // Далее забираем все данные из результата запроса и устанавливаем в остальные поля
           ui->tableWidgetProfile->setItem(i,0, new QTableWidgetItem(it->FromWhere));
           ui->tableWidgetProfile->setItem(i,1, new QTableWidgetItem(it->Standart));
           ui->tableWidgetProfile->setItem(i,2, new QTableWidgetItem(it->WidthProfile));
           ui->tableWidgetProfile->setItem(i,3, new QTableWidgetItem(it->HightProfile));
           ui->tableWidgetProfile->setItem(i,4, new QTableWidgetItem(it->WallThickness));
           ui->tableWidgetProfile->setItem(i,5, new QTableWidgetItem(it->Steel));
           ui->tableWidgetProfile->setItem(i,6, new QTableWidgetItem(it->Tonnag));
           ui->tableWidgetProfile->setItem(i,7, new QTableWidgetItem(it->WholesalePrice));
           ui->tableWidgetProfile->setItem(i,8, new QTableWidgetItem(it->SellingPrice));

           i++;
   }
   // Ресайзим колонки по содержимому
   ui->tableWidgetProfile->resizeColumnsToContents();

   foreach( price_db *it, price_profile ){
    delete it;
   }

}


void MainWindow::on_OpenRoundFile_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,tr("utsk-price-round-pipe"), QDir::homePath(), tr("Files Excel(*.xls *.xlsx)"));

    //QMessageBox::information(this, "..", file_name);
    QString str = file_name;
    QByteArray ba = str.toLocal8Bit();
    const char* c_str = ba.data();

    const char* name_file_profile = "utsk-price-round-pipe.xlsx";



    //-----"/home/sergey/utsk-price-round-pipe.xlsx"

       Book* book = xlCreateXMLBook();

       if(book->load(c_str))
       {
          Sheet* sheet = book->getSheet(0);
          if(sheet)
          {
             for(int row = 9; row < sheet->lastRow(); row++)
             {
                 QString st0 = sheet->readStr(row, 0);
                 QString st1 = sheet->readStr(row, 1);
                 QString st2 = sheet->readStr(row, 2);
                 QString st3 = sheet->readStr(row, 3);
                 QString st4 = sheet->readStr(row, 4);
                 QString st5 = sheet->readStr(row, 5);
                 QString st6 = sheet->readStr(row, 6);
                 QString st7 = sheet->readStr(row, 7);
                 QString st8 = sheet->readStr(row, 8);
                    price_round.append(new price_db(st0, st1, st2, st3, st4, st5, st6, st7, st8));
             }
          }
          else
          {
                 QMessageBox::warning(this, "Error file selection", "File is empty");
          }
       }

       book->release();

       ui->tableWidgetRound->setColumnCount(9); // Указываем число колонок
       ui->tableWidgetRound->setShowGrid(true); // Включаем сетку
       // Разрешаем выделение только одного элемента
       ui->tableWidgetRound->setSelectionMode(QAbstractItemView::SingleSelection);
       // Разрешаем выделение построчно
       ui->tableWidgetRound->setSelectionBehavior(QAbstractItemView::SelectRows);
       // Устанавливаем заголовки колонок
       ui->tableWidgetRound->setHorizontalHeaderLabels(StringsProfile);
       // Растягиваем последнюю колонку на всё доступное пространство
       ui->tableWidgetRound->horizontalHeader()->setStretchLastSection(true);
       // Скрываем колонку под номером 0
       //ui->tableWidgetProfile->hideColumn(0);
       ui->tableWidgetRound->setEditTriggers(QTableWidget::NoEditTriggers);

       // Выполняем заполнение QTableWidget записями с помощью цикла

    int i = 0;
    foreach( price_db *it, price_round ){
    //for (QList<price_db>::iterator it = price_profile.begin(); it != price_profile.end(); ++it){

           ui->tableWidgetRound->insertRow(i);

           // Далее забираем все данные из результата запроса и устанавливаем в остальные поля
           ui->tableWidgetRound->setItem(i,0, new QTableWidgetItem(it->FromWhere));
           ui->tableWidgetRound->setItem(i,1, new QTableWidgetItem(it->Standart));
           ui->tableWidgetRound->setItem(i,2, new QTableWidgetItem(it->WidthProfile));
           ui->tableWidgetRound->setItem(i,3, new QTableWidgetItem(it->HightProfile));
           ui->tableWidgetRound->setItem(i,4, new QTableWidgetItem(it->WallThickness));
           ui->tableWidgetRound->setItem(i,5, new QTableWidgetItem(it->Steel));
           ui->tableWidgetRound->setItem(i,6, new QTableWidgetItem(it->Tonnag));
           ui->tableWidgetRound->setItem(i,7, new QTableWidgetItem(it->WholesalePrice));
           ui->tableWidgetRound->setItem(i,8, new QTableWidgetItem(it->SellingPrice));

           i++;
   }
   // Ресайзим колонки по содержимому
   ui->tableWidgetRound->resizeColumnsToContents();
   foreach( price_db *it, price_round ){
        delete it;
   }

}


void MainWindow::on_pushReconciliationProfile_clicked()
{

}


void MainWindow::on_pushReconciliationRound_clicked()
{

}

