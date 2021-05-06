#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QImage>
#include <easypr.h>
#include <vector>
#include <QTextCodec>

using  namespace easypr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800,480);
    thread = new Mythread;
    connect(thread,&Mythread::send_img,this,&MainWindow::recv_img);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::car_plate_recognize(QString filePath)
{
    std::string file = filePath.toUtf8().data();
    Mat src = imread(file);

    CPlateRecognize pr;	//车牌字符识别
    pr.setLifemode(true);//设置提取车牌参数（高斯滤波，等）
    pr.setDebug(false);//关闭调试
    pr.setMaxPlates(1);//识别一个车牌
    //设置检测模式， 演示， sobel算子， cmser算子
    pr.setDetectType(PR_DETECT_COLOR | PR_DETECT_SOBEL|PR_DETECT_CMSER);

    //存储车牌的容器
    vector<CPlate> plateVec;

    //从原图中提取可能车牌
    int result = pr.plateRecognize(src, plateVec);
    if (result == 0)
    {
        size_t num = plateVec.size();
        for (size_t j = 0; j < num; j++)
        {
            //输出所有检测的车牌号
            cout << plateVec[j].getPlateStr() << endl;
        }
    }

    if (result != 0) cout << "result:" << result << endl;

    //获取第一张车牌号并且转字符串
    String tmp = plateVec[0].getPlateStr();
    //把opencv里面的字符串转Qt中的字符串
//    QString car = QString::fromLocal8Bit(tmp.c_str());
    QString car = tmp.c_str();
    qDebug()<<car;

    //获取第一种车牌的图片矩阵
    Mat carPlateMat = plateVec[0].getPlateMat();
    cvtColor(carPlateMat,carPlateMat,CV_BGR2RGB);
    //把图片矩阵转QImage用来在界面上显示
    QImage image =QImage(carPlateMat.data,carPlateMat.cols,carPlateMat.rows,QImage::Format_RGB888);

    ui->label_2->setPixmap(QPixmap::fromImage(image));

//    QImage image = mat_to_qimage(carPlateMat);
//    emit sendCarImage(image);//把图片用信号发送
    return car;
}

void MainWindow::recv_img(QPixmap img)
{
    ui->label->setPixmap(img);//显示
}

//
void Mythread::run()
{
//    Mat img=imread("D:\\qt_project\\CarPlateRecognize\\test\\A5J512.jpg");
//    //显示在label img需要转换格式，BGR转 RGB
//    cvtColor(img,img,CV_BGR2RGB);
//    QImage image=QImage(img.data,img.cols,img.rows,QImage::Format_RGB888);//将cv的mat类转 qimage类型

//    emit send_img(QPixmap::fromImage(image));//发送信号
    //摄像头
    VideoCapture vc(7);//7表示用第一个摄像头

    if(!vc.isOpened())
    {
        QMessageBox::warning(NULL, "warning","vc.isOpened");
        return;
    }
    while(1)
    {
        vc.read(img);
        cvtColor(img,img,CV_BGR2RGB);
        QImage image=QImage(img.data,img.cols,img.rows,QImage::Format_RGB888);//将cv的mat类转 qimage类型
        emit send_img(QPixmap::fromImage(image));
    }
}
// 拍照
void Mythread::photoes()
{
    if(img.empty())
    {
        QMessageBox::warning(NULL,"warning","camera no open");
        return;
    }
    cvtColor(img,img,CV_BGR2RGB);//颜色转换
    imwrite("1.bmp",img);//保存图片
    qDebug()<<"save ok";

}

void MainWindow::on_pushButton_clicked()
{
    if(!thread->isRunning())//判断是否在运行
    {
        thread->start();//运行线程

    }
    else
        QMessageBox::warning(NULL,"warning","is running");

}

void MainWindow::on_pushButton_2_clicked()//拍照
{
    thread->photoes();
    QThread::msleep(5);
    QString str;
    str = car_plate_recognize("./1.bmp");
//    qDebug()<<str;
//    QTextCodec* gbk = QTextCodec::codecForName("GBK");

//    ui->label_3->setText("id:"+ gbk->toUnicode(str.toStdString().c_str()));
    ui->label_3->setText("id"+str);
}

void MainWindow::on_pushButton_3_clicked()//close
{
    thread->terminate();
    ui->label->clear();
    ui->label_2->clear();
    ui->label_3->clear();

}
