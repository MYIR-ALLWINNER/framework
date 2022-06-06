/********************************************************************************
** Form generated from reading UI file 'reverseline.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REVERSELINE_H
#define UI_REVERSELINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReverseLine
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QWidget *widget_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *ReverseLine)
    {
        if (ReverseLine->objectName().isEmpty())
            ReverseLine->setObjectName(QString::fromUtf8("ReverseLine"));
        ReverseLine->resize(660, 430);
        gridLayout_2 = new QGridLayout(ReverseLine);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 60, -1, 60);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_2 = new QGroupBox(ReverseLine);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"border-width:2px;\n"
"border-style:solid;\n"
"border-radius: 10px;\n"
"border-color:blue;\n"
"margin-top:0.5ex;\n"
"}\n"
"font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        widget_2 = new QWidget(groupBox_2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(295, 228));
        widget_2->setMaximumSize(QSize(295, 228));

        gridLayout_4->addWidget(widget_2, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 1, 1, 1, 1);

        groupBox = new QGroupBox(ReverseLine);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"border-width:2px;\n"
"border-style:solid;\n"
"border-radius: 10px;\n"
"border-color:blue;\n"
"margin-top:0.5ex;\n"
"}\n"
"font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
""));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(295, 228));
        widget->setMaximumSize(QSize(295, 228));

        gridLayout_3->addWidget(widget, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        label = new QLabel(ReverseLine);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("color:rgb(255,255,255);\n"
"background-color:rgb(255,255,255,0);\n"
"font: 63 11pt \"Ubuntu\";"));
        label->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(ReverseLine);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("color:rgb(255,255,255);\n"
"font: 63 11pt \"Ubuntu\";\n"
"background-color:rgb(255,255,255,0);"));
        label_2->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 5);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(ReverseLine);

        QMetaObject::connectSlotsByName(ReverseLine);
    } // setupUi

    void retranslateUi(QDialog *ReverseLine)
    {
        ReverseLine->setWindowTitle(QApplication::translate("ReverseLine", "Dialog", nullptr));
        groupBox_2->setTitle(QString());
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("ReverseLine", "\345\200\222\350\275\246\345\220\216\350\247\206\351\242\204\350\247\210", nullptr));
        label_2->setText(QApplication::translate("ReverseLine", "\345\200\222\350\275\246\347\272\277\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReverseLine: public Ui_ReverseLine {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REVERSELINE_H
