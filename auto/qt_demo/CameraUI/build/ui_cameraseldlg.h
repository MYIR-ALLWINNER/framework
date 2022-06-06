/********************************************************************************
** Form generated from reading UI file 'cameraseldlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERASELDLG_H
#define UI_CAMERASELDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraSelDlg
{
public:
    QPushButton *pushButtonEnter;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayoutVideo;
    QCheckBox *checkBoxVideo2;
    QCheckBox *checkBoxVideo6;
    QCheckBox *checkBoxVideo0;
    QCheckBox *checkBoxVideo1;
    QCheckBox *checkBoxVideo7;
    QCheckBox *checkBoxVideo4;
    QCheckBox *checkBoxVideo5;
    QCheckBox *checkBoxVideo3;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *CameraSelDlg)
    {
        if (CameraSelDlg->objectName().isEmpty())
            CameraSelDlg->setObjectName(QString::fromUtf8("CameraSelDlg"));
        CameraSelDlg->resize(287, 339);
        CameraSelDlg->setStyleSheet(QString::fromUtf8("background-color:rgb(104, 98, 98,90);\n"
"border-radius:15px;\n"
""));
        pushButtonEnter = new QPushButton(CameraSelDlg);
        pushButtonEnter->setObjectName(QString::fromUtf8("pushButtonEnter"));
        pushButtonEnter->setGeometry(QRect(100, 270, 80, 40));
        pushButtonEnter->setMinimumSize(QSize(80, 40));
        pushButtonEnter->setMaximumSize(QSize(80, 40));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        pushButtonEnter->setFont(font);
        pushButtonEnter->setFocusPolicy(Qt::WheelFocus);
        gridLayoutWidget_2 = new QWidget(CameraSelDlg);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(60, 30, 160, 218));
        gridLayoutVideo = new QGridLayout(gridLayoutWidget_2);
        gridLayoutVideo->setObjectName(QString::fromUtf8("gridLayoutVideo"));
        gridLayoutVideo->setContentsMargins(0, 0, 0, 0);
        checkBoxVideo2 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup = new QButtonGroup(CameraSelDlg);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(checkBoxVideo2);
        checkBoxVideo2->setObjectName(QString::fromUtf8("checkBoxVideo2"));

        gridLayoutVideo->addWidget(checkBoxVideo2, 5, 0, 1, 1);

        checkBoxVideo6 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup->addButton(checkBoxVideo6);
        checkBoxVideo6->setObjectName(QString::fromUtf8("checkBoxVideo6"));

        gridLayoutVideo->addWidget(checkBoxVideo6, 1, 0, 1, 1);

        checkBoxVideo0 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup->addButton(checkBoxVideo0);
        checkBoxVideo0->setObjectName(QString::fromUtf8("checkBoxVideo0"));

        gridLayoutVideo->addWidget(checkBoxVideo0, 7, 0, 1, 1);

        checkBoxVideo1 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup->addButton(checkBoxVideo1);
        checkBoxVideo1->setObjectName(QString::fromUtf8("checkBoxVideo1"));

        gridLayoutVideo->addWidget(checkBoxVideo1, 6, 0, 1, 1);

        checkBoxVideo7 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup->addButton(checkBoxVideo7);
        checkBoxVideo7->setObjectName(QString::fromUtf8("checkBoxVideo7"));

        gridLayoutVideo->addWidget(checkBoxVideo7, 0, 0, 1, 1);

        checkBoxVideo4 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup->addButton(checkBoxVideo4);
        checkBoxVideo4->setObjectName(QString::fromUtf8("checkBoxVideo4"));

        gridLayoutVideo->addWidget(checkBoxVideo4, 3, 0, 1, 1);

        checkBoxVideo5 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup->addButton(checkBoxVideo5);
        checkBoxVideo5->setObjectName(QString::fromUtf8("checkBoxVideo5"));

        gridLayoutVideo->addWidget(checkBoxVideo5, 2, 0, 1, 1);

        checkBoxVideo3 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup->addButton(checkBoxVideo3);
        checkBoxVideo3->setObjectName(QString::fromUtf8("checkBoxVideo3"));

        gridLayoutVideo->addWidget(checkBoxVideo3, 4, 0, 1, 1);


        retranslateUi(CameraSelDlg);

        QMetaObject::connectSlotsByName(CameraSelDlg);
    } // setupUi

    void retranslateUi(QDialog *CameraSelDlg)
    {
        CameraSelDlg->setWindowTitle(QApplication::translate("CameraSelDlg", "Dialog", nullptr));
        pushButtonEnter->setText(QApplication::translate("CameraSelDlg", "\347\241\256\345\256\232", nullptr));
        checkBoxVideo2->setText(QApplication::translate("CameraSelDlg", "Video2", nullptr));
        checkBoxVideo6->setText(QApplication::translate("CameraSelDlg", "Video6", nullptr));
        checkBoxVideo0->setText(QApplication::translate("CameraSelDlg", "Video0", nullptr));
        checkBoxVideo1->setText(QApplication::translate("CameraSelDlg", "Video1", nullptr));
        checkBoxVideo7->setText(QApplication::translate("CameraSelDlg", "Video7", nullptr));
        checkBoxVideo4->setText(QApplication::translate("CameraSelDlg", "Video4", nullptr));
        checkBoxVideo5->setText(QApplication::translate("CameraSelDlg", "Video5", nullptr));
        checkBoxVideo3->setText(QApplication::translate("CameraSelDlg", "Video3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraSelDlg: public Ui_CameraSelDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERASELDLG_H
