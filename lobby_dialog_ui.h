/********************************************************************************
** Form generated from reading UI file 'lobby_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LOBBY_DIALOG_UI_H
#define LOBBY_DIALOG_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LobbyDialog
{
public:
    QWidget *centralwidget;
    QListWidget *characterList;
    QGraphicsView *characterView;
    QListView *userlist;
    QScrollArea *worldScroll;
    QWidget *scrollAreaWidgetContents;
    QListWidget *worldList;
    QLabel *userlabel;
    QPushButton *readyButton;
    QPushButton *quitButton;
    QGraphicsView *mapView;
    QStatusBar *statusbar;

    void setupUi(QDialog *LobbyDialog)
    {
        if (LobbyDialog->objectName().isEmpty())
            LobbyDialog->setObjectName(QStringLiteral("LobbyDialog"));
        LobbyDialog->resize(981, 586);
        centralwidget = new QWidget(LobbyDialog);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setGeometry(QRect(0, 0, 991, 552));
        characterList = new QListWidget(centralwidget);
        new QListWidgetItem(characterList);
        new QListWidgetItem(characterList);
        new QListWidgetItem(characterList);
        new QListWidgetItem(characterList);
        new QListWidgetItem(characterList);
        characterList->setObjectName(QStringLiteral("characterList"));
        characterList->setGeometry(QRect(30, 210, 271, 81));
        characterView = new QGraphicsView(centralwidget);
        characterView->setObjectName(QStringLiteral("characterView"));
        characterView->setGeometry(QRect(340, 211, 261, 261));
        userlist = new QListView(centralwidget);
        userlist->setObjectName(QStringLiteral("userlist"));
        userlist->setGeometry(QRect(30, 320, 271, 171));
        worldScroll = new QScrollArea(centralwidget);
        worldScroll->setObjectName(QStringLiteral("worldScroll"));
        worldScroll->setGeometry(QRect(30, 30, 571, 161));
        worldScroll->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 569, 159));
        worldList = new QListWidget(scrollAreaWidgetContents);
        new QListWidgetItem(worldList);
        new QListWidgetItem(worldList);
        new QListWidgetItem(worldList);
        new QListWidgetItem(worldList);
        new QListWidgetItem(worldList);
        new QListWidgetItem(worldList);
        new QListWidgetItem(worldList);
        new QListWidgetItem(worldList);
        new QListWidgetItem(worldList);
        new QListWidgetItem(worldList);
        new QListWidgetItem(worldList);
        new QListWidgetItem(worldList);
        worldList->setObjectName(QStringLiteral("worldList"));
        worldList->setGeometry(QRect(10, 10, 551, 141));
        worldScroll->setWidget(scrollAreaWidgetContents);
        userlabel = new QLabel(centralwidget);
        userlabel->setObjectName(QStringLiteral("userlabel"));
        userlabel->setGeometry(QRect(30, 300, 51, 16));
        readyButton = new QPushButton(centralwidget);
        readyButton->setObjectName(QStringLiteral("readyButton"));
        readyButton->setGeometry(QRect(390, 500, 111, 22));
        quitButton = new QPushButton(centralwidget);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setGeometry(QRect(510, 500, 80, 22));
        mapView = new QGraphicsView(centralwidget);
        mapView->setObjectName(QStringLiteral("mapView"));
        mapView->setGeometry(QRect(620, 30, 341, 491));
        statusbar = new QStatusBar(LobbyDialog);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        statusbar->setGeometry(QRect(0, 0, 3, 22));

        retranslateUi(LobbyDialog);

        QMetaObject::connectSlotsByName(LobbyDialog);
    } // setupUi

    void retranslateUi(QDialog *LobbyDialog)
    {
        LobbyDialog->setWindowTitle(QApplication::translate("LobbyDialog", "MainWindow", Q_NULLPTR));

        const bool __sortingEnabled = characterList->isSortingEnabled();
        characterList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = characterList->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("LobbyDialog", "Character 1", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem1 = characterList->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("LobbyDialog", "Character 2", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem2 = characterList->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("LobbyDialog", "Character 3", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem3 = characterList->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("LobbyDialog", "Character 4", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem4 = characterList->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("LobbyDialog", "Character 5", Q_NULLPTR));
        characterList->setSortingEnabled(__sortingEnabled);


        const bool __sortingEnabled1 = worldList->isSortingEnabled();
        worldList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem5 = worldList->item(0);
        ___qlistwidgetitem5->setText(QApplication::translate("LobbyDialog", "World 1", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem6 = worldList->item(1);
        ___qlistwidgetitem6->setText(QApplication::translate("LobbyDialog", "World 2", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem7 = worldList->item(2);
        ___qlistwidgetitem7->setText(QApplication::translate("LobbyDialog", "World 3", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem8 = worldList->item(3);
        ___qlistwidgetitem8->setText(QApplication::translate("LobbyDialog", "World 4", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem9 = worldList->item(4);
        ___qlistwidgetitem9->setText(QApplication::translate("LobbyDialog", "World 5", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem10 = worldList->item(5);
        ___qlistwidgetitem10->setText(QApplication::translate("LobbyDialog", "World 6", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem11 = worldList->item(6);
        ___qlistwidgetitem11->setText(QApplication::translate("LobbyDialog", "World 7", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem12 = worldList->item(7);
        ___qlistwidgetitem12->setText(QApplication::translate("LobbyDialog", "World 8", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem13 = worldList->item(8);
        ___qlistwidgetitem13->setText(QApplication::translate("LobbyDialog", "World 9", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem14 = worldList->item(9);
        ___qlistwidgetitem14->setText(QApplication::translate("LobbyDialog", "World 10", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem15 = worldList->item(10);
        ___qlistwidgetitem15->setText(QApplication::translate("LobbyDialog", "World 11", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem16 = worldList->item(11);
        ___qlistwidgetitem16->setText(QApplication::translate("LobbyDialog", "World 12", Q_NULLPTR));
        worldList->setSortingEnabled(__sortingEnabled1);

        userlabel->setText(QApplication::translate("LobbyDialog", "Userlist", Q_NULLPTR));
        readyButton->setText(QApplication::translate("LobbyDialog", "Ready", Q_NULLPTR));
        quitButton->setText(QApplication::translate("LobbyDialog", "Quit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LobbyDialog: public Ui_LobbyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LOBBY_DIALOG_UI_H
