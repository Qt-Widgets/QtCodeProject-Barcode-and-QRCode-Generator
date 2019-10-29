#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QCodePrinter;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_barcodeButton_clicked();
    void on_qrcodeButton_clicked();

private:
    Ui::MainWindow *ui;
    QCodePrinter *mCodePrinter;
};

#endif // MAINWINDOW_H
