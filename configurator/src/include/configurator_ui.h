#ifndef __CONFIGURATOR_UI_H
#define __CONFIGURATOR_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTabWidget>


QT_BEGIN_NAMESPACE

class Ui_ConfiguratorMainWindow
{
    public:
        QWidget *centralwidget;
        QPushButton *saveButton;
        QPushButton *quitButton;
        QPushButton* add_char_button;
        QPushButton* add_map_button;
        QLabel *status_label;
        QStatusBar *statusbar;

        QScrollArea* char_scroll_area;
        QBoxLayout* char_vert_layout;
        QScrollArea* map_scroll_area;
        QBoxLayout* map_vert_layout;
        QScrollArea* weapon_scroll_area;
        QBoxLayout* weapon_vert_layout;

        QTabWidget* tab_widget;
        QWidget* char_tab;
        QWidget* map_tab;
        QWidget* weapon_tab;

        QWidget* char_widget;
        QWidget* map_widget;
        QWidget* weapon_widget;
		  QRect vert_dim = QRect(10, 10, 630, 545);
		  QRect scroll_dim = QRect(5, 30, 652, 485);
		  QRect widget_dim = QRect(10, 10, 630, 545);
               
        void setupUi(QMainWindow *ConfiguratorMainWindow)
        {
            if (ConfiguratorMainWindow->objectName().isEmpty())
                ConfiguratorMainWindow->setObjectName(QStringLiteral("ConfiguratorMainWindow"));
            ConfiguratorMainWindow->resize(670, 610);
            centralwidget = new QWidget(ConfiguratorMainWindow);
            centralwidget->setObjectName(QStringLiteral("centralwidget"));
            tab_widget = new QTabWidget(centralwidget);
            tab_widget->setGeometry(QRect(5, 10, 660, 545));
            tab_widget->setObjectName(QStringLiteral("tab_widget"));

            char_tab = new QWidget();
            char_tab->setObjectName(QStringLiteral("char_tab"));
            map_tab = new QWidget();
            map_tab->setObjectName(QStringLiteral("map_tab"));
            weapon_tab = new QWidget();
            weapon_tab->setObjectName(QStringLiteral("weapon_tab"));

            tab_widget->addTab(char_tab, QString("Characters"));
            tab_widget->addTab(map_tab, QString("Maps"));
            tab_widget->addTab(weapon_tab, QString("Weapons"));

            char_scroll_area = new QScrollArea(char_tab);
            char_scroll_area->setObjectName(QStringLiteral("char_scroll_area"));
            char_scroll_area->setGeometry(scroll_dim);

            char_widget = new QWidget;
            char_widget->setGeometry(widget_dim);
            char_vert_layout = new QVBoxLayout(char_widget);
            char_vert_layout->setObjectName(QStringLiteral("char_vert_layout"));
            char_vert_layout->setGeometry(vert_dim);
            char_vert_layout->setSizeConstraint(QLayout::SetFixedSize); //widgets in the layout have a fixed size
            char_scroll_area->setWidget(char_widget);

            map_scroll_area = new QScrollArea(map_tab);
            map_scroll_area->setObjectName(QStringLiteral("char_scroll_area"));
            map_scroll_area->setGeometry(scroll_dim);

            map_widget = new QWidget;
            map_widget->setGeometry(widget_dim);
            map_vert_layout = new QVBoxLayout(map_widget);
            map_vert_layout->setObjectName(QStringLiteral("map_vert_layout"));
            map_vert_layout->setGeometry(vert_dim);
            map_vert_layout->setSizeConstraint(QLayout::SetFixedSize); //widgets in the layout have a fixed size
            map_scroll_area->setWidget(map_widget);

            weapon_scroll_area = new QScrollArea(weapon_tab);
            weapon_scroll_area->setObjectName(QStringLiteral("weapon_scroll_area"));
            weapon_scroll_area->setGeometry(scroll_dim);

            weapon_widget = new QWidget;
            weapon_widget->setGeometry(widget_dim);
            weapon_vert_layout = new QVBoxLayout(weapon_widget);
            weapon_vert_layout->setObjectName(QStringLiteral("weapon_vert_layout"));
            weapon_vert_layout->setGeometry(vert_dim);
            weapon_vert_layout->setSizeConstraint(QLayout::SetFixedSize); //widgets in the layout have a fixed size
            weapon_scroll_area->setWidget(weapon_widget);

            saveButton = new QPushButton(centralwidget);
            saveButton->setObjectName(QStringLiteral("saveButton"));
            saveButton->setGeometry(QRect(330, 560, 120, 20));
            quitButton = new QPushButton(centralwidget);
            quitButton->setObjectName(QStringLiteral("quitButton"));
            quitButton->setGeometry(QRect(470, 560, 80, 20));

            status_label = new QLabel(centralwidget);
            status_label->setObjectName(QStringLiteral("status_label"));
            status_label->setGeometry(QRect(70, 560, 280, 20));

            add_char_button = new QPushButton(char_tab);
            add_char_button->setObjectName(QStringLiteral("add_char_button"));
            add_char_button->setText("Add character");
            add_char_button->setGeometry(QRect(5, 5, 150, 20));

            add_map_button = new QPushButton(map_tab);
            add_map_button->setObjectName(QStringLiteral("add_map_button"));
            add_map_button->setText("Add map");
            add_map_button->setGeometry(QRect(5, 5, 150, 20));

            ConfiguratorMainWindow->setCentralWidget(centralwidget);
            statusbar = new QStatusBar(ConfiguratorMainWindow);
            statusbar->setObjectName(QStringLiteral("statusbar"));
            ConfiguratorMainWindow->setStatusBar(statusbar);

            retranslateUi(ConfiguratorMainWindow);

            QMetaObject::connectSlotsByName(ConfiguratorMainWindow);
        } // setupUi

        void retranslateUi(QMainWindow *ConfiguratorMainWindow)
        {
            ConfiguratorMainWindow->setWindowTitle(QApplication::translate("ConfiguratorMainWindow", "MainWindow", Q_NULLPTR));
            saveButton->setText(QApplication::translate("ConfiguratorMainWindow", "Save configuration", Q_NULLPTR));
            quitButton->setText(QApplication::translate("ConfiguratorMainWindow", "Quit", Q_NULLPTR));
            status_label->setText(QString());
        } // retranslateUi

};

namespace Ui {
    class ConfiguratorMainWindow: public Ui_ConfiguratorMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // __CONFIGURATOR_UI_H
