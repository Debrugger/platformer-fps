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

LobbyDialog::LobbyDialog()
{
	setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle("Lobby");
   
	connect(characterList, SIGNAL(currentRowChanged(int)), this, SLOT(OnCharListChanged()));

	characterList->setCurrentRow(0);
	
	UpdateCharImage(characterList->currentRow()); /*Set up graphics view for character picture*/
}

LobbyDialog::~LobbyDialog()
{
}

void LobbyDialog::on_quitButton_clicked()
{
	cout << lobby_dialog_ptr->characterList->currentRow() << endl;
	lobby_dialog_ptr->close();
	app->quit();
}

void LobbyDialog::UpdateCharImage(int char_index)
{
	int width = characterView->geometry().width();
	int height = characterView->geometry().height();

   char_view_scene = new QGraphicsScene(QRectF(0, 0, width, height), 0);
	char_view_scene->clear();
	characterView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /*no scroll bars in the image*/
	characterView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	switch (char_index) /*char_index is the column number right now, decides what character preview image to load*/
	{
		case 0: char_pixmap.load("rc/lightros.png"); /*load image here*/ 
		break;
		case 1: char_pixmap.load("../wallpapers/abstract-hexagons.png"); /*load image here*/
		break;
	}

	/*make image fit in graphics view*/
	char_view_scene->addPixmap(char_pixmap.scaled(QSize((int)char_view_scene->width(), (int)char_view_scene->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	characterView->fitInView(char_view_scene->itemsBoundingRect(), Qt::KeepAspectRatio);
	characterView->setScene(char_view_scene);
}

void LobbyDialog::OnCharListChanged()
{
	cout << "Character list: Row changed to " << characterList->currentRow() << endl;
	UpdateCharImage(characterList->currentRow());
}

int main(int c, char *p[])
{
	app = new QApplication(c, p);
	lobby_dialog_ptr = new LobbyDialog;
	lobby_dialog_ptr->exec();
	return app->exec();
}

