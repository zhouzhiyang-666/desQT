/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_4;
    QLineEdit *input_miyao;
    QLabel *label_3;
    QLabel *label_5;
    QPushButton *pushButton_3;
    QLabel *label_6;
    QTextEdit *txtmingwen;
    QTextEdit *miwen;
    QLineEdit *miyao;
    QLabel *label_7;
    QLabel *label_8;
    QTextEdit *input_miwen;
    QTextEdit *output_mingwen;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(500, 565);
        MainWindow->setMinimumSize(QSize(500, 565));
        MainWindow->setMaximumSize(QSize(500, 565));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 40, 54, 12));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 110, 91, 16));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 500, 81, 31));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(410, 500, 81, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 150, 54, 12));
        input_miyao = new QLineEdit(centralWidget);
        input_miyao->setObjectName(QStringLiteral("input_miyao"));
        input_miyao->setGeometry(QRect(90, 330, 231, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 260, 71, 21));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 330, 71, 20));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(210, 500, 81, 31));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 370, 61, 16));
        txtmingwen = new QTextEdit(centralWidget);
        txtmingwen->setObjectName(QStringLiteral("txtmingwen"));
        txtmingwen->setGeometry(QRect(70, 30, 371, 71));
        miwen = new QTextEdit(centralWidget);
        miwen->setObjectName(QStringLiteral("miwen"));
        miwen->setGeometry(QRect(70, 140, 371, 71));
        miyao = new QLineEdit(centralWidget);
        miyao->setObjectName(QStringLiteral("miyao"));
        miyao->setGeometry(QRect(150, 110, 291, 20));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 10, 481, 20));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(13, 230, 471, 20));
        input_miwen = new QTextEdit(centralWidget);
        input_miwen->setObjectName(QStringLiteral("input_miwen"));
        input_miwen->setGeometry(QRect(80, 250, 361, 71));
        output_mingwen = new QTextEdit(centralWidget);
        output_mingwen->setObjectName(QStringLiteral("output_mingwen"));
        output_mingwen->setGeometry(QRect(80, 370, 361, 121));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 500, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\346\230\216\346\226\207\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\345\257\206\351\222\245(\351\232\217\346\234\272\347\224\237\346\210\220)\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\345\212\240\345\257\206", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "\350\247\243\345\257\206", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\345\257\206\346\226\207\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\345\257\206\346\226\207(\350\247\243\345\257\206)\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\345\257\206\351\222\245(\350\247\243\345\257\206)\357\274\232", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "\351\207\215\347\275\256", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "\346\230\216\346\226\207\350\276\223\345\207\272\357\274\232", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "-------------------------------------\345\212\240\345\257\206--------------------------------------", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "--------------------------------------\350\247\243\345\257\206------------------------------------", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
