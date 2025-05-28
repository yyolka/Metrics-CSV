/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_9;
    QTableWidget *tableWidget;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_6;
    QPushButton *chooseFileButton;
    QLineEdit *fileNameLineEdit;
    QVBoxLayout *verticalLayout_5;
    QPushButton *loadDataButton;
    QPushButton *calculateMetricsButton;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_8;
    QLabel *chooseRegionLabel;
    QLineEdit *regionLineEdit;
    QVBoxLayout *verticalLayout_7;
    QLabel *chooseColumnLabel;
    QComboBox *columnComboBox;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *minLabel;
    QLineEdit *minLineEdit;
    QVBoxLayout *verticalLayout_2;
    QLabel *medianLabel;
    QLineEdit *medianLineEdit;
    QVBoxLayout *verticalLayout_4;
    QLabel *maxLabel;
    QLineEdit *maxLineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        verticalLayout_9->addWidget(tableWidget);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");

        verticalLayout_9->addWidget(graphicsView);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");

        verticalLayout_9->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(verticalLayout_9);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        chooseFileButton = new QPushButton(centralwidget);
        chooseFileButton->setObjectName("chooseFileButton");

        verticalLayout_6->addWidget(chooseFileButton);

        fileNameLineEdit = new QLineEdit(centralwidget);
        fileNameLineEdit->setObjectName("fileNameLineEdit");
        fileNameLineEdit->setReadOnly(true);

        verticalLayout_6->addWidget(fileNameLineEdit);


        horizontalLayout_2->addLayout(verticalLayout_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        loadDataButton = new QPushButton(centralwidget);
        loadDataButton->setObjectName("loadDataButton");

        verticalLayout_5->addWidget(loadDataButton);

        calculateMetricsButton = new QPushButton(centralwidget);
        calculateMetricsButton->setObjectName("calculateMetricsButton");

        verticalLayout_5->addWidget(calculateMetricsButton);


        horizontalLayout_2->addLayout(verticalLayout_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        chooseRegionLabel = new QLabel(centralwidget);
        chooseRegionLabel->setObjectName("chooseRegionLabel");

        verticalLayout_8->addWidget(chooseRegionLabel);

        regionLineEdit = new QLineEdit(centralwidget);
        regionLineEdit->setObjectName("regionLineEdit");

        verticalLayout_8->addWidget(regionLineEdit);


        horizontalLayout_3->addLayout(verticalLayout_8);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        chooseColumnLabel = new QLabel(centralwidget);
        chooseColumnLabel->setObjectName("chooseColumnLabel");

        verticalLayout_7->addWidget(chooseColumnLabel);

        columnComboBox = new QComboBox(centralwidget);
        columnComboBox->addItem(QString());
        columnComboBox->addItem(QString());
        columnComboBox->addItem(QString());
        columnComboBox->addItem(QString());
        columnComboBox->addItem(QString());
        columnComboBox->setObjectName("columnComboBox");

        verticalLayout_7->addWidget(columnComboBox);


        horizontalLayout_3->addLayout(verticalLayout_7);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        minLabel = new QLabel(centralwidget);
        minLabel->setObjectName("minLabel");

        verticalLayout_3->addWidget(minLabel);

        minLineEdit = new QLineEdit(centralwidget);
        minLineEdit->setObjectName("minLineEdit");
        minLineEdit->setReadOnly(true);

        verticalLayout_3->addWidget(minLineEdit);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        medianLabel = new QLabel(centralwidget);
        medianLabel->setObjectName("medianLabel");

        verticalLayout_2->addWidget(medianLabel);

        medianLineEdit = new QLineEdit(centralwidget);
        medianLineEdit->setObjectName("medianLineEdit");
        medianLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(medianLineEdit);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        maxLabel = new QLabel(centralwidget);
        maxLabel->setObjectName("maxLabel");

        verticalLayout_4->addWidget(maxLabel);

        maxLineEdit = new QLineEdit(centralwidget);
        maxLineEdit->setObjectName("maxLineEdit");
        maxLineEdit->setReadOnly(true);

        verticalLayout_4->addWidget(maxLineEdit);


        horizontalLayout->addLayout(verticalLayout_4);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        chooseFileButton->setText(QCoreApplication::translate("MainWindow", "Choose File", nullptr));
        fileNameLineEdit->setText(QString());
        loadDataButton->setText(QCoreApplication::translate("MainWindow", "Load data", nullptr));
        calculateMetricsButton->setText(QCoreApplication::translate("MainWindow", "Calculate metrics", nullptr));
        chooseRegionLabel->setText(QCoreApplication::translate("MainWindow", "Choose region", nullptr));
        chooseColumnLabel->setText(QCoreApplication::translate("MainWindow", "Choose column", nullptr));
        columnComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "natural_population_growth", nullptr));
        columnComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "birth_rate", nullptr));
        columnComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "death_rate", nullptr));
        columnComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "gdw", nullptr));
        columnComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "urbanization", nullptr));

        minLabel->setText(QCoreApplication::translate("MainWindow", "Minimum", nullptr));
        medianLabel->setText(QCoreApplication::translate("MainWindow", "Median", nullptr));
        maxLabel->setText(QCoreApplication::translate("MainWindow", "Maximum", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
