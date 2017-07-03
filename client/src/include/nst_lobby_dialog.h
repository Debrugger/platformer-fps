#ifndef __LOBBY_DIALOG_H
#define __LOBBY_DIALOG_H

#include "qtinc.h"
#include "build/lobby_dialog.ui.h"

class LobbyDialog : public QMainWindow, public Ui::LobbyWindow  /*Ui:: has to be same as window/widget name in qtcreator .ui file*/
{
	Q_OBJECT;

   const int BrokenConfig = 20; //internal excaption in constructor
QGraphicsScene* char_view_scene; /*needs to be global because scene gets deleted when out of scope otherwise*/
QGraphicsScene* map_view_scene;

public:
	LobbyDialog();
	virtual ~LobbyDialog();
 	void ReadSettings();
	void UpdateImage(QGraphicsView*&, QGraphicsScene*&, QPixmap&, QString&);
	void LogPrint(const QString&);
	void resizeEvent(QResizeEvent*);

   static const int FailedToBuild = 10;
	QPixmap char_pixmap;
	QPixmap map_pixmap;

public slots:
	void OnCharListChanged();
	void OnMapListChanged();
	void on_quitButton_clicked();
	void on_gl_button_clicked();
	
};

#endif //__LOBBY_DIALOG_H
