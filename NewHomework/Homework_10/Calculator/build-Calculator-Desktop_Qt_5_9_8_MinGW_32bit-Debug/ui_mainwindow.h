/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_10;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_17;
    QRadioButton *floatButton;
    QRadioButton *intButton;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpinBox *row_1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpinBox *col_1;
    QVBoxLayout *verticalLayout_9;
    QSpacerItem *verticalSpacer_5;
    QPushButton *generateMatrix_1;
    QSpacerItem *verticalSpacer_9;
    QTextBrowser *text_1;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_16;
    QSpacerItem *verticalSpacer;
    QRadioButton *minuxButton;
    QSpacerItem *verticalSpacer_3;
    QRadioButton *plusButton;
    QSpacerItem *verticalSpacer_4;
    QRadioButton *multiplyButton;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSpinBox *row_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QSpinBox *col_2;
    QVBoxLayout *verticalLayout_12;
    QSpacerItem *verticalSpacer_8;
    QPushButton *generateMatrix_2;
    QSpacerItem *verticalSpacer_10;
    QTextBrowser *text_2;
    QVBoxLayout *verticalLayout_7;
    QSpacerItem *verticalSpacer_6;
    QLabel *label;
    QSpacerItem *verticalSpacer_7;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_13;
    QSpacerItem *verticalSpacer_11;
    QPushButton *calculate;
    QSpacerItem *verticalSpacer_13;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_14;
    QSpacerItem *verticalSpacer_12;
    QPushButton *transpose;
    QSpacerItem *verticalSpacer_14;
    QTextBrowser *text_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1167, 691);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_17 = new QVBoxLayout(groupBox);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        floatButton = new QRadioButton(groupBox);
        floatButton->setObjectName(QStringLiteral("floatButton"));

        verticalLayout_17->addWidget(floatButton);

        intButton = new QRadioButton(groupBox);
        intButton->setObjectName(QStringLiteral("intButton"));

        verticalLayout_17->addWidget(intButton);


        verticalLayout_10->addWidget(groupBox);


        verticalLayout->addLayout(verticalLayout_10);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(10, -1, 10, -1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);

        horizontalLayout_3->addWidget(label_2);

        row_1 = new QSpinBox(centralWidget);
        row_1->setObjectName(QStringLiteral("row_1"));

        horizontalLayout_3->addWidget(row_1);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 2);

        verticalLayout_8->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(10, -1, 10, -1);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        horizontalLayout_4->addWidget(label_3);

        col_1 = new QSpinBox(centralWidget);
        col_1->setObjectName(QStringLiteral("col_1"));

        horizontalLayout_4->addWidget(col_1);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 2);

        verticalLayout_8->addLayout(horizontalLayout_4);


        horizontalLayout_2->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(10, -1, 0, 0);
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_5);

        generateMatrix_1 = new QPushButton(centralWidget);
        generateMatrix_1->setObjectName(QStringLiteral("generateMatrix_1"));

        verticalLayout_9->addWidget(generateMatrix_1);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_9);

        verticalLayout_9->setStretch(0, 5);
        verticalLayout_9->setStretch(1, 1);
        verticalLayout_9->setStretch(2, 2);

        horizontalLayout_2->addLayout(verticalLayout_9);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_2);

        text_1 = new QTextBrowser(centralWidget);
        text_1->setObjectName(QStringLiteral("text_1"));

        verticalLayout_3->addWidget(text_1);

        verticalLayout_3->setStretch(0, 3);
        verticalLayout_3->setStretch(1, 7);

        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, -1, -1, -1);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setCheckable(false);
        verticalLayout_16 = new QVBoxLayout(groupBox_2);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_16->addItem(verticalSpacer);

        minuxButton = new QRadioButton(groupBox_2);
        minuxButton->setObjectName(QStringLiteral("minuxButton"));

        verticalLayout_16->addWidget(minuxButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_16->addItem(verticalSpacer_3);

        plusButton = new QRadioButton(groupBox_2);
        plusButton->setObjectName(QStringLiteral("plusButton"));

        verticalLayout_16->addWidget(plusButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_16->addItem(verticalSpacer_4);

        multiplyButton = new QRadioButton(groupBox_2);
        multiplyButton->setObjectName(QStringLiteral("multiplyButton"));

        verticalLayout_16->addWidget(multiplyButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_16->addItem(verticalSpacer_2);

        verticalLayout_16->setStretch(0, 15);
        verticalLayout_16->setStretch(1, 1);
        verticalLayout_16->setStretch(2, 5);
        verticalLayout_16->setStretch(3, 1);
        verticalLayout_16->setStretch(4, 5);
        verticalLayout_16->setStretch(5, 1);
        verticalLayout_16->setStretch(6, 5);

        verticalLayout_6->addWidget(groupBox_2);

        verticalLayout_6->setStretch(0, 10);

        horizontalLayout->addLayout(verticalLayout_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(10, -1, 10, -1);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        horizontalLayout_6->addWidget(label_4);

        row_2 = new QSpinBox(centralWidget);
        row_2->setObjectName(QStringLiteral("row_2"));

        horizontalLayout_6->addWidget(row_2);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 2);

        verticalLayout_11->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(10, -1, 10, -1);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        horizontalLayout_7->addWidget(label_5);

        col_2 = new QSpinBox(centralWidget);
        col_2->setObjectName(QStringLiteral("col_2"));

        horizontalLayout_7->addWidget(col_2);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 2);

        verticalLayout_11->addLayout(horizontalLayout_7);


        horizontalLayout_5->addLayout(verticalLayout_11);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(10, -1, -1, 0);
        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_8);

        generateMatrix_2 = new QPushButton(centralWidget);
        generateMatrix_2->setObjectName(QStringLiteral("generateMatrix_2"));

        verticalLayout_12->addWidget(generateMatrix_2);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_10);

        verticalLayout_12->setStretch(0, 5);
        verticalLayout_12->setStretch(1, 1);
        verticalLayout_12->setStretch(2, 2);

        horizontalLayout_5->addLayout(verticalLayout_12);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 1);

        verticalLayout_5->addLayout(horizontalLayout_5);

        text_2 = new QTextBrowser(centralWidget);
        text_2->setObjectName(QStringLiteral("text_2"));

        verticalLayout_5->addWidget(text_2);

        verticalLayout_5->setStretch(0, 3);
        verticalLayout_5->setStretch(1, 7);

        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(40, -1, -1, -1);
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_6);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_7->addWidget(label);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_7);

        verticalLayout_7->setStretch(0, 10);
        verticalLayout_7->setStretch(1, 1);
        verticalLayout_7->setStretch(2, 5);

        horizontalLayout->addLayout(verticalLayout_7);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, -1);
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_11);

        calculate = new QPushButton(centralWidget);
        calculate->setObjectName(QStringLiteral("calculate"));

        verticalLayout_13->addWidget(calculate);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_13);

        verticalLayout_13->setStretch(0, 5);
        verticalLayout_13->setStretch(1, 1);
        verticalLayout_13->setStretch(2, 2);

        horizontalLayout_8->addLayout(verticalLayout_13);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_14->addItem(verticalSpacer_12);

        transpose = new QPushButton(centralWidget);
        transpose->setObjectName(QStringLiteral("transpose"));
        transpose->setFont(font);

        verticalLayout_14->addWidget(transpose);

        verticalSpacer_14 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_14->addItem(verticalSpacer_14);

        verticalLayout_14->setStretch(0, 5);
        verticalLayout_14->setStretch(1, 1);
        verticalLayout_14->setStretch(2, 2);

        horizontalLayout_8->addLayout(verticalLayout_14);

        horizontalLayout_8->setStretch(0, 2);
        horizontalLayout_8->setStretch(1, 2);
        horizontalLayout_8->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout_8);

        text_3 = new QTextBrowser(centralWidget);
        text_3->setObjectName(QStringLiteral("text_3"));

        verticalLayout_4->addWidget(text_3);

        verticalLayout_4->setStretch(0, 3);
        verticalLayout_4->setStretch(1, 7);

        horizontalLayout->addLayout(verticalLayout_4);

        horizontalLayout->setStretch(0, 10);
        horizontalLayout->setStretch(1, 3);
        horizontalLayout->setStretch(2, 10);
        horizontalLayout->setStretch(3, 3);
        horizontalLayout->setStretch(4, 10);

        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 12);

        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1167, 23));
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
        groupBox->setTitle(QString());
        floatButton->setText(QApplication::translate("MainWindow", "\346\265\256\347\202\271", Q_NULLPTR));
        intButton->setText(QApplication::translate("MainWindow", "\346\225\264\346\225\260", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\350\241\214\346\225\260\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\345\210\227\346\225\260\357\274\232", Q_NULLPTR));
        generateMatrix_1->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\347\237\251\351\230\2651", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        minuxButton->setText(QApplication::translate("MainWindow", "-", Q_NULLPTR));
        plusButton->setText(QApplication::translate("MainWindow", "+", Q_NULLPTR));
        multiplyButton->setText(QApplication::translate("MainWindow", "*", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\350\241\214\346\225\260\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\345\210\227\346\225\260\357\274\232", Q_NULLPTR));
        generateMatrix_2->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\347\237\251\351\230\2652", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "=", Q_NULLPTR));
        calculate->setText(QApplication::translate("MainWindow", "\350\256\241\347\256\227", Q_NULLPTR));
        transpose->setText(QApplication::translate("MainWindow", "\347\273\223\346\236\234\350\275\254\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
