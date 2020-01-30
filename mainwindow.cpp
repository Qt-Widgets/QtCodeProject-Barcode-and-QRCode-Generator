#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcodeprinter.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mCodePrinter = new QCodePrinter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_barcodeButton_clicked()
{
    QSize size = ui->barcodeLabel->size() - QSize(2,2);
    QImage barcode = mCodePrinter->printBarcode("Hello, world", size, Qt::black);
    ui->barcodeLabel->setPixmap(QPixmap::fromImage(barcode));
}

void MainWindow::on_qrcodeButton_clicked()
{
    QSize size = ui->barcodeLabel->size() - QSize(2,2);
    QImage qrcode = mCodePrinter->printQrcode("Hello, world", size, Qt::black);
    ui->qrcodeLabel->setPixmap(QPixmap::fromImage(qrcode));
}
