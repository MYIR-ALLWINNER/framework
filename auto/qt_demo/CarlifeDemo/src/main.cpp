/*!
 * @file main.cpp
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#include "carlifewindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QFont>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //for chinese support
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
    translator1.load("/font/qt_zh_CN.qm");
    a.installTranslator(&translator1);
    CarlifeWindow w;
    w.show();

    return a.exec();
}
