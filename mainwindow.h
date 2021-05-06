#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<opencv2/opencv.hpp>
#include<QDebug>
#include <QThread>
using namespace cv;
class Mythread :public QThread{
    Q_OBJECT
public:
    Mythread(){}
    ~Mythread(){}
    void run();
    void photoes();
signals:
    void send_img(QPixmap map);
private:
    Mat img;
};



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString car_plate_recognize(QString filePath);

private slots:
    void  recv_img(QPixmap img);
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    Mythread *thread;

};
#endif // MAINWINDOW_H
