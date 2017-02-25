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

#include "main.h"
#include "../../build/configurator/configurator_ui.h"

using namespace std;

QApplication* app;
MainWindow* mainwindow_ptr;
QSignalMapper* signalmapper;

QString char_image_path[5];
QString map_image_path[5];

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

	m1_map_lineEdit->setReadOnly(true);
	m2_map_lineEdit->setReadOnly(true);
	m3_map_lineEdit->setReadOnly(true);
	m4_map_lineEdit->setReadOnly(true);
	m5_map_lineEdit->setReadOnly(true);
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

   connect(m1_map_Button, SIGNAL(clicked()), signalmapper, SLOT(map()));
   connect(m2_map_Button, SIGNAL(clicked()), signalmapper, SLOT(map()));
   connect(m3_map_Button, SIGNAL(clicked()), signalmapper, SLOT(map()));
   connect(m4_map_Button, SIGNAL(clicked()), signalmapper, SLOT(map()));
   connect(m5_map_Button, SIGNAL(clicked()), signalmapper, SLOT(map()));

   /*Passing arguments to a SLOT is impossible, a signal mapper takes all the signals and reroutes them to the same function with diff. arguments*/
	signalmapper->setMapping(c1_image_Button, 1);
	signalmapper->setMapping(c2_image_Button, 2);
	signalmapper->setMapping(c3_image_Button, 3);
	signalmapper->setMapping(c4_image_Button, 4);
	signalmapper->setMapping(c5_image_Button, 5);

	signalmapper->setMapping(m1_map_Button, 10);
	signalmapper->setMapping(m2_map_Button, 11);
	signalmapper->setMapping(m3_map_Button, 12);
	signalmapper->setMapping(m4_map_Button, 13);
	signalmapper->setMapping(m5_map_Button, 14);

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
	QString* p;
	if (button_number < 10)
		p = &char_image_path[button_number - 1];
	else
		p = &map_image_path[button_number - 10];
	QString path = QFileDialog::getOpenFileName(this, tr("Open image"), app->applicationDirPath(), tr("PNG Images (*.png)"));
	QDir dir(QDir::currentPath());
	*p = dir.relativeFilePath(path);
	qDebug() << "Path to image: " << *p;
	
	switch (button_number)
	{
		case 1: c1_image_lineEdit->setText(char_image_path[button_number-1]); break;
		case 2: c2_image_lineEdit->setText(char_image_path[button_number-1]); break;
		case 3: c3_image_lineEdit->setText(char_image_path[button_number-1]); break;
		case 4: c4_image_lineEdit->setText(char_image_path[button_number-1]); break;
		case 5: c5_image_lineEdit->setText(char_image_path[button_number-1]); break;

		case 10: m1_map_lineEdit->setText(map_image_path[button_number-10]); break; 
		case 11: m2_map_lineEdit->setText(map_image_path[button_number-10]); break; 
		case 12: m3_map_lineEdit->setText(map_image_path[button_number-10]); break; 
		case 13: m4_map_lineEdit->setText(map_image_path[button_number-10]); break; 
		case 14: m5_map_lineEdit->setText(map_image_path[button_number-10]); break; 
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

	for (int i = 0; i < 4; i++)
	{
		char_image_path[i] = settings.value(QString("char_image%1").arg(i+1)).toString();
		map_image_path[i] = settings.value(QString("map_image%1").arg(i+1)).toString();
	}
	settings.endGroup();

	c1_image_lineEdit->setText(char_image_path[0]);
	c2_image_lineEdit->setText(char_image_path[1]);
	c3_image_lineEdit->setText(char_image_path[2]);
	c4_image_lineEdit->setText(char_image_path[3]);
	c5_image_lineEdit->setText(char_image_path[4]);

	m1_map_lineEdit->setText(map_image_path[0]);
	m2_map_lineEdit->setText(map_image_path[1]);
	m3_map_lineEdit->setText(map_image_path[2]);
	m4_map_lineEdit->setText(map_image_path[3]);
	m5_map_lineEdit->setText(map_image_path[4]);

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

	settings.setValue("map_image1", map_image_path[0]);
	settings.setValue("map_image2", map_image_path[1]);
	settings.setValue("map_image3", map_image_path[2]);
	settings.setValue("map_image4", map_image_path[3]);
	settings.setValue("map_image5", map_image_path[4]);
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
