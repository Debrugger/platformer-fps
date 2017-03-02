#ifndef CONFIGURATOR_UI_H
#define CONFIGURATOR_UI_H

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


QT_BEGIN_NAMESPACE

class Ui_ConfiguratorMainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *saveButton;
    QPushButton *quitButton;
	 QPushButton* add_char_button;
    QLabel *status_label;
    QStatusBar *statusbar;
	 QScrollArea* char_scroll_area;
	 QBoxLayout* char_vert_layout;
	 
	 QGroupBox* char_box[30];
	 QPushButton* char_img_button[30];

	 QWidget* char_widget;

    void setupUi(QMainWindow *ConfiguratorMainWindow)
    {
        if (ConfiguratorMainWindow->objectName().isEmpty())
            ConfiguratorMainWindow->setObjectName(QStringLiteral("ConfiguratorMainWindow"));
        ConfiguratorMainWindow->resize(670, 610);
        centralwidget = new QWidget(ConfiguratorMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));

        char_scroll_area = new QScrollArea(centralwidget);
		  char_scroll_area->setObjectName(QStringLiteral("char_scroll_area"));
		  char_scroll_area->setGeometry(QRect(10, 50, 650, 500));

		  char_widget = new QWidget;
		  char_widget->setGeometry(QRect(10, 10, 650, 580));
		  char_vert_layout = new QVBoxLayout(char_widget);
		  char_vert_layout->setObjectName(QStringLiteral("char_vert_layout"));
		  char_vert_layout->setGeometry(QRect(10, 10, 650, 580));
		  char_vert_layout->setSizeConstraint(QLayout::SetFixedSize); //widgets in the layout have a fixed size
		  char_scroll_area->setWidget(char_widget);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(329, 560, 111, 20));
        quitButton = new QPushButton(centralwidget);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setGeometry(QRect(470, 560, 80, 20));

        status_label = new QLabel(centralwidget);
        status_label->setObjectName(QStringLiteral("status_label"));
        status_label->setGeometry(QRect(70, 560, 181, 20));

		  add_char_button = new QPushButton(centralwidget);
        add_char_button->setObjectName(QStringLiteral("add_char_button"));
        add_char_button->setText("Add character");
        add_char_button->setGeometry(QRect(10, 25, 150, 20));

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

#endif // CONFIGURATOR_UI_H
