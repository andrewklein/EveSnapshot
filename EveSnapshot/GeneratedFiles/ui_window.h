/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *mainTab;
    QGridLayout *gridLayout_2;
    QPushButton *loadProfileAllBtn;
    QLabel *selectedProfileLbl;
    QComboBox *profileComboBox;
    QPushButton *loadProfileBtn;
    QTreeWidget *profileLoadedTree;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QPushButton *deleteProfileBtn;
    QLabel *selectedCharLbl;
    QPushButton *createFromSelectedBtn;
    QPushButton *renameProfileBtn;
    QTreeWidget *profileTree;
    QComboBox *charSelectCombo;
    QWidget *settingsTab;
    QFormLayout *formLayout;
    QLabel *evePathLbl;
    QLineEdit *evePathInput;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(460, 280);
        MainWindow->setDocumentMode(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        mainTab = new QWidget();
        mainTab->setObjectName(QStringLiteral("mainTab"));
        gridLayout_2 = new QGridLayout(mainTab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        loadProfileAllBtn = new QPushButton(mainTab);
        loadProfileAllBtn->setObjectName(QStringLiteral("loadProfileAllBtn"));

        gridLayout_2->addWidget(loadProfileAllBtn, 6, 1, 1, 1);

        selectedProfileLbl = new QLabel(mainTab);
        selectedProfileLbl->setObjectName(QStringLiteral("selectedProfileLbl"));

        gridLayout_2->addWidget(selectedProfileLbl, 1, 1, 1, 1);

        profileComboBox = new QComboBox(mainTab);
        profileComboBox->setObjectName(QStringLiteral("profileComboBox"));

        gridLayout_2->addWidget(profileComboBox, 2, 1, 1, 1);

        loadProfileBtn = new QPushButton(mainTab);
        loadProfileBtn->setObjectName(QStringLiteral("loadProfileBtn"));

        gridLayout_2->addWidget(loadProfileBtn, 5, 1, 1, 1);

        profileLoadedTree = new QTreeWidget(mainTab);
        profileLoadedTree->setObjectName(QStringLiteral("profileLoadedTree"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(profileLoadedTree->sizePolicy().hasHeightForWidth());
        profileLoadedTree->setSizePolicy(sizePolicy);
        profileLoadedTree->setFrameShape(QFrame::StyledPanel);
        profileLoadedTree->setFrameShadow(QFrame::Sunken);
        profileLoadedTree->setIndentation(6);

        gridLayout_2->addWidget(profileLoadedTree, 1, 0, 6, 1);

        tabWidget->addTab(mainTab, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        deleteProfileBtn = new QPushButton(tab);
        deleteProfileBtn->setObjectName(QStringLiteral("deleteProfileBtn"));

        gridLayout_3->addWidget(deleteProfileBtn, 5, 1, 1, 1);

        selectedCharLbl = new QLabel(tab);
        selectedCharLbl->setObjectName(QStringLiteral("selectedCharLbl"));

        gridLayout_3->addWidget(selectedCharLbl, 0, 1, 1, 1);

        createFromSelectedBtn = new QPushButton(tab);
        createFromSelectedBtn->setObjectName(QStringLiteral("createFromSelectedBtn"));

        gridLayout_3->addWidget(createFromSelectedBtn, 3, 1, 1, 1);

        renameProfileBtn = new QPushButton(tab);
        renameProfileBtn->setObjectName(QStringLiteral("renameProfileBtn"));

        gridLayout_3->addWidget(renameProfileBtn, 4, 1, 1, 1);

        profileTree = new QTreeWidget(tab);
        profileTree->setObjectName(QStringLiteral("profileTree"));
        profileTree->setIndentation(5);

        gridLayout_3->addWidget(profileTree, 0, 0, 6, 1);

        charSelectCombo = new QComboBox(tab);
        charSelectCombo->setObjectName(QStringLiteral("charSelectCombo"));

        gridLayout_3->addWidget(charSelectCombo, 1, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        settingsTab = new QWidget();
        settingsTab->setObjectName(QStringLiteral("settingsTab"));
        settingsTab->setEnabled(true);
        formLayout = new QFormLayout(settingsTab);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        evePathLbl = new QLabel(settingsTab);
        evePathLbl->setObjectName(QStringLiteral("evePathLbl"));

        formLayout->setWidget(0, QFormLayout::LabelRole, evePathLbl);

        evePathInput = new QLineEdit(settingsTab);
        evePathInput->setObjectName(QStringLiteral("evePathInput"));
        evePathInput->setCursorMoveStyle(Qt::VisualMoveStyle);

        formLayout->setWidget(1, QFormLayout::SpanningRole, evePathInput);

        tabWidget->addTab(settingsTab, QString());

        verticalLayout_2->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "EveSnapshot", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
#ifndef QT_NO_TOOLTIP
        tabWidget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_ACCESSIBILITY
        tabWidget->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        loadProfileAllBtn->setText(QApplication::translate("MainWindow", "Load Profile for All Characters", 0));
        selectedProfileLbl->setText(QApplication::translate("MainWindow", "Selected Profile", 0));
        loadProfileBtn->setText(QApplication::translate("MainWindow", "Load Profile for Character", 0));
        QTreeWidgetItem *___qtreewidgetitem = profileLoadedTree->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "Profile Loaded", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Character Name", 0));
        tabWidget->setTabText(tabWidget->indexOf(mainTab), QApplication::translate("MainWindow", "Characters", 0));
        deleteProfileBtn->setText(QApplication::translate("MainWindow", "Delete Selected Profile", 0));
        selectedCharLbl->setText(QApplication::translate("MainWindow", "Selected Character", 0));
        createFromSelectedBtn->setText(QApplication::translate("MainWindow", "Create New From Selected Character", 0));
        renameProfileBtn->setText(QApplication::translate("MainWindow", "Rename Selected Profile", 0));
        QTreeWidgetItem *___qtreewidgetitem1 = profileTree->headerItem();
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "Profile Name", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Manage Profiles", 0));
        evePathLbl->setText(QApplication::translate("MainWindow", "Eve Settings Path", 0));
        tabWidget->setTabText(tabWidget->indexOf(settingsTab), QApplication::translate("MainWindow", "Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
