#include <math.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

/* Qt */
#include <QApplication>

#include "configurator.h"
#include "configurator_ui.h"

using namespace std;

QApplication* app;
MainWindow* mainwindow_ptr;
QSignalMapper* signalmapper;

QString char_image_path[5];

MainWindow::MainWindow()
{
	setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_QuitOnClose);
	setWindowTitle("Configurator");

	signalmapper = new QSignalMapper(this);

	c1_image_lineEdit->setReadOnly(true);
	c2_image_lineEdit->setReadOnly(true);
	c3_image_lineEdit->setReadOnly(true);
	c4_image_lineEdit->setReadOnly(true);
	c5_image_lineEdit->setReadOnly(true);
	setStyleSheet("QLineEdit[readOnly=\"true\"] {"
			"color: #808080;"
			"background-color: #F0F0F0;"
			"border: 1px solid #B0B0B0;"
			"border-radius: 2px;}");

   connect(c1_image_Button, SIGNAL(clicked()), signalmapper, SLOT(map()));
   connect(c2_image_Button, SIGNAL(clicked()), signalmapper, SLOT(map()));
   connect(c3_image_Button, SIGNAL(clicked()), signalmapper, SLOT(map()));
   connect(c4_image_Button, SIGNAL(clicked()), signalmapper, SLOT(map()));
   connect(c5_image_Button, SIGNAL(clicked()), signalmapper, SLOT(map()));
   /*Passing arguments to a SLOT is impossible, a signal mapper takes all the signals and reroutes them to the same function with diff. arguments*/
	signalmapper->setMapping(c1_image_Button, 1);
	signalmapper->setMapping(c2_image_Button, 2);
	signalmapper->setMapping(c3_image_Button, 3);
	signalmapper->setMapping(c4_image_Button, 4);
	signalmapper->setMapping(c5_image_Button, 5);

	connect(signalmapper, SIGNAL(mapped(int)), this, SLOT(ButtonClicked(int)));

	connect(quitButton, SIGNAL(clicked()), this, SLOT(QuitClicked()));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(SaveSettings()));

	ReadSettings();
}

MainWindow::~MainWindow()
{
}

void MainWindow::ButtonClicked(int button_number)
{
	char_image_path[button_number - 1] = QFileDialog::getOpenFileName(this, tr("Open image"), app->applicationDirPath(), tr("PNG Images (*.png)"));
	qDebug() << "Path to image: " << char_image_path[button_number-1];
	switch (button_number)
	{
		case 1: c1_image_lineEdit->setText(char_image_path[button_number-1]); break;
		case 2: c2_image_lineEdit->setText(char_image_path[button_number-1]); break;
		case 3: c3_image_lineEdit->setText(char_image_path[button_number-1]); break;
		case 4: c4_image_lineEdit->setText(char_image_path[button_number-1]); break;
		case 5: c5_image_lineEdit->setText(char_image_path[button_number-1]); break;
	}
}

void MainWindow::QuitClicked()
{
	mainwindow_ptr->close();
	app->quit();
}

void MainWindow::ReadSettings()
{
	QSettings settings("settings", QSettings::NativeFormat);
	settings.beginGroup("Preview_Images");
	char_image_path[0] = settings.value("char_image1").toString();
	char_image_path[1] = settings.value("char_image2").toString();
	char_image_path[2] = settings.value("char_image3").toString();
	char_image_path[3] = settings.value("char_image4").toString();
	char_image_path[4] = settings.value("char_image5").toString();
	settings.endGroup();
	c1_image_lineEdit->setText(char_image_path[0]);
	c2_image_lineEdit->setText(char_image_path[1]);
	c3_image_lineEdit->setText(char_image_path[2]);
	c4_image_lineEdit->setText(char_image_path[3]);
	c5_image_lineEdit->setText(char_image_path[4]);

	for (int i = 0; i < 4; i++)
		qDebug() << "Loaded image path " << char_image_path[i];
}

void MainWindow::SaveSettings()
{
	QSettings settings("settings", QSettings::NativeFormat);
	settings.setIniCodec("UTF-8");
	settings.beginGroup("Preview_Images");
	settings.setValue("char_image1", char_image_path[0]);
	settings.setValue("char_image2", char_image_path[1]);
	settings.setValue("char_image3", char_image_path[2]);
	settings.setValue("char_image4", char_image_path[3]);
	settings.setValue("char_image5", char_image_path[4]);
	settings.endGroup();

	status_label->setText("Settings Saved!");
}

int main(int c, char*p[])
{
	app = new QApplication(c, p);

   mainwindow_ptr = new MainWindow;
	mainwindow_ptr->show();
	return app->exec();
}
//also der soll wenns eine gibt die config laden, alles in die felder schreiben
//wenn nich gibt halt nicht
//dann die pfad strings in ne config file schreiben
