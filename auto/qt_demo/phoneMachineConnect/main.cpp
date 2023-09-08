#include "pmmain.h"
#include <QApplication>

#ifndef CAR_APP
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QWidget content2;
    content2.setAttribute(Qt::WA_TranslucentBackground,true);
    content2.setStyleSheet("background-color: transparent");
    pmMain *w = pmMain::getInstance(&content2);
    w->showPhoneMachineConnect();

    content2.show();
    return a.exec();
}
#endif
