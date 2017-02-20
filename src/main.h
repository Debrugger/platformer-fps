#ifndef __MAIN_H
#define __MAIN_H
#include <QApplication>
#include <QDialog>
#include <QDebug>
#include <QSettings>

#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QLineEdit>

#include <QGraphicsView>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFileDialog>

#include "lobby_dialog_ui.h"

class LobbyDialog : public QDialog, public Ui::LobbyDialog  /*Ui:: has to be same as window/widget name in qtcreator .ui file*/
{
	Q_OBJECT;
public:
	LobbyDialog();
	virtual ~LobbyDialog();

 	void ReadSettings();

	QPixmap char_pixmap;
	void UpdateImage(QGraphicsView*&, QGraphicsScene*&, QPixmap&, QString&, int);
public slots:
	void OnCharListChanged();
	void on_quitButton_clicked();
	
};


#endif // __MAIN_H

