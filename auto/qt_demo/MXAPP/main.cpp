#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QFont>
#include <QTimer>
#include <QDateTime>
#include "qmlplot.h"
#include "common.h"
#include "myfunction.h"
#include "translator.h"
#include "mvideooutput.h"
#include "qmlprocess.h"
#include "ChargeManage.h"
#include "Charge104.h"
#include "ClearCache.h"

using namespace std;
using namespace MQP;

void iconFontInit()
{
//
    int fontId_digital = QFontDatabase::addApplicationFont(":/fonts/DIGITAL/DS-DIGIB.TTF");
    int fontId_fws = QFontDatabase::addApplicationFont(":/fonts/fontawesome-webfont.ttf");
    QString fontName_fws = QFontDatabase::applicationFontFamilies(fontId_fws).at(0);
    QFont iconFont_fws;
    iconFont_fws.setFamily(fontName_fws);
    QApplication::setFont(iconFont_fws);
    iconFont_fws.setPixelSize(20);
}

int main(int argc, char *argv[])
{

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication app(argc, argv);


    app.setOrganizationName("MYiR_Electronics");
    app.setApplicationName("MEasy_HMI");
    app.setApplicationVersion("V2.0");

    QQmlApplicationEngine engine;

    qmlRegisterType<QmlProcess>("mprocess", 1, 0, "QmlProcess");
    qmlRegisterType<GetSystemInfo>("GetSystemInfoAPI", 1, 0, "GetSystemInfo");
    qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");
    qmlRegisterType<MyFunction>("MyFunction.module", 1, 0, "MyFunction");
    qmlRegisterType<ChargeManage>("ChargeManage",1,0,"ChargeManage");
    qmlRegisterType<Charge104>("Charge104",1,0,"Charge104");
    qmlRegisterType<MVideoOutput>("mvideooutput",1,0, "MVideoOutput");

    Translator *translator = Translator::getInstance();
    translator->set_QQmlEngine(&engine);
    engine.rootContext()->setContextProperty("translator",
                                             translator);

    ClearCache *clear_cache = new ClearCache;

    //font icon init
    iconFontInit();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
