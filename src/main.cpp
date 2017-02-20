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
#include "lobby_dialog_ui.h"

using namespace std;

QApplication* app;

LobbyDialog* lobby_dialog_ptr;

QGraphicsScene* char_view_scene; /*needs to be global because scene gets deleted when out of scope otherwise*/

QString char_image_path[5]; /*the idea is that this will be filled by reading a QSettings config file, will be changed to type QString*/

LobbyDialog::LobbyDialog()
{
	setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_QuitOnClose);
	setWindowTitle("Lobby");
   
	connect(characterList, SIGNAL(currentRowChanged(int)), this, SLOT(OnCharListChanged()));

	characterView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /*no scroll bars in the image*/
	characterView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	mapView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /*no scroll bars in the image*/
	mapView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	int width = characterView->geometry().width();
	int height = characterView->geometry().height();
   char_view_scene = new QGraphicsScene(QRectF(0, 0, width, height), 0);
	characterList->setCurrentRow(0);
	ReadSettings();
	UpdateImage(characterView, char_view_scene, char_pixmap, char_image_path[characterList->currentRow()], characterList->currentRow()); /*Set up graphics view for character picture*/
}

LobbyDialog::~LobbyDialog()
{
}

void LobbyDialog::on_quitButton_clicked()
{
  cout << "Quit" << endl;
  close();
  app->quit();
}

void LobbyDialog::UpdateImage(QGraphicsView*& view, QGraphicsScene*& scene, QPixmap& pixmap, QString& path, int image_index)
{
	scene->clear();
	pixmap.load(path);
	qDebug() << "image_index: " << image_index << path;

	/*make image fit in graphics view*/
	scene->addPixmap(pixmap.scaled(QSize((int)scene->width(), (int)scene->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	//characterView->fitInView(char_view_scene->itemsBoundingRect(), Qt::KeepAspectRatio); /*scaling works w/o this, with this the image is not scaled properly the first time*/
	view->setScene(scene);
}

void LobbyDialog::OnCharListChanged()
{
	cout << "Character list: Row changed to " << characterList->currentRow() << endl;
	UpdateImage(characterView, char_view_scene, char_pixmap, char_image_path[characterList->currentRow()], characterList->currentRow());
}

void LobbyDialog::ReadSettings()
{
	QSettings settings("settings", QSettings::NativeFormat);
	settings.setIniCodec("UTF-8");
	settings.beginGroup("Preview_Images");
	char_image_path[0] = settings.value("char_image1").toString();
	char_image_path[1] = settings.value("char_image2").toString();
	char_image_path[2] = settings.value("char_image3").toString();
	char_image_path[3] = settings.value("char_image4").toString();
	char_image_path[4] = settings.value("char_image5").toString();
	settings.endGroup();

	cout << "Settings loaded!" << endl;
	for (int i = 0; i < 4; i++)
		qDebug() << "Loaded image path " << char_image_path[i];

}

int main(int c, char *p[])
{
	app = new QApplication(c, p);
   app->setOrganizationName("Platformer FPS");
	app->setApplicationName("Shooter with platforms");

	lobby_dialog_ptr = new LobbyDialog;
	lobby_dialog_ptr->exec();
	return app->exec();
}

