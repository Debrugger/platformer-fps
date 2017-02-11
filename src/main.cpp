#include <math.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
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


LobbyDialog::LobbyDialog()
{
	setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle("Lobby");


   /*Set up graphics view for character picture*/
	int width = characterView->geometry().width();
	int height = characterView->geometry().height();

	QPixmap pixmap;
   char_view_scene = new QGraphicsScene(QRectF(0, 0, width, height), 0);

	characterView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /*no scroll bars in the image*/
	characterView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	pixmap.load("rc/lightros.png"); /*load image here*/

	/*make image fit in graphics view*/
	char_view_scene->addPixmap(pixmap.scaled(QSize((int)char_view_scene->width(), (int)char_view_scene->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	characterView->fitInView(char_view_scene->itemsBoundingRect(), Qt::KeepAspectRatio);
	characterView->setScene(char_view_scene);
}

LobbyDialog::~LobbyDialog()
{
}
int main(int c, char *p[])
{
	app = new QApplication(c, p);
	lobby_dialog_ptr = new LobbyDialog;
	lobby_dialog_ptr->exec();
	return app->exec();
}

