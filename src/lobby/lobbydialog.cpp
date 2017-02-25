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

#include <QApplication>

#include "main.h"

using namespace std;

QGraphicsScene* char_view_scene; /*needs to be global because scene gets deleted when out of scope otherwise*/
QGraphicsScene* map_view_scene;

QString char_image_path[5];
QString map_image_path[5];

LobbyDialog::LobbyDialog()
{
	setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_QuitOnClose);
	setWindowTitle("Lobby");
   
	connect(characterList, SIGNAL(currentRowChanged(int)), this, SLOT(OnCharListChanged()));
	connect(mapList, SIGNAL(currentRowChanged(int)), this, SLOT(OnMapListChanged()));

	characterView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /*no scroll bars in the image*/
	characterView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	mapView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /*no scroll bars in the image*/
	mapView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

   char_view_scene = new QGraphicsScene(QRectF(0, 0, characterView->geometry().width(), characterView->geometry().height()), 0);
   map_view_scene = new QGraphicsScene(QRectF(0, 0, mapView->geometry().width(), mapView->geometry().height()), 0);

	characterList->setCurrentRow(0);
	mapList->setCurrentRow(0);
	ReadSettings();
	UpdateImage(characterView, char_view_scene, char_pixmap, char_image_path[characterList->currentRow()]); /*Set up graphics view for character picture*/
	UpdateImage(mapView, map_view_scene, map_pixmap, map_image_path[mapList->currentRow()]);
}

LobbyDialog::~LobbyDialog()
{
}

void LobbyDialog::on_quitButton_clicked()
{
  cout << "Quit" << endl;
  close();
static_cast<QApplication *>(QApplication::instance())->quit();
}

void LobbyDialog::UpdateImage(QGraphicsView*& view, QGraphicsScene*& scene, QPixmap& pixmap, QString& path)
{
	scene->clear();
	pixmap.load(path);

	/*make image fit in graphics view*/
	scene->addPixmap(pixmap.scaled(QSize((int)scene->width(), (int)scene->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	//characterView->fitInView(char_view_scene->itemsBoundingRect(), Qt::KeepAspectRatio); /*scaling works w/o this, with this the image is not scaled properly the first time*/
	view->setScene(scene);
}

void LobbyDialog::OnCharListChanged()
{
	cout << "Character list: Row changed to " << characterList->currentRow() << endl;
	UpdateImage(characterView, char_view_scene, char_pixmap, char_image_path[characterList->currentRow()]);
}

void LobbyDialog::OnMapListChanged()
{
	cout << "Map list: Row changed to " << mapList->currentRow() << endl;
	UpdateImage(mapView, map_view_scene, map_pixmap, map_image_path[mapList->currentRow()]);
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

	map_image_path[0] = settings.value("map_image1").toString();
	map_image_path[1] = settings.value("map_image2").toString();
	map_image_path[2] = settings.value("map_image3").toString();
	map_image_path[3] = settings.value("map_image4").toString();
	map_image_path[4] = settings.value("map_image5").toString();
	settings.endGroup();

	cout << "Settings loaded!" << endl;
	for (int i = 0; i < 4; i++)
		qDebug() << "Loaded image path " << char_image_path[i];

}
