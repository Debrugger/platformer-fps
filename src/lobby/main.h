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
#include <QString>
#include <QFileDialog>

#include "../../build/lobby/lobby_dialog_ui.h"
#include "../../build/lobby/connect_dialog_ui.h"

class LobbyDialog : public QDialog, public Ui::LobbyDialog  /*Ui:: has to be same as window/widget name in qtcreator .ui file*/
{
	Q_OBJECT;
public:
	LobbyDialog();
	virtual ~LobbyDialog();

 	void ReadSettings();

	QPixmap char_pixmap;
	QPixmap map_pixmap;
	void UpdateImage(QGraphicsView*&, QGraphicsScene*&, QPixmap&, QString&);
public slots:
	void OnCharListChanged();
	void OnMapListChanged();
	void on_quitButton_clicked();
	
};

class ConnectDialog : public QDialog, public Ui::ConnectDialog
{
	Q_OBJECT;
public:
	ConnectDialog();
	virtual ~ConnectDialog();
public slots:
	void on_cancel_button_clicked();
};

struct Item
{
	QString image_path;
	QString file_path;
	QString name;
};

#endif // __MAIN_H

