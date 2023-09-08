/********************************************************************************
** Form generated from reading UI file 'mainwindowbase.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWBASE_H
#define UI_MAINWINDOWBASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowBase
{
public:
    QAction *printAction;
    QAction *quitAction;
    QAction *markAction;
    QAction *unmarkAction;
    QAction *clearAction;
    QAction *printPreviewAction;
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QMenu *menu_Selection;
    QMenu *menu_File;
    QStatusBar *statusbar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *vboxLayout1;
    QTreeWidget *fontTree;

    void setupUi(QMainWindow *MainWindowBase)
    {
        if (MainWindowBase->objectName().isEmpty())
            MainWindowBase->setObjectName(QString::fromUtf8("MainWindowBase"));
        MainWindowBase->resize(800, 345);
        printAction = new QAction(MainWindowBase);
        printAction->setObjectName(QString::fromUtf8("printAction"));
        printAction->setEnabled(false);
        quitAction = new QAction(MainWindowBase);
        quitAction->setObjectName(QString::fromUtf8("quitAction"));
        markAction = new QAction(MainWindowBase);
        markAction->setObjectName(QString::fromUtf8("markAction"));
        unmarkAction = new QAction(MainWindowBase);
        unmarkAction->setObjectName(QString::fromUtf8("unmarkAction"));
        clearAction = new QAction(MainWindowBase);
        clearAction->setObjectName(QString::fromUtf8("clearAction"));
        printPreviewAction = new QAction(MainWindowBase);
        printPreviewAction->setObjectName(QString::fromUtf8("printPreviewAction"));
        printPreviewAction->setEnabled(false);
        centralwidget = new QWidget(MainWindowBase);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        vboxLayout = new QVBoxLayout(centralwidget);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        vboxLayout->addWidget(textEdit);

        MainWindowBase->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowBase);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 18));
        menu_Selection = new QMenu(menubar);
        menu_Selection->setObjectName(QString::fromUtf8("menu_Selection"));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindowBase->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowBase);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindowBase->setStatusBar(statusbar);
        dockWidget = new QDockWidget(MainWindowBase);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        vboxLayout1 = new QVBoxLayout(dockWidgetContents);
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        fontTree = new QTreeWidget(dockWidgetContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        fontTree->setHeaderItem(__qtreewidgetitem);
        fontTree->setObjectName(QString::fromUtf8("fontTree"));
        fontTree->setSelectionMode(QAbstractItemView::ExtendedSelection);

        vboxLayout1->addWidget(fontTree);

        dockWidget->setWidget(dockWidgetContents);
        MainWindowBase->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Selection->menuAction());
        menu_Selection->addAction(markAction);
        menu_Selection->addAction(unmarkAction);
        menu_Selection->addAction(clearAction);
        menu_File->addAction(printPreviewAction);
        menu_File->addAction(printAction);
        menu_File->addAction(quitAction);

        retranslateUi(MainWindowBase);

        QMetaObject::connectSlotsByName(MainWindowBase);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowBase)
    {
        MainWindowBase->setWindowTitle(QApplication::translate("MainWindowBase", "Font Sampler", nullptr));
        printAction->setText(QApplication::translate("MainWindowBase", "&Print...", nullptr));
#ifndef QT_NO_SHORTCUT
        printAction->setShortcut(QApplication::translate("MainWindowBase", "Ctrl+P", nullptr));
#endif // QT_NO_SHORTCUT
        quitAction->setText(QApplication::translate("MainWindowBase", "E&xit", nullptr));
#ifndef QT_NO_SHORTCUT
        quitAction->setShortcut(QApplication::translate("MainWindowBase", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        markAction->setText(QApplication::translate("MainWindowBase", "&Mark", nullptr));
#ifndef QT_NO_SHORTCUT
        markAction->setShortcut(QApplication::translate("MainWindowBase", "Ctrl+M", nullptr));
#endif // QT_NO_SHORTCUT
        unmarkAction->setText(QApplication::translate("MainWindowBase", "&Unmark", nullptr));
#ifndef QT_NO_SHORTCUT
        unmarkAction->setShortcut(QApplication::translate("MainWindowBase", "Ctrl+U", nullptr));
#endif // QT_NO_SHORTCUT
        clearAction->setText(QApplication::translate("MainWindowBase", "&Clear", nullptr));
        printPreviewAction->setText(QApplication::translate("MainWindowBase", "Print Preview...", nullptr));
        menu_Selection->setTitle(QApplication::translate("MainWindowBase", "&Selection", nullptr));
        menu_File->setTitle(QApplication::translate("MainWindowBase", "&File", nullptr));
        dockWidget->setWindowTitle(QApplication::translate("MainWindowBase", "Available Fonts", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowBase: public Ui_MainWindowBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWBASE_H
