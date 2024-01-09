#include "main_desktop.h"
#include <QApplication>
#include <QTextCodec>
#include <QFont>
#include <QTranslator>
#include <QPixmap>
#include <QSplashScreen>
int main(int argc, char *argv[])
{
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

    main_desktop w;
    w.show();
    if(pix.load(":/bootlogo.jpg"))
    {
        splash.finish(&w);
    }
    w.videoshow();

    return a.exec();
}
