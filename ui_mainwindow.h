/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *s_mainWindowGridLayout;
    QGroupBox *s_renderSettings;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *RenderLabel;
    QPushButton *m_RenderButton;
    QLineEdit *SaveImageName;
    QLabel *SaveImageLabel;
    QRadioButton *SaveImageBoolean;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1080, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        s_mainWindowGridLayout = new QGridLayout(centralwidget);
        s_mainWindowGridLayout->setObjectName(QStringLiteral("s_mainWindowGridLayout"));
        s_renderSettings = new QGroupBox(centralwidget);
        s_renderSettings->setObjectName(QStringLiteral("s_renderSettings"));
        gridLayout = new QGridLayout(s_renderSettings);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 0, 1, 1);

        RenderLabel = new QLabel(s_renderSettings);
        RenderLabel->setObjectName(QStringLiteral("RenderLabel"));

        gridLayout->addWidget(RenderLabel, 1, 0, 1, 1);

        m_RenderButton = new QPushButton(s_renderSettings);
        m_RenderButton->setObjectName(QStringLiteral("m_RenderButton"));

        gridLayout->addWidget(m_RenderButton, 2, 0, 1, 1);

        SaveImageName = new QLineEdit(s_renderSettings);
        SaveImageName->setObjectName(QStringLiteral("SaveImageName"));
        SaveImageName->setEnabled(true);

        gridLayout->addWidget(SaveImageName, 5, 0, 1, 1);

        SaveImageLabel = new QLabel(s_renderSettings);
        SaveImageLabel->setObjectName(QStringLiteral("SaveImageLabel"));

        gridLayout->addWidget(SaveImageLabel, 3, 0, 1, 1);

        SaveImageBoolean = new QRadioButton(s_renderSettings);
        SaveImageBoolean->setObjectName(QStringLiteral("SaveImageBoolean"));

        gridLayout->addWidget(SaveImageBoolean, 4, 0, 1, 1);


        s_mainWindowGridLayout->addWidget(s_renderSettings, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        s_mainWindowGridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        s_mainWindowGridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1080, 27));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CYRenderer", 0));
        s_renderSettings->setTitle(QApplication::translate("MainWindow", "Render Settings", 0));
        RenderLabel->setText(QApplication::translate("MainWindow", "Render", 0));
        m_RenderButton->setText(QApplication::translate("MainWindow", "Render", 0));
        SaveImageLabel->setText(QApplication::translate("MainWindow", "Save Image", 0));
        SaveImageBoolean->setText(QApplication::translate("MainWindow", "SaveImage", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
