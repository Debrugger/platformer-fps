#ifndef __MAIN_H
#define __MAIN_H
#include <QApplication>
#include <QMainWindow>
#include <QDebug>

#include <QSignalMapper>

#include <QLabel>
#include <QSettings>
#include <QPushButton>
#include <QString>
#include <QLineEdit>
#include <QFileDialog>

#include "../../build/configurator/configurator_ui.h"

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
	void ButtonClicked(int);
	void SaveSettings();
	
};


#endif // __MAIN_H
