/********************************************************************************
** Form generated from reading UI file 'searchfiledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHFILEDIALOG_H
#define UI_SEARCHFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_searchFileDialog
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;

    void setupUi(QWidget *searchFileDialog)
    {
        if (searchFileDialog->objectName().isEmpty())
            searchFileDialog->setObjectName(QString::fromUtf8("searchFileDialog"));
        searchFileDialog->resize(690, 399);
        searchFileDialog->setMinimumSize(QSize(690, 399));
        searchFileDialog->setMaximumSize(QSize(690, 399));
        widget = new QWidget(searchFileDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 690, 39));
        widget->setMinimumSize(QSize(690, 39));
        widget->setMaximumSize(QSize(690, 39));
        widget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(0, 170, 255),stop:1  rgb(0, 255, 255));"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(widget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setMinimumSize(QSize(251, 35));
        titleLabel->setMaximumSize(QSize(251, 35));
        titleLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color:white;"));
        titleLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(titleLabel);

        stackedWidget = new QStackedWidget(searchFileDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 40, 691, 361));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        retranslateUi(searchFileDialog);

        QMetaObject::connectSlotsByName(searchFileDialog);
    } // setupUi

    void retranslateUi(QWidget *searchFileDialog)
    {
        searchFileDialog->setWindowTitle(QApplication::translate("searchFileDialog", "Form", nullptr));
        titleLabel->setText(QApplication::translate("searchFileDialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; color:#ffffff;\">\346\267\273\345\212\240\346\233\262\347\233\256\345\210\260\345\210\227\350\241\250</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class searchFileDialog: public Ui_searchFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHFILEDIALOG_H
