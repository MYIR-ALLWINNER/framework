#include "main_desktop.h"
#include <QApplication>
#include <QTextCodec>
#include <QFont>
#include <QTranslator>
#include <QPixmap>
#include <QSplashScreen>
#include <QTime>
#include <QDebug>

int main(int argc, char *argv[])
{
	QTime time;
	time.start();
    QApplication a(argc, argv);
    //中文支持
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    a.setFont(QFont("WenQuanYi Zen Hei", 12));
    qApp->setFont(QFont("WenQuanYi Zen Hei", 12));

    QTranslator translator(0);
    translator.load("filemanager_zh",".");
    a.installTranslator(&translator);

    QTranslator qttranslator(0);
    qttranslator.load("qt_zh_CN",".");
    a.installTranslator(&qttranslator);

    QTranslator fileinfotranslator(0);
    fileinfotranslator.load("qfile_zh",".");
    a.installTranslator(&fileinfotranslator);

    QTranslator translator1(0);
    translator1.load("/icon/qt_zh_CN.qm");
    a.installTranslator(&translator1);

	qDebug()<<"===start QTime.start & QTime.elspsed ="<<time.elapsed()<<"ms";
#if 0
    QPixmap pix;
    QSplashScreen splash;
    if(pix.load(":/bootlogo.jpg"))
    {
        splash.setPixmap(pix);
        splash.show();

    }else
    {
        qDebug()<<"read image error";
    }
#endif

	time.start();
    main_desktop w;
    w.show();
	qDebug()<<"===main_desktop QTime.start & QTime.elspsed ="<<time.elapsed()<<"ms";

#if 0
    if(pix.load(":/bootlogo.jpg"))
    {
        splash.finish(&w);
    }
#endif

	time.start();
    w.videoshow();
	qDebug()<<"===videoshow QTime.start & QTime.elspsed ="<<time.elapsed()<<"ms";

    return a.exec();
}
