#ifndef __CONFIGURATOR_H
#define __CONFIGURATOR_H
#include <QApplication>
#include <QMainWindow>
#include <QDebug>

#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QLineEdit>
#include <QFileDialog>

#include "configurator_ui.h"

class MainWindow : public QMainWindow, public Ui::MainWindow  /*Ui:: has to be same as window/widget name in qtcreator .ui file*/
{
	Q_OBJECT;
public:
	MainWindow();
	virtual ~MainWindow();

 	void ReadSettings();

	QPixmap char_pixmap;
public slots:
	void QuitClicked();
	
};


#endif // __CONFIGURATOR_H

