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
#include "configurator_ui.h"

using namespace std;

QApplication* app;
MainWindow* mainwindow_ptr;

QString char_image_path[5];
QString map_image_path[5];

Character* Character::first_character = 0;
Character* Character::last_character = 0;

MainWindow::MainWindow()
{
	setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_QuitOnClose);
	setWindowTitle("Configurator");

	QScrollBar* scrollbar = char_scroll_area->verticalScrollBar();

	setStyleSheet("QLineEdit[readOnly=\"true\"] {"
			"color: #808080;"
			"background-color: #F0F0F0;"
			"border: 1px solid #B0B0B0;"
			"border-radius: 2px;}");

	connect(quitButton, SIGNAL(clicked()), this, SLOT(QuitClicked()));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(SaveSettings()));
	connect(scrollbar, SIGNAL(rangeChanged(int,int)), this, SLOT(ScrollBarToBottom(int, int)));

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

	settings.endGroup();

	for (int i = 0; i < 4; i++)
		qDebug() << "Loaded image path " << char_image_path[i];
}

void MainWindow::SaveSettings()
{
	QSettings settings("settings", QSettings::NativeFormat);
	settings.setIniCodec("UTF-8");

	settings.beginGroup("Names");
	settings.endGroup();

	settings.beginGroup("Preview_Images");
	for (int i = 0; i < 5; i++)
		settings.setValue(QString("char_image%1").arg(i + 1), char_image_path[i]);

	for (int i = 0; i < 5; i++)
		settings.setValue(QString("map_image%1").arg(i + 1), map_image_path[i]);
	settings.endGroup();

	status_label->setText("Settings Saved!");
}

void MainWindow::on_add_char_button_clicked()
{
	Character* character = new Character;
	character->Show();

	if (character->LastCharacter()->index == 29)
		add_char_button->setEnabled(false);
}

void MainWindow::ScrollBarToBottom(int min, int max)
{
    char_scroll_area->verticalScrollBar()->setValue(max);
}

Character::Character()
{
	next_character = 0;
	prev_character = last_character;

	if (!first_character)
	{
		first_character = this;
		index = 0;
	}
	else
	{
		last_character->next_character = this;
		index = prev_character->index + 1;
	}
	last_character = this;

	group_box = new QGroupBox();
	group_box->setFixedSize(618, 150);

	label = new QLabel(group_box);
	label->setText(QString("Character #%1").arg(index + 1));

	delete_button = new QToolButton(group_box);
	delete_button->setAutoFillBackground(true);
	delete_button->setGeometry(601, 19, 15, 15);
	delete_button->setIcon(QIcon("rc/img/delete.png"));
	delete_button->setIconSize(QSize(40, 40));

	img_edit = new QLineEdit(group_box);
	img_edit->setGeometry(QRect(100, 30, 400, 21));
	img_edit->setReadOnly(true);

	img_button = new QPushButton("Browse", group_box);
	img_button->move(10, 30);

	model_edit = new QLineEdit(group_box);
	model_edit->setGeometry(QRect(100, 60, 400, 21)); 
	model_edit->setReadOnly(true);

	model_button = new QPushButton("Browse", group_box);
	model_button->move(10, 60);

	mainwindow_ptr->char_vert_layout->addWidget(group_box);

	connect(delete_button, SIGNAL(clicked()), this, SLOT(DeleteClicked()));
}

Character::~Character()
{
	if (next_character)
		next_character->prev_character = prev_character;
	else
		last_character = prev_character;

	if (prev_character)
		prev_character->next_character = next_character;
	else
		first_character = next_character;
	NumberElements();
	if (last_character->index <= 29)
		mainwindow_ptr->add_char_button->setEnabled(true);
}

void Character::DeleteClicked()
{
	group_box->hide();
	label->hide();
	delete_button->hide();
	delete this;
}

void Character::NumberElements()
{
	int i = 0;
	Character* c;
	c = first_character;
	while (c)
	{
		c->index = i;
		c->label->setText(QString("Character #%1").arg(i + 1));
		c = c->next_character;
		i++;
	}
}

int main(int c, char*p[])
{
	app = new QApplication(c, p);
   mainwindow_ptr = new MainWindow;
	mainwindow_ptr->show();
	return app->exec();
}
