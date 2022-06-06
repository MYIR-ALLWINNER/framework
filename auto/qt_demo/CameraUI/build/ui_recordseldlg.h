/********************************************************************************
** Form generated from reading UI file 'recordseldlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDSELDLG_H
#define UI_RECORDSELDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecordSelDlg
{
public:
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayoutVideo;
    QCheckBox *checkBoxVideo5;
    QCheckBox *checkBoxVideo7;
    QCheckBox *checkBoxVideo2;
    QCheckBox *checkBoxVideo1;
    QCheckBox *checkBoxVideo4;
    QCheckBox *checkBoxVideo3;
    QCheckBox *checkBoxVideo0;
    QCheckBox *checkBoxVideo6;
    QPushButton *pushButtonEnter;
    QLabel *VideoLabel;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *RecordSelDlg)
    {
        if (RecordSelDlg->objectName().isEmpty())
            RecordSelDlg->setObjectName(QString::fromUtf8("RecordSelDlg"));
        RecordSelDlg->resize(297, 358);
        RecordSelDlg->setStyleSheet(QString::fromUtf8("background-color:rgb(104, 98, 98,90);\n"
"border-radius:15px;\n"
""));
        gridLayoutWidget_2 = new QWidget(RecordSelDlg);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(60, 60, 160, 218));
        gridLayoutVideo = new QGridLayout(gridLayoutWidget_2);
        gridLayoutVideo->setObjectName(QString::fromUtf8("gridLayoutVideo"));
        gridLayoutVideo->setContentsMargins(0, 0, 0, 0);
        checkBoxVideo5 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup = new QButtonGroup(RecordSelDlg);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(checkBoxVideo5);
        checkBoxVideo5->setObjectName(QString::fromUtf8("checkBoxVideo5"));

        gridLayoutVideo->addWidget(checkBoxVideo5, 2, 0, 1, 1);

        checkBoxVideo7 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup->addButton(checkBoxVideo7);
        checkBoxVideo7->setObjectName(QString::fromUtf8("checkBoxVideo7"));

        gridLayoutVideo->addWidget(checkBoxVideo7, 0, 0, 1, 1);

        checkBoxVideo2 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup->addButton(checkBoxVideo2);
        checkBoxVideo2->setObjectName(QString::fromUtf8("checkBoxVideo2"));

        gridLayoutVideo->addWidget(checkBoxVideo2, 5, 0, 1, 1);

        checkBoxVideo1 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup->addButton(checkBoxVideo1);
        checkBoxVideo1->setObjectName(QString::fromUtf8("checkBoxVideo1"));

        gridLayoutVideo->addWidget(checkBoxVideo1, 6, 0, 1, 1);

        checkBoxVideo4 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup->addButton(checkBoxVideo4);
        checkBoxVideo4->setObjectName(QString::fromUtf8("checkBoxVideo4"));

        gridLayoutVideo->addWidget(checkBoxVideo4, 3, 0, 1, 1);

        checkBoxVideo3 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup->addButton(checkBoxVideo3);
        checkBoxVideo3->setObjectName(QString::fromUtf8("checkBoxVideo3"));

        gridLayoutVideo->addWidget(checkBoxVideo3, 4, 0, 1, 1);

        checkBoxVideo0 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup->addButton(checkBoxVideo0);
        checkBoxVideo0->setObjectName(QString::fromUtf8("checkBoxVideo0"));

        gridLayoutVideo->addWidget(checkBoxVideo0, 7, 0, 1, 1);

        checkBoxVideo6 = new QCheckBox(gridLayoutWidget_2);
        buttonGroup->addButton(checkBoxVideo6);
        checkBoxVideo6->setObjectName(QString::fromUtf8("checkBoxVideo6"));

        gridLayoutVideo->addWidget(checkBoxVideo6, 1, 0, 1, 1);

        pushButtonEnter = new QPushButton(RecordSelDlg);
        pushButtonEnter->setObjectName(QString::fromUtf8("pushButtonEnter"));
        pushButtonEnter->setGeometry(QRect(100, 290, 80, 40));
        pushButtonEnter->setMinimumSize(QSize(80, 40));
        pushButtonEnter->setMaximumSize(QSize(80, 40));
        pushButtonEnter->setFocusPolicy(Qt::WheelFocus);
        VideoLabel = new QLabel(RecordSelDlg);
        VideoLabel->setObjectName(QString::fromUtf8("VideoLabel"));
        VideoLabel->setGeometry(QRect(40, 20, 200, 21));
        VideoLabel->setMaximumSize(QSize(601, 31));
        VideoLabel->setAlignment(Qt::AlignCenter);

        retranslateUi(RecordSelDlg);

        QMetaObject::connectSlotsByName(RecordSelDlg);
    } // setupUi

    void retranslateUi(QDialog *RecordSelDlg)
    {
        RecordSelDlg->setWindowTitle(QApplication::translate("RecordSelDlg", "Dialog", nullptr));
        checkBoxVideo5->setText(QApplication::translate("RecordSelDlg", "RedVideo5", nullptr));
        checkBoxVideo7->setText(QApplication::translate("RecordSelDlg", "RedVideo7", nullptr));
        checkBoxVideo2->setText(QApplication::translate("RecordSelDlg", "RedVideo2", nullptr));
        checkBoxVideo1->setText(QApplication::translate("RecordSelDlg", "RedVideo1", nullptr));
        checkBoxVideo4->setText(QApplication::translate("RecordSelDlg", "RedVideo4", nullptr));
        checkBoxVideo3->setText(QApplication::translate("RecordSelDlg", "RedVideo3", nullptr));
        checkBoxVideo0->setText(QApplication::translate("RecordSelDlg", "RedVideo0", nullptr));
        checkBoxVideo6->setText(QApplication::translate("RecordSelDlg", "RedVideo6", nullptr));
        pushButtonEnter->setText(QApplication::translate("RecordSelDlg", "\347\241\256\345\256\232", nullptr));
        VideoLabel->setText(QApplication::translate("RecordSelDlg", "current preview:video0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecordSelDlg: public Ui_RecordSelDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDSELDLG_H
