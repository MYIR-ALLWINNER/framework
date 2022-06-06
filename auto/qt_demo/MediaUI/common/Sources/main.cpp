/*!
 * @file main.cpp
 * Copyright (c) 2018
 * @brief des
 * detailed des
 *
 * @date 2018
 * @author lee
 */
#include "common/Header/mediahome.h"

#include <QApplication>
#include <QTextCodec>
#include <QFont>
#include <QTranslator>
#include <QDebug>
#include <QList>
#include <QListWidgetItem>
#include <QMetaType>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    a.setFont(QFont("WenQuanYi Zen Hei", 8));
    qApp->setFont(QFont("WenQuanYi Zen Hei", 8));

    //call format:QTranslator::load(filename,directory, delim, suffix )
    QTranslator translator(0);
    bool ret = translator.load("filemanager_zh",":/fonts/",".","qm");
    a.installTranslator(&translator);
    qDebug()<<"load filemanager_zh ok;";

    QTranslator qttranslator(0);
    ret = qttranslator.load("qt_zh_CN",":/fonts/",".","qm");
    a.installTranslator(&qttranslator);
    qDebug()<<"load qt_zh_CN ok;";

    QTranslator fileinfotranslator(0);
    ret = fileinfotranslator.load("qfile_zh",":/fonts/",".","qm");
    a.installTranslator(&fileinfotranslator);
    qDebug()<<"load qfile_zh ok;";

    qRegisterMetaType<QList<QListWidgetItem*> >("QList<QListWidgetItem*>");

    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));

    MediaHome w;
    w.show();

    return a.exec();
}
