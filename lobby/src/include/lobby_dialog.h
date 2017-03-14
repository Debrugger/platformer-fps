#ifndef __LOBBY_DIALOG_H
#define __LOBBY_DIALOG_H

#include "qtinc.h"
#include "build/lobby_dialog.ui.h"

class LobbyDialog : public QDialog, public Ui::LobbyDialog  /*Ui:: has to be same as window/widget name in qtcreator .ui file*/
{
	Q_OBJECT;

   const int BrokenConfig = 20; //internal excaption in constructor

public:
	LobbyDialog();
	virtual ~LobbyDialog();

 	void ReadSettings();

	QPixmap char_pixmap;
	QPixmap map_pixmap;
	void UpdateImage(QGraphicsView*&, QGraphicsScene*&, QPixmap&, QString&);
	void LogPrint(const QString&);

   static const int FailedToBuild = 10;

public slots:
	void OnCharListChanged();
	void OnMapListChanged();
	void on_quitButton_clicked();
	
};

#endif //__LOBBY_DIALOG_H
